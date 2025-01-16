#include "precomp.h"
#pragma hdrstop
#include <crypto/sha.h>
#include <wincrypt.h>
#include "../include/dummy.h"
#include "../include/digpid.h"
#include "../include/errors.h"
#include "../include/trivialencrypt.h"
#include "../include/autoptr.h"
#include "../liclib/crypthelper.h"
#include "pidutil.h"

const BYTE byte_101A038[] = {
0x06,0x02,0x00,0x00,0x00,0x24,0x00,0x00,0x52,0x53,0x41,0x31,0x00,0x04,0x00,0x00,
0x01,0x00,0x01,0x00,0x27,0x6C,0x1C,0x2A,0x35,0xCB,0xF2,0xBE,0xC0,0xC3,0xFE,0xE5,
0xB0,0xA8,0xA4,0x44,0xD5,0x6F,0xDB,0x28,0xE4,0xD3,0x22,0xF7,0x66,0xC4,0x42,0x13,
0x00,0x10,0x53,0xF8,0xAC,0xAE,0x37,0xEC,0x37,0xCD,0x85,0x2A,0xAC,0xB0,0x42,0x20,
0x8B,0x2A,0x5D,0x5B,0x08,0x98,0x93,0x5A,0x1A,0x55,0x7C,0xC8,0x7D,0xE2,0xAB,0x9A,
0xAA,0x1C,0x4E,0xCB,0xDA,0x86,0xA6,0xA7,0x32,0xB3,0xB7,0xE7,0xAD,0x84,0x17,0x41,
0xB4,0xEE,0xCE,0x1D,0x5A,0xBA,0xD8,0x8B,0x16,0x84,0x2C,0xA2,0x08,0xD3,0xC5,0xEC,
0xB9,0xCA,0x93,0x90,0x5D,0x56,0x4C,0xF4,0x88,0x94,0xFD,0xA0,0x3D,0xB5,0xDB,0x6D,
0xB4,0x36,0x5B,0xF9,0xDB,0xEF,0xB3,0x03,0x66,0xF0,0xAC,0xE2,0xBD,0xD4,0xC6,0x43,
0xED,0x62,0x28,0xAC,
};

// L"\\dpcdll.dll"
WCHAR word_1075A18[] = {0x2D02,0x48FC,0x03FA,0xC38B,0xE29B,0x31FC,0xAA8C,0x9CF7,0x2732,0x1633,0x57D0,0xEA49,0xFE7A,0x95B6};
// L"Software\Microsoft\Windows NT\CurrentVersion"
WCHAR word_1075A38[] = {0x2CDE,0xCDBD,0xA402,0xC5A3,0x0A36,0xDA5C,0xA5DF,0x03F5,0xF5B2,0xA065,0xDBE2,0x4086,0x03F4,0x2BDA,0x0E37,0x56C1,0x3BBB,0x76B0,0x2D1C,0x978A,0xF494,0x91D4,0x99E1,0x3EBD,0xE952,0x041D,0x77CD,0x30D6,0x8B22,0x919B,0xD9DE,0x18FF,0xB040,0xA119,0xA1E5,0xE240,0xF925,0x5DB3,0xC64B,0x81EE,0x5F65,0xC290,0xC255,0x79DC,0xF720,0x4B0A,0xCF9D};
// L"ProductID"
WCHAR word_1075A98[] = {0x653C,0x113E,0xC741,0x1575,0xEB61,0xC26E,0x516C,0x10F0,0xE3B2,0x0EFC,0x7756,0x5F92};
// L"DigitalProductID"
WCHAR word_1075AB0[] = {0x1B00,0xEA43,0x3531,0x1E66,0x8DDA,0x5DD8,0xAA24,0x7BDE,0xF8A7,0x9A8C,0xE1F1,0xADCB,0x8FFF,0x12C4,0xADC1,0xDA46,0x5AAF,0x8142,0x7CE2};
LPCSTR WPAPidGenWImport = (LPCSTR)125;
LPCSTR WPAPidCheckImport = (LPCSTR)123;
LPCSTR WPAGetProductChannelInfoImport = (LPCSTR)122;
const void* ScpProtectedData_2_1_0_10_00_00[] = {
	&word_1075A18,
	&word_1075A38,
	&word_1075AB0,
	&word_1075A98,
	&byte_101A038,
};

