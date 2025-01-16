#include "precomp.h"
#pragma hdrstop
#include <wincrypt.h>
#include <objbase.h>

#include "lmcrypt.h"
#include "../include/certchain.h"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() Begin_Vspweb_Scp_Segment_3_5();
#endif
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_5() {
__asm {
                mov     eax, 3
BEGIN_SCP_SEGMENT_3_5_0_10_00_00:
                mov     ebx, 5
                retn
}
}
#endif
#pragma warning(pop)

CWPACertificateManager::CWPACertificateManager() {
#ifdef _X86_
	void Begin_Vspweb_Scp_Segment_3_5();
	void End_Vspweb_Scp_Segment_3_5();
	__asm cmp eax, offset Begin_Vspweb_Scp_Segment_3_5
	__asm cmp eax, offset End_Vspweb_Scp_Segment_3_5
#endif
	m_lpKey1 = NULL;
	m_cbKey1 = 0;
	m_lpKey2 = NULL;
	m_cbKey2 = 0;
	m_Unused = 0;
}

CWPACertificateManager::~CWPACertificateManager() {
}

DWORD CWPACertificateManager::Init(const BYTE* lpKey1, DWORD cbKey1, const BYTE* lpKey2, DWORD cbKey2) {
	DWORD err = 0;
	if (lpKey1 == NULL || cbKey1 == 0 || lpKey2 == NULL || cbKey2 == 0) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	m_cbKey1 = cbKey1;
	m_lpKey1 = (BYTE*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbKey1);
	if (!m_lpKey1) {
		err = ERROR_OUTOFMEMORY;
		goto Done;
	}
	memcpy(m_lpKey1, lpKey1, cbKey1);
	m_cbKey2 = cbKey2;
	m_lpKey2 = (BYTE*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbKey2);
	if (!m_lpKey2) {
		err = ERROR_OUTOFMEMORY;
		goto Done;
	}
	memcpy(m_lpKey2, lpKey2, cbKey2);
Done:
	return err;
}

DWORD CWPACertificateManager::Clear() {
	if (m_lpKey1) {
		HeapFree(GetProcessHeap(), 0, m_lpKey1);
		m_lpKey1 = NULL;
		m_cbKey1 = 0;
	}
	if (m_lpKey2) {
		HeapFree(GetProcessHeap(), 0, m_lpKey2);
		m_lpKey2 = NULL;
		m_cbKey2 = 0;
	}
	return ERROR_SUCCESS;
}

DWORD CWPACertificateManager::FindWPAExtension(HCERTSTORE hCertStore, PCCERT_CONTEXT* ppCertContext, PVOID* ppData, DWORD* pcbData) {
	DWORD err = 0;
	PCCERT_CONTEXT pCurrentCertContext = NULL;
	if (hCertStore == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	bool found = false;
	for (;;) {
		pCurrentCertContext = CertEnumCertificatesInStore(hCertStore, pCurrentCertContext);
		if (!pCurrentCertContext) {
			break;
		}
		PCERT_EXTENSION pWPAExtension = CertFindExtension(
			"1.3.6.1.4.1.311.41.3",
			pCurrentCertContext->pCertInfo->cExtension,
			pCurrentCertContext->pCertInfo->rgExtension);
		if (!pWPAExtension) {
			continue;
		}
		*ppCertContext = pCurrentCertContext;
		*pcbData = pWPAExtension->Value.cbData;
		*ppData = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, *pcbData);
		if (!*ppData) {
			err = ERROR_OUTOFMEMORY;
			goto Done;
		}
		memcpy(*ppData, pWPAExtension->Value.pbData, *pcbData);
		found = true;
		break;
	}
	if (!found) {
		err = CRYPT_E_NOT_FOUND;
	}
Done:
	return err;
}

static DWORD __forceinline CreateGuidAsString(LPWSTR szTarget, DWORD dwTargetChars) {
	GUID guid;
	DWORD err = CoCreateGuid(&guid);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	if (StringFromGUID2(guid, szTarget, dwTargetChars)) {
		return ERROR_SUCCESS;
	}
	return ERROR_INSUFFICIENT_BUFFER;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
LPWSTR CWPACertificateManager::WasteGuid() {
	LPWSTR edi = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x40 * sizeof(WCHAR));
	if (!edi) {
		goto Done;
	}
	DWORD err = CreateGuidAsString(edi, 0x40);
	if (err != ERROR_SUCCESS) {
fakelabel:
		HeapFree(GetProcessHeap(), 0, edi);
		edi = NULL;
	}
Done:
	return edi;
}
#pragma warning(pop)

