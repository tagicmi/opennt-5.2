#include <wincrypt.h>
class CWPACertificateManager
{
    BYTE* m_lpKey1;
    DWORD m_cbKey1;
    BYTE* m_lpKey2;
    DWORD m_cbKey2;
    DWORD m_Unused;
public:
    CWPACertificateManager();
    ~CWPACertificateManager();
    DWORD Init(const BYTE* lpKey1, DWORD cbKey1, const BYTE* lpKey2, DWORD cbKey2);
    DWORD Clear();
    DWORD ValidateInternetActivation(const BYTE* lpRootCert, DWORD cbRootCert, const BYTE* lpCertChain, DWORD cbCertChain, LPVOID* ppLicense, DWORD* pcbLicense);
private:
    DWORD FindWPAExtension(HCERTSTORE hCertStore, PCCERT_CONTEXT* ppCertContext, PVOID* ppData, DWORD* pcbData);
    LPWSTR WasteGuid();
    DWORD LoadPrivateKeys(LPCWSTR szIgnored, HCRYPTPROV* phCryptProv);
    DWORD ClosePrivateKeys(LPCWSTR szIgnored, HCRYPTPROV hCryptProv);
};