//#include "pidutil_eh.inc"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() Begin_Vspweb_Scp_Segment_2_2();
#endif
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_2_2() {
__asm {
                mov     eax, 2
BEGIN_SCP_SEGMENT_2_2_0_10_00_00:
                mov     ebx, 2
                retn
}
}
#endif
#pragma warning(pop)

typedef DWORD (STDAPICALLTYPE *PIDGenWType)(
    LPWSTR  lpstrSecureCdKey,   // [IN] 25-character Secure CD-Key (gets U-Cased)
    LPCWSTR lpstrMpc,           // [IN] 5-character Microsoft Product Code
    LPCWSTR lpstrSku,           // [IN] Stock Keeping Unit (formatted like 123-12345)
    LPCWSTR lpstrOemId,         // [IN] 4-character OEM ID or NULL
    LPWSTR  lpstrLocal24,       // [IN] 24-character ordered set to use for decode base conversion or NULL for default set (gets U-Cased)
    LPBYTE lpbPublicKey,        // [IN] pointer to optional public key or NULL
    DWORD  dwcbPublicKey,       // [IN] byte length of optional public key
    //DWORD  dwKeyIdx,            // [IN] key pair index optional public key
    BOOL   fOem,                // [IN] is this an OEM install?

    LPWSTR lpstrPid2,           // [OUT] PID 2.0, pass in ptr to 24 character array
    LPBYTE  lpbDigPid,          // [IN/OUT] pointer to DigitalPID buffer. First DWORD is the length
    //LPDWORD lpdwSeq,            // [OUT] optional ptr to sequence number (can be NULL)
    LPBOOL  pfCCP,              // [OUT] optional ptr to Compliance Checking flag (can be NULL)
    LPBOOL  pfPSS);             // [OUT] optional ptr to 'PSS Assigned' flag (can be NULL)

HRESULT sub_105D75C(HMODULE hDpcDll, LPBYTE lpDigitalPID, DWORD cbDigitalPID, LPWSTR lpszMpc) {
	if (lpDigitalPID == NULL) {
		return E_FAIL;
	}
	WCHAR var_88[30];
	WCHAR Alphabet[] = L"BCDFGHJKMPQRTVWXY2346789";
	var_88[29] = 0;
	BYTE* cdKey = ((DIGITALPID*)lpDigitalPID)->abCdKey;
	for (DWORD j = 28; j < 29; j--) {
		DWORD eax = 0;
		BYTE* ptr = cdKey + 14;
		for (DWORD i = 15; i; i--, ptr--) {
			eax = eax * 0x100 + *ptr;
			*ptr = (BYTE)(eax / 24);
			eax = eax % 24;
		}
		var_88[j] = Alphabet[eax];
		if (j != 0 && j % 6 == 0) {
			var_88[--j] = L'-';
		}
	}
	struct {
		union {
			DIGITALPID PidStruc;
			BYTE Buffer[0x100];
		};
		WCHAR f100[24];
	} var_1D8;
	var_1D8.PidStruc.dwLength = sizeof(var_1D8.Buffer);
	PIDGenWType PIDGenW = (PIDGenWType)GetProcAddress(hDpcDll, WPAPidGenWImport);
	if (PIDGenW != NULL) {
	WCHAR String1[24] = {0};
	bool wasError = false;
	if (lpszMpc != NULL) {
		lstrcpyn(String1, lpszMpc, 6);
	} else {
		if (!MultiByteToWideChar(CP_ACP, 0, ((DIGITALPID*)lpDigitalPID)->szPid2, -1, String1, sizeof(String1) / sizeof(String1[0]))) {
			wasError = true;
		}
	}
	if (!wasError) {
	String1[5] = 0;
	WCHAR WideCharStr[16];
	if (MultiByteToWideChar(CP_ACP, 0, ((DIGITALPID*)lpDigitalPID)->szSku, -1, WideCharStr, sizeof(WideCharStr) / sizeof(WideCharStr[0]))) {
	WCHAR var_4C[8];
	if (MultiByteToWideChar(CP_ACP, 0, ((DIGITALPID*)lpDigitalPID)->szOemId, -1, var_4C, sizeof(var_4C) / sizeof(var_4C[0]))) {
	DWORD ret = PIDGenW(var_88, String1, WideCharStr, var_4C, 0, 0, 0, ((DIGITALPID*)lpDigitalPID)->dwKeyIdx & 1, var_1D8.f100, var_1D8.Buffer, 0, 0);
	if (ret != 0) {
		if (ret == 1) {
			return E_WPA_ERROR_B039;
		} else if (ret == 20) {
			return E_OUTOFMEMORY;
		} else {
			return E_FAIL;
		}
	}
	memcpy(lpDigitalPID, &var_1D8, cbDigitalPID);
	return S_OK;
	}}}}
	DWORD err = GetLastError();
	return HRESULT_FROM_WIN32(err);
}

