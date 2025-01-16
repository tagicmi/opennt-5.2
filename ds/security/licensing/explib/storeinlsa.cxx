#include "precomp.h"
#pragma hdrstop
#include <ntlsa.h>
#include "storeinlsa.h"

HRESULT CLSAStoreForWPA::LoadData(LPBYTE lpData, LPDWORD pcbData) {
    if (lpData == NULL || pcbData == NULL) {
        return E_INVALIDARG;
    }
    HRESULT hr = Open();
    if (FAILED(hr)) {
        return hr;
    }
    m_fStoreOpened = TRUE;
    PLSA_UNICODE_STRING Data = NULL;
    NTSTATUS ntstatus = LsaRetrievePrivateData(m_hLSAHandle, &m_usKeyName, &Data);
    if (ntstatus != STATUS_SUCCESS || Data == NULL) {
        return HRESULT_FROM_WIN32(LsaNtStatusToWinError(ntstatus));
    }
    DWORD err;
    if (Data->Length == 0) {
        err = ERROR_FILE_NOT_FOUND;
        *pcbData = 0;
    } else {
        if (*pcbData != 0 && *pcbData < Data->Length) {
            SecureZeroMemory(Data->Buffer, Data->Length);
            LsaFreeMemory(Data);
            return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
        }
        *pcbData = Data->Length;
        memcpy(lpData, Data->Buffer, Data->Length);
        err = ERROR_SUCCESS;
    }
    SecureZeroMemory(Data->Buffer, Data->Length);
    LsaFreeMemory(Data);
    return HRESULT_FROM_WIN32(err);
}

HRESULT CLSAStoreForWPA::StoreData(CONST BYTE* lpData, DWORD cbData) {
    if (lpData == NULL) {
        return E_INVALIDARG;
    }
    HRESULT hr = Open();
    if (FAILED(hr)) {
        return hr;
    }
    m_fStoreOpened = TRUE;
    LSA_UNICODE_STRING Data;
    Data.Length = (USHORT)cbData;
    Data.MaximumLength = (USHORT)cbData;
    Data.Buffer = (PWSTR)lpData;
    NTSTATUS ntstatus = LsaStorePrivateData(m_hLSAHandle, &m_usKeyName, &Data);
    return HRESULT_FROM_WIN32(LsaNtStatusToWinError(ntstatus));
}

HRESULT CLSAStoreForWPA::Open() {
    if (m_hLSAHandle != NULL) {
        return S_OK;
    }
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));
    NTSTATUS ntstatus = LsaOpenPolicy(&m_usSystemName, &ObjectAttributes, m_dwDesiredAccess, &m_hLSAHandle);
    return HRESULT_FROM_WIN32(LsaNtStatusToWinError(ntstatus));
}

void CLSAStoreForWPA::InitUnicodeString(UNICODE_STRING* pUnicodeString, LPCWSTR pszString) {
    if (pszString == NULL) {
        pUnicodeString->Buffer = NULL;
        pUnicodeString->Length = 0;
        pUnicodeString->MaximumLength = 0;
    } else {
        DWORD Length = lstrlen(pszString);
        pUnicodeString->Length = (USHORT)(Length * sizeof(*pszString));
        pUnicodeString->Buffer = (PWSTR)pszString;
        pUnicodeString->MaximumLength = (USHORT)((Length + 1) * sizeof(*pszString));
    }
}
