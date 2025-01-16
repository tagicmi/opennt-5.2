class CLSAStoreForWPA {
private:
    UNICODE_STRING m_usSystemName;
    UNICODE_STRING m_usKeyName;
    ACCESS_MASK m_dwDesiredAccess;
    LSA_HANDLE m_hLSAHandle;
    BOOL m_fStoreOpened;

    HRESULT Open();
    void InitUnicodeString(UNICODE_STRING* pUnicodeString, LPCWSTR pszString);

public:
    CLSAStoreForWPA(LPCWSTR lpszSystemName, ACCESS_MASK dwDesiredAccess, LPCWSTR lpszKeyName) { // sub_103F5DF
        InitUnicodeString(&m_usSystemName, lpszSystemName);
        InitUnicodeString(&m_usKeyName, lpszKeyName);
        m_hLSAHandle = NULL;
        m_fStoreOpened = FALSE;
        m_dwDesiredAccess = dwDesiredAccess;
    }
    ~CLSAStoreForWPA() { // sub_103F6D9
        if (m_hLSAHandle) {
            LsaClose(m_hLSAHandle);
        }
        m_hLSAHandle = NULL;
    }
    HRESULT LoadData(LPBYTE lpData, LPDWORD pcbData);
    HRESULT StoreData(CONST BYTE* lpData, DWORD cbData);
};