typedef DWORD (STDAPICALLTYPE *PidCheckType)(LPBYTE lpbDigPid);
HRESULT sub_105DA03(HMODULE hDpcDll, LPBYTE lpDigitalPID, DWORD cbDigitalPID, LPWSTR lpszMpc) {
	HRESULT hr = E_FAIL;
	PidCheckType PidCheck = (PidCheckType)GetProcAddress(hDpcDll, WPAPidCheckImport);
	if (PidCheck != NULL) {
		DWORD check = PidCheck(lpDigitalPID);
		if (check != 0) {
			if (check == 6) {
				hr = E_OUTOFMEMORY;
			} else if (check == 1) {
				hr = E_WPA_ERROR_B039;
			}
		} else {
			hr = sub_105D75C(hDpcDll, lpDigitalPID, cbDigitalPID, lpszMpc);
			if (SUCCEEDED(hr)) {
				hr = S_OK;
			}	
		}
	} else {
		hr = HRESULT_FROM_WIN32(GetLastError());
	}
	return hr;
}

void __forceinline copy(PWSTR to, DWORD& offsetto, PCWSTR from, DWORD offsetfrom, DWORD count) {
	for (; count--; ) {
		to[offsetto++] = from[offsetfrom++];
	}
}

void sub_105DB4E(PWSTR arg_0, DWORD arg_4) {
	WCHAR String2[24];
	DWORD i = 0;
	copy(String2, i, arg_0, 0, 6);
	copy(String2, i, arg_0, 12, 3);
	//i = copy(String2, i, L"-", 0, 1);
	String2[i++] = L'-';
	String2[i++] = arg_0[15];
	copy(String2, i, arg_0, 18, 5);
	int eax = 0;
	int j;
	for (j = 0; j < 6; j++) {
		eax += String2[j + 10] - L'0';
	}
	_itow(7 - eax % 7, &String2[i], 10);
	i++;
	String2[i++] = L'-';
	DWORD x = arg_4 >> 1;
	PWSTR p = &String2[i];
	PWSTR* q = &p;
	_itow(x / 10, *q, 10);
	i++;
	p = &String2[i];
	_itow(x % 10, *q, 10);
	i++;
	for (j = 0; j < 3; j++)
	    String2[i++] = L'0';
	String2[23] = 0;
	lstrcpyn(arg_0, String2, lstrlen(arg_0) + 1);
}

typedef HRESULT (STDAPICALLTYPE *WPAGetProductChannelInfoType)(
	DWORD dwKeyIdx,
	DWORD dwChannelID,
	DWORD dwVersion,
	CWPAProductChannelInfoSigned* pChannelInfo);

HRESULT sub_105DE67(HMODULE hDpcDll, DWORD dwKeyIdx, DWORD dwChannelID, CWPAProductChannelInfo* pChannelInfo) {
	WPAGetProductChannelInfoType GetProductChannelInfo =
		(WPAGetProductChannelInfoType)GetProcAddress(hDpcDll, WPAGetProductChannelInfoImport);
	if (GetProductChannelInfo == NULL) {
		return HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND);
	}
	CWPAProductChannelInfoSigned ChannelInfo;
	HRESULT hr = GetProductChannelInfo(dwKeyIdx, dwChannelID, 2600, &ChannelInfo);
	if (SUCCEEDED(hr)) {
		CWPACryptHelper SigChecker;
		hr = SigChecker.sub_104FD06(byte_101A038, sizeof(byte_101A038), 1);
		if (SUCCEEDED(hr)) {
			hr = SigChecker.sub_10500FE(&ChannelInfo.Info, sizeof(ChannelInfo.Info), ChannelInfo.lpSignature, ChannelInfo.cbSignature);
			if (SUCCEEDED(hr)) {
				if (ChannelInfo.dwRecordIdx == ChannelInfo.Info.dwChannelInfoIdx) {
					*pChannelInfo = ChannelInfo.Info;
				} else {
					hr = E_FAIL;
				}
			}
		}
		if (ChannelInfo.cbSignature != 0) {
			HeapFree(GetProcessHeap(), 0, ChannelInfo.lpSignature);
		}
	}
	return hr;
}

