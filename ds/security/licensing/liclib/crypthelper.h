class CWPACryptHelper {
    HCRYPTPROV field_4;
    HCRYPTHASH field_8;
    HCRYPTKEY field_C;
    DWORD field_10;

public:
    CWPACryptHelper(); // sub_104FAF9
    virtual ~CWPACryptHelper(); // sub_10505D2
    void Clear();
    HRESULT sub_104FD06(CONST BYTE* lpKey, DWORD cbKey, DWORD field_10_);
    HRESULT sub_10500FE(LPCVOID lpData, DWORD cbData, LPCVOID lpSignature, DWORD cbSignature);
    HRESULT sub_105021B(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData);
    HRESULT sub_1050495(LPBYTE lpData, DWORD cbData, PDWORD pcbDecrypted);
    HRESULT sub_105068E(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData);
};
