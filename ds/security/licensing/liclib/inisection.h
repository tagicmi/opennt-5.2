#pragma once
#include "iniparser.h"

class CIniSection
{
	BOOL m_fAttached;
	LPCSTR m_lpSectionData;
	DWORD m_cbSectionData;
	HANDLE m_hFile;
	HANDLE m_hFileMapping;
	LPVOID m_lpFileMap;
public:
	CIniSection();
	~CIniSection();
	DWORD Parse(CParser& parser);
	DWORD Attach(LPCSTR lpFileData, DWORD cbFileData, LPCSTR lpszSectionName);
	void Close();
protected:
	DWORD _FindSection(LPCSTR lpFileData, DWORD cbFileData, LPCSTR lpszSectionName, LPCSTR& lpSectionData, DWORD& cbSectionData);
};