HRESULT sub_105E080(HMODULE* phDpcDll) {
	*phDpcDll = NULL;
	WCHAR Buffer[0x112];
	DWORD nSysDirLen = GetSystemDirectory(Buffer, sizeof(Buffer) / sizeof(Buffer[0]));
	if (nSysDirLen == 0 || nSysDirLen + 15 >= sizeof(Buffer) / sizeof(Buffer[0])) {
		return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
	}
	lstrcat(Buffer, CWPAStringsDecryptor(word_1075A18, sizeof(word_1075A18) / sizeof(word_1075A18[0]), unk_1019768));
	*phDpcDll = LoadLibrary(Buffer);
	if (*phDpcDll == NULL) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
extern "C" void __declspec() End_Vspweb_Scp_Segment_2_2();
#ifdef _x86
void __declspec(naked) End_Vspweb_Scp_Segment_2_2() {
__asm {
                mov     ecx, 2
END_SCP_SEGMENT_2_2:
                mov     edx, 2
                retn
}
}
#endif
#pragma warning(pop)

extern "C" HRESULT sub_105E224(DWORD arg_0, LPVOID lpData, DWORD cbData) {
	AutoHKEY var_10;
	DWORD err = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		CWPAStringsDecryptor(word_1075A38, sizeof(word_1075A38) / sizeof(word_1075A38[0]), unk_1019768),
		0,
		KEY_READ,
		&var_10);
	if (err != ERROR_SUCCESS) {
		return HRESULT_FROM_WIN32(err);
	}
	DWORD Type = (arg_0 == 2) ? REG_SZ : REG_BINARY;
	err = RegQueryValueEx(var_10,
		arg_0 == 2
			? CWPAStringsDecryptor(word_1075A98, sizeof(word_1075A98) / sizeof(word_1075A98[0]), unk_1019768)
			: CWPAStringsDecryptor(word_1075AB0, sizeof(word_1075AB0) / sizeof(word_1075AB0[0]), unk_1019768),
		NULL,
		&Type,
		(LPBYTE)lpData,
		&cbData);
	return HRESULT_FROM_WIN32(err);
}

extern "C" HRESULT sub_105E511(DWORD arg_0, LPVOID lpData, DWORD cbData) {
	AutoHKEY var_10;
	DWORD err = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		CWPAStringsDecryptor(word_1075A38, sizeof(word_1075A38) / sizeof(word_1075A38[0]), unk_1019768),
		0,
		KEY_WRITE,
		&var_10);
	if (err != ERROR_SUCCESS) {
		return HRESULT_FROM_WIN32(err);
	}
	DWORD Type = (arg_0 == 2) ? REG_SZ : REG_BINARY;
	err = RegSetValueEx(var_10,
		arg_0 == 2
			? CWPAStringsDecryptor(word_1075A98, sizeof(word_1075A98) / sizeof(word_1075A98[0]), unk_1019768)
			: CWPAStringsDecryptor(word_1075AB0, sizeof(word_1075AB0) / sizeof(word_1075AB0[0]), unk_1019768),
		NULL,
		Type,
		(LPBYTE)lpData,
		cbData);
	return HRESULT_FROM_WIN32(err);
}

HRESULT sub_105E81B(PWSTR lpszPid2, DWORD cchPid2, PDWORD pdwKeyIdx, PDWORD pdwChannelID, PBOOL pfOem, CWPAProductChannelInfo* pChannelInfo) {
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_2_1_0_10_00_00 ; void const * * ScpProtectedData_2_1_0_10_00_00
                pop     eax
                cmp     eax, offset Begin_Vspweb_Scp_Segment_2_2 ; Begin_Vspweb_Scp_Segment_2_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_2_2 ; End_Vspweb_Scp_Segment_2_2(void)
	}
