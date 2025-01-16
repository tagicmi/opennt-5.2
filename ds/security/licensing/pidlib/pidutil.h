#pragma once
// channel ID = yyy in xxxxx-yyy-... from product id;
// sequence number from CD code is yyy*1000000+...
struct CWPAProductChannelInfo {
	DWORD dwChannelInfoIdx;
	DWORD dwKeyIdx;
	DWORD dwChannelIDMin;
	DWORD dwChannelIDMax;
	DWORD dwLicenseType;
	DWORD dwDaysForActivation;
	DWORD dwDaysForEval;
};
struct CWPAProductChannelInfoSigned {
	DWORD dwRecordIdx; // just an index in table of possible CWPAProductChannelInfo-s
	CWPAProductChannelInfo Info;
	DWORD cbSignature;
	LPBYTE lpSignature;
};
extern void sub_105DB4E(PWSTR arg_0, DWORD arg_4);
extern HRESULT sub_105E81B(PWSTR lpszPid2, DWORD cchPid2, PDWORD pdwKeyIdx, PDWORD pdwChannelID, PBOOL pfOem, CWPAProductChannelInfo* pChannelInfo);
extern HRESULT sub_105EAF9(PWSTR arg_0, DWORD arg_4);
extern "C" HRESULT GetFullPKAndHash(LPWSTR lpProductKey, DWORD cbProductKey, LPBYTE lpHash, DWORD cbHash);
extern "C" HRESULT sub_105E224(DWORD arg_0, LPVOID lpData, DWORD cbData);
extern "C" HRESULT sub_105E511(DWORD arg_0, LPVOID lpData, DWORD cbData);