DWORD CWPACertificateManager::LoadPrivateKeys(LPCWSTR szIgnored, HCRYPTPROV* phCryptProv) {
	DWORD err = ERROR_SUCCESS;
	HCRYPTKEY hKey1 = NULL, hKey2 = NULL;
	if (m_lpKey1 == NULL || m_lpKey2 == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Cleanup;
	}
	if (!CryptAcquireContext(phCryptProv, NULL, MS_STRONG_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET)) {
		err = GetLastError();
		goto Cleanup;
	}
	if (m_lpKey1 != NULL) {
		if (!CryptImportKey(*phCryptProv, m_lpKey1, m_cbKey1, NULL, NULL, &hKey1)) {
			err = GetLastError();
			goto Cleanup;
		}
	}
	if (m_lpKey2 != NULL) {
		if (!CryptImportKey(*phCryptProv, m_lpKey2, m_cbKey2, NULL, NULL, &hKey2)) {
			err = GetLastError();
			goto Cleanup;
		}
	}
Cleanup:
	if (hKey1 != NULL) {
		CryptDestroyKey(hKey1);
	}
	if (hKey2 != NULL) {
		CryptDestroyKey(hKey2);
	}
	return err;
}

DWORD CWPACertificateManager::ClosePrivateKeys(LPCWSTR szIgnored, HCRYPTPROV hCryptProv) {
	if (hCryptProv && szIgnored) {
		CryptReleaseContext(hCryptProv, 0);
	}
	return ERROR_SUCCESS;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() End_Vspweb_Scp_Segment_3_5();
#endif
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_5() {
__asm {
                                        ; sub_105C1EC+Co
                mov     ecx, 3
END_SCP_SEGMENT_3_5:
                mov     edx, 5
                retn
}
}
#endif

#pragma warning(pop)

DWORD CWPACertificateManager::ValidateInternetActivation(const BYTE* lpRootCert, DWORD cbRootCert, const BYTE* lpCertChain, DWORD cbCertChain, LPVOID* ppLicense, DWORD* pcbLicense) {
	HCRYPTPROV hCryptProvForPublicKey = NULL;
	HCRYPTPROV hCryptProvForCertChain = NULL;
	HCERTSTORE hCertStore = NULL;
	PCCERT_CONTEXT pCertContext = NULL;
	PCERT_PUBLIC_KEY_INFO pPublicKey = 0;
	DWORD cbPublicKey = 0;
	PVOID pLicenseData = 0;
	DWORD cbLicenseData = 0;
	DWORD err;
	LPWSTR szIgnored = WasteGuid();
	if (!szIgnored) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	err = LoadPrivateKeys(szIgnored, &hCryptProvForPublicKey);
	if (err != ERROR_SUCCESS) {
		goto Cleanup;
	}
	if (!CryptExportPublicKeyInfo(hCryptProvForPublicKey, AT_SIGNATURE, X509_ASN_ENCODING, NULL, &cbPublicKey)) {
		err = GetLastError();
		goto Cleanup;
	}
	pPublicKey = (PCERT_PUBLIC_KEY_INFO)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbPublicKey);
	if (pPublicKey == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	if (!CryptExportPublicKeyInfo(hCryptProvForPublicKey, AT_SIGNATURE, X509_ASN_ENCODING, pPublicKey, &cbPublicKey)) {
		err = GetLastError();
		goto Cleanup;
	}
	if (!CryptAcquireContext(&hCryptProvForCertChain, NULL, MS_STRONG_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		err = GetLastError();
		goto Cleanup;
	}
	CRYPT_DATA_BLOB CertStoreBlob;
	CertStoreBlob.cbData = cbCertChain;
	CertStoreBlob.pbData = (BYTE*)lpCertChain;
	hCertStore = CertOpenStore(
		CERT_STORE_PROV_PKCS7,
		X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		hCryptProvForCertChain,
		CERT_STORE_NO_CRYPT_RELEASE_FLAG, 
		&CertStoreBlob);
	if (hCertStore == NULL) {
		err = GetLastError();
		goto Cleanup;
	}
	err = FindWPAExtension(hCertStore, &pCertContext, &pLicenseData, &cbLicenseData);
	if (err != ERROR_SUCCESS) {
		goto Cleanup;
	}
	if (!CertComparePublicKeyInfo(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, pPublicKey, &pCertContext->pCertInfo->SubjectPublicKeyInfo)) {
		err = ERROR_INVALID_PARAMETER;
		goto Cleanup;
	}
	err = WPAValidateCertChain(hCertStore, pCertContext, lpRootCert, cbRootCert);
	if (err != ERROR_SUCCESS) {
		goto Cleanup;
	}
	*ppLicense = pLicenseData;
	*pcbLicense = cbLicenseData;
Cleanup:
	if (err != ERROR_SUCCESS && pLicenseData != NULL) {
		HeapFree(GetProcessHeap(), 0, pLicenseData);
	}
	if (pCertContext != NULL) {
		CertFreeCertificateContext(pCertContext);
	}
	if (hCertStore != NULL) {
		CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
	}
	if (hCryptProvForCertChain != NULL) {
		CryptReleaseContext(hCryptProvForCertChain, 0);
	}
	if (pPublicKey != NULL) {
		HeapFree(GetProcessHeap(), 0, pPublicKey);
	}
	ClosePrivateKeys(szIgnored, hCryptProvForPublicKey);
	if (szIgnored != NULL) {
		HeapFree(GetProcessHeap(), 0, szIgnored);
	}
	return err;
}