#endif
	WPADummy();
	if (pdwKeyIdx == NULL || pdwChannelID == NULL || pfOem == NULL) {
		return E_INVALIDARG;
	}
	*pfOem = FALSE;
	*pdwKeyIdx = 0;
	*pdwChannelID = 0;
	ZeroMemory(lpszPid2, cchPid2 * sizeof(WCHAR));
	union {
		DIGITALPID Pid;
		BYTE Buffer[0x100];
	} var_110;
	ZeroMemory(&var_110, sizeof(var_110));
	HRESULT hr = sub_105E224(3, var_110.Buffer, sizeof(var_110.Buffer));
	if (FAILED(hr)) {
		return hr;
	}
	HMODULE hDpcDll;
	hr = sub_105E080(&hDpcDll);
	if (FAILED(hr)) {
		return hr;
	}
	hr = sub_105DA03(hDpcDll, var_110.Buffer, sizeof(var_110.Buffer), NULL);
	if (SUCCEEDED(hr)) {
		*pdwKeyIdx = var_110.Pid.dwKeyIdx;
		if (!MultiByteToWideChar(CP_ACP, 0, var_110.Pid.szPid2, -1, lpszPid2, cchPid2)) {
			FreeLibrary(hDpcDll);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (!wcsncmp(&lpszPid2[5], L"-OEM-", 5)) {
			*pfOem = TRUE;
		}
		WCHAR String1[4];
		lstrcpyn(String1, &lpszPid2[*pfOem ? 12 : 6], 4);
		String1[3] = 0;
		*pdwChannelID = _wtol(String1);
		if (pChannelInfo != NULL) {
			hr = sub_105DE67(hDpcDll, *pdwKeyIdx, *pdwChannelID, pChannelInfo);
		}
	}
	FreeLibrary(hDpcDll);
	return hr;
}

HRESULT sub_105EAF9(PWSTR lpszPid2, DWORD cchPid2) {
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_2_1_0_10_00_00 ; void const * * ScpProtectedData_2_1_0_10_00_00
                pop     eax
                cmp     eax, offset Begin_Vspweb_Scp_Segment_2_2 ; Begin_Vspweb_Scp_Segment_2_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_2_2 ; End_Vspweb_Scp_Segment_2_2(void)
	}
#endif
	WPADummy();
	if (cchPid2 < 24) {
		return HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
	}
	DWORD dwKeyIdx = 0;
	DWORD dwChannelID = 0;
	BOOL fOem = FALSE;
	HRESULT hr = sub_105E81B(lpszPid2, cchPid2, &dwKeyIdx, &dwChannelID, &fOem, NULL);
	if (SUCCEEDED(hr) && fOem) {
		sub_105DB4E(lpszPid2, dwKeyIdx);
	}
	return hr;
}

extern "C" HRESULT GetFullPKAndHash(LPWSTR lpProductKey, DWORD cbProductKey, LPBYTE lpHash, DWORD cbHash) {
	WCHAR ProductKeyBuf[30];
	if (lpProductKey == NULL) {
		lpProductKey = ProductKeyBuf;
		cbProductKey = sizeof(ProductKeyBuf);
	}
	BYTE var_1E4[0x100];
	HRESULT hr = sub_105E224(3, var_1E4, sizeof(var_1E4));
	if (FAILED(hr)) {
		return hr;
	}
	if ((cbProductKey & ~1) >= 30 * sizeof(WCHAR)) {
		DIGITALPID* pid = (DIGITALPID*)var_1E4;
		WCHAR szAlphabet[] = L"BCDFGHJKMPQRTVWXY2346789";
		lpProductKey[29] = 0;
		for (DWORD j = 28; j < 29; j--) {
			DWORD eax = 0;
			for (DWORD i = 14; i < 15; i--) {
				eax = eax * 0x100 + pid->abCdKey[i];
				pid->abCdKey[i] = (BYTE)(eax / 24);
				eax = eax % 24;
			}
			lpProductKey[j] = szAlphabet[eax];
			if (j != 0 && j % 6 == 0) {
				lpProductKey[--j] = L'-';
			}
		}
		A_SHA_CTX ShaContext;
		A_SHAInit(&ShaContext);
		A_SHAUpdate(&ShaContext, (BYTE*)lpProductKey, cbProductKey);
		A_SHAFinal(&ShaContext, lpHash);
		return ERROR_SUCCESS;
	} else {
		return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
	}
}
