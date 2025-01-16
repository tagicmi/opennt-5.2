#pragma once
class CAutoString {
	char* m_lpData;
	DWORD m_dwAllocated;
	DWORD m_dwSize;
	const char* m_lpCurrent;
	DWORD m_nStringsCount;
	DWORD m_dwIncreaseSize;
public:
	CAutoString();
	~CAutoString();
	virtual void Reset();
	DWORD AddString(LPCSTR lpszData);
	DWORD AddString(LPCSTR lpData, DWORD cbData);
	LPCSTR MoveToFirstString();
	LPCSTR MoveToNextString();
	void ChangeIncreaseSize(DWORD dwIncreaseSize);
};
