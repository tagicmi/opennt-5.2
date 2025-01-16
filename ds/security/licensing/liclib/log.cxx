#include "precomp.h"
#pragma hdrstop
#include "log.h"

CAutoString::CAutoString() {
	m_lpData = NULL;
	m_dwAllocated = 0;
	m_dwSize = 0;
	m_lpCurrent = NULL;
	m_dwIncreaseSize = 0x400;
	m_nStringsCount = 0;
}

CAutoString::~CAutoString() {
	Reset();
}

void CAutoString::Reset() {
	delete m_lpData;
	m_lpData = NULL;
	m_dwAllocated = 0;
	m_dwSize = 0;
	m_nStringsCount = 0;
}

DWORD CAutoString::AddString(LPCSTR lpszData) {
	return AddString(lpszData, lstrlenA(lpszData));
}

DWORD CAutoString::AddString(LPCSTR lpData, DWORD cbData) {
	DWORD err = ERROR_SUCCESS;
	DWORD var_10 = cbData + 5;
	if (m_dwSize + var_10 + 4 >= m_dwAllocated) {
		DWORD var_C = m_dwIncreaseSize + m_dwAllocated + var_10 + 4;
		char* var_8 = new char[var_C];
		if (var_8 == NULL) {
			err = ERROR_OUTOFMEMORY;
			goto Done;
		}
		memcpy(var_8, m_lpData, m_dwSize);
		delete m_lpData;
		m_lpData = var_8;
		m_dwAllocated = var_C;
	}
	*(DWORD*)(m_lpData + m_dwSize) = cbData;
	lstrcpynA(m_lpData + m_dwSize + 4, lpData, cbData + 1);
	m_dwSize += var_10;
	*(DWORD*)(m_lpData + m_dwSize) = 0xFFFFFFFF;
	++m_nStringsCount;
Done:
	return err;
}

LPCSTR CAutoString::MoveToFirstString() {
	m_lpCurrent = m_lpData;
	if (m_lpData == NULL || *(DWORD*)m_lpData == 0xFFFFFFFF) {
		return NULL;
	}
	return m_lpData + 4;
}

LPCSTR CAutoString::MoveToNextString() {
	if (m_lpCurrent != NULL) {
		m_lpCurrent += *(DWORD*)m_lpCurrent + 5;
	}
	if (*(DWORD*)m_lpCurrent == 0xFFFFFFFF) {
		return NULL;
	}
	return m_lpCurrent + 4;
}

void CAutoString::ChangeIncreaseSize(DWORD dwIncreaseSize) {
	m_dwIncreaseSize = dwIncreaseSize;
}
