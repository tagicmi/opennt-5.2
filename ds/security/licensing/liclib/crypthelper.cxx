#include "precomp.h"
#pragma hdrstop
#include <wincrypt.h>
#include "crypthelper.h"
#include "../include/autoptr.h"
#include "../include/trivialencrypt.h"

CWPACryptHelper::CWPACryptHelper() {
	field_4 = 0;
	field_8 = 0;
	field_C = 0;
	field_10 = 0;
#ifdef _x64
	extern "C" void Begin_Vspweb_Scp_Segment_9_2(void);
	extern "C" void End_Vspweb_Scp_Segment_9_2(void);
#endif
#ifdef _X86_
	extern void Begin_Vspweb_Scp_Segment_9_2(void);
	extern void End_Vspweb_Scp_Segment_9_2(void);
	__asm cmp eax, offset Begin_Vspweb_Scp_Segment_9_2
	__asm cmp eax, offset End_Vspweb_Scp_Segment_9_2
#endif
}

CWPACryptHelper::~CWPACryptHelper() {
	Clear();
}

void CWPACryptHelper::Clear() {
	if (field_C != NULL) {
		CryptDestroyKey(field_C);
		field_C = NULL;
	}
	if (field_8 != NULL) {
		CryptDestroyHash(field_8);
		field_8 = NULL;
	}
	if (field_4 != NULL) {
		CryptReleaseContext(field_4, 0);
		field_4 = NULL;
	}
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_9_2() {
__asm {
                mov     eax, 9
BEGIN_SCP_SEGMENT_9_2_0_10_00_00:
                mov     ebx, 2
                retn
}
}
#endif
#pragma warning(pop)

HRESULT CWPACryptHelper::sub_104FD06(CONST BYTE* lpKey, DWORD cbKey, DWORD field_10_) {
	HRESULT hr = S_OK;
	field_10 = field_10_;
	if (field_10 == 1) {
		if (!CryptAcquireContext(
			&field_4,
			NULL,
			MS_STRONG_PROV,
			PROV_RSA_FULL,
			CRYPT_VERIFYCONTEXT | CRYPT_PREGEN | CRYPT_UPDATE_KEY))
		{
			DWORD err = GetLastError();
			if (err != ERROR_SUCCESS) {
				if (FAILED(HRESULT_FROM_WIN32(err))) {
					hr = HRESULT_FROM_WIN32(err);
				} else {
					hr = E_FAIL;
				}
				if (FAILED(hr)) {
					goto Done;
				}
			}
		}
		if (!CryptImportKey(field_4, lpKey, cbKey, NULL, 0, &field_C)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
			goto Done;
		}
		if (!CryptCreateHash(field_4, CALG_SHA1, NULL, 0, &field_8)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
			goto Done;
		}
Done:
		if (FAILED(hr)) {
			Clear();
		}
		return hr;
	} else {
		if (!CryptAcquireContext(
			&field_4,
			NULL,
			MS_STRONG_PROV,
			PROV_RSA_FULL,
			CRYPT_VERIFYCONTEXT))
		{
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		if (SUCCEEDED(hr) && !CryptCreateHash(field_4, CALG_MD5, NULL, 0, &field_8)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		if (SUCCEEDED(hr) && !CryptHashData(field_8, lpKey, cbKey, 0)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		if (SUCCEEDED(hr) && !CryptDeriveKey(field_4, CALG_RC4, field_8, CRYPT_EXPORTABLE | (128 << 16), &field_C)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		if (FAILED(hr)) {
			Clear();
		}
		return hr;
	}
}

HRESULT CWPACryptHelper::sub_10500FE(LPCVOID lpData, DWORD cbData, LPCVOID lpSignature, DWORD cbSignature) {
	if (!CryptHashData(field_8, (CONST BYTE*)lpData, cbData, 0)) {
		HRESULT hr;
		if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		} else {
			hr = E_FAIL;
		}
		return hr;
	}
	if (!CryptVerifySignature(field_8, (CONST BYTE*)lpSignature, cbSignature, field_C, NULL, 0)) {
		HRESULT hr;
		if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		} else {
			hr = E_FAIL;
		}
		return hr;
	}
	return S_OK;
}

HRESULT CWPACryptHelper::sub_105021B(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData) {
	HRESULT hr = S_OK;
	DWORD err = RegQueryValueEx(hKey, lpValueName, NULL, NULL, lpData, &cbData);
	hr = HRESULT_FROM_WIN32(err);
	if (FAILED(hr)) {
		goto Done;
	}
	if (!CryptDecrypt(field_C, NULL, TRUE, 0, lpData, &cbData)) {
		if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		} else {
			hr = E_FAIL;
		}
		goto Done;
	}
	WPADecrypt(lpData, cbData, dword_1019778);
Done:
	return hr;
}

HRESULT CWPACryptHelper::sub_1050495(LPBYTE lpData, DWORD cbData, PDWORD pcbDecrypted) {
	HRESULT hr = S_OK;
	*pcbDecrypted = cbData;
	if (!CryptDecrypt(field_C, NULL, TRUE, 0, lpData, pcbDecrypted)) {
		if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		} else {
			hr = E_FAIL;
		}
		return hr;
	}
	return hr;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_9_2(void) {
__asm {
                mov     ecx, 9
END_SCP_SEGMENT_9_2:
                mov     edx, 2
                retn
}
}
#endif
#pragma warning(pop)

HRESULT CWPACryptHelper::sub_105068E(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData) {
	HRESULT hr = S_OK;
	AutoHeapPtr<BYTE> Buffer = (BYTE*)HeapAlloc(GetProcessHeap(), 0, cbData);
	if (Buffer == NULL) {
		hr = E_OUTOFMEMORY;
	} else {
		memcpy(Buffer, lpData, cbData);
		WPAEncrypt(Buffer, cbData, dword_1019778);
		DWORD dwDataLen = cbData;
		if (!CryptEncrypt(field_C, NULL, TRUE, 0, Buffer, &dwDataLen, cbData)) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		if (FAILED(hr)) {
			return hr;
		}
		if (RegSetValueEx(hKey, lpValueName, NULL, REG_BINARY, Buffer, cbData) != ERROR_SUCCESS) {
			if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
				hr = HRESULT_FROM_WIN32(GetLastError());
			} else {
				hr = E_FAIL;
			}
		}
		return hr;
	}
	return hr;
}
