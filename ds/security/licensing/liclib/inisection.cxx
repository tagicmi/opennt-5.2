#include "precomp.h"
#pragma hdrstop
#include "inisection.h"

CIniSection::CIniSection() {
	m_hFile = INVALID_HANDLE_VALUE;
	m_fAttached = FALSE;
	m_lpSectionData = 0;
	m_cbSectionData = 0;
	m_hFileMapping = NULL;
	m_lpFileMap = NULL;
}

CIniSection::~CIniSection() {
	Close();
}

DWORD CIniSection::Parse(CParser& parser) {
	if (!m_fAttached) {
		return 0xE001;
	}
	return parser.Parse(m_lpSectionData, m_cbSectionData);
}

inline LONG sub_104DF79(LPCSTR szHaystack, ULONG nHaystackOffset, DWORD cchHaystack, LPCSTR szNeedle, DWORD cchNeedle) {
	for (ULONG nOffset = nHaystackOffset; (LONG)(nOffset - nHaystackOffset) <= (LONG)(cchHaystack - cchNeedle); nOffset++) {
		if (!_strnicmp(szHaystack + nOffset, szNeedle, cchNeedle)) {
			return nOffset;
		}
	}
	return -1;
}

DWORD CIniSection::_FindSection(LPCSTR lpFileData, DWORD cbFileData, LPCSTR lpszSectionName, LPCSTR& lpSectionData, DWORD& cbSectionData) {
	DWORD err = ERROR_SUCCESS;
	if (lpFileData == NULL || lpszSectionName == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	char Dest[MAX_PATH];
	Dest[MAX_PATH - 1] = 0;
	if (_snprintf(Dest, MAX_PATH - 1, "[%s]", lpszSectionName) < 0) {
		err = 0xE003;
		goto Done;
	}
	DWORD edi = lstrlenA(Dest);
	ULONG eax = sub_104DF79(lpFileData, 0, cbFileData, Dest, edi);
	if ((LONG)eax < 0) {
		err = 0xE002;
		goto Done;
	}
	eax += edi + 1;
	for (; eax < cbFileData; eax++) {
		if (lpFileData[eax] != ' ') {
			if (lpFileData[eax] != '\r' && lpFileData[eax] != '\n') {
				err = 0xE004;
				goto Done;
			}
			break;
		}
	}
	for (; eax < cbFileData; eax++) {
		if (lpFileData[eax] != '\r' && lpFileData[eax] != '\n') {
			break;
		}
	}
	lpSectionData = lpFileData + eax;
	DWORD ecx;
	for (ecx = eax; ecx < cbFileData; ecx++) {
		if (lpFileData[ecx] == '[') {
			break;
		}
	}
	cbSectionData = ecx - eax;
Done:
	return err;
}

void CIniSection::Close() {
	m_fAttached = FALSE;
	m_lpSectionData = NULL;
	m_cbSectionData = 0;
	if (m_lpFileMap != NULL) {
		UnmapViewOfFile(m_lpFileMap);
		m_lpFileMap = NULL;
	}
	if (m_hFileMapping != NULL) {
		CloseHandle(m_hFileMapping);
		m_hFileMapping = NULL;
	}
	if (m_hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
}

DWORD CIniSection::Attach(LPCSTR lpFileData, DWORD cbFileData, LPCSTR lpszSectionName) {
	if (lpFileData == NULL || lpszSectionName == NULL || *lpszSectionName == 0) {
		return ERROR_INVALID_PARAMETER;
	}
	if (m_fAttached) {
		Close();
	}
	DWORD err = _FindSection(lpFileData, cbFileData, lpszSectionName, m_lpSectionData, m_cbSectionData);
	if (err == ERROR_SUCCESS) {
		m_fAttached = TRUE;
	}
	return err;
}
