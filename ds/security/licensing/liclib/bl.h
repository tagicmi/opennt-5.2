#pragma once
struct BLPIDFILE_VERSIONINFO {
	WORD field_0;
	WORD field_2;
};
extern HRESULT SearchAndCheckPID(BYTE* lpIniData, DWORD cbIniData, PCWSTR lpszProductId, BOOL fOem, DWORD* arg_10);
extern HRESULT sub_1051879(LPCWSTR lpszBaseDir, LPCWSTR arg_4, INT arg_8, PDWORD arg_C);
extern HRESULT GetBLVersion(BYTE* arg_0, DWORD arg_4, struct BLPIDFILE_VERSIONINFO * arg_8);
