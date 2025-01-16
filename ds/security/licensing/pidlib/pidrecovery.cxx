#include "precomp.h"
#pragma hdrstop
#include <ntregapi.h>
#include "../include/autoptr.h"
#include "../include/trivialencrypt.h"
#include "../include/digpid.h"
#include "../include/keyexists.h"
#include "../lib/basex.h"
#include "pidutil.h"

// L"ProductID"
WCHAR szBackupProductID[] = {0x653C,0x113E,0xC741,0x1575,0xEB61,0xC26E,0x516C,0x10F0,0xE3B2,0x0EFC,0x7756,0x5F92};
// L"DigitalProductID"
WCHAR szBackupDigitalProductID[] = {0x1B00,0xEA43,0x3531,0x1E66,0x8DDA,0x5DD8,0xAA24,0x7BDE,0xF8A7,0x9A8C,0xE1F1,0xADCB,0x8FFF,0x12C4,0xADC1,0xDA46,0x5AAF,0x8142,0x7CE2};
//extern __declspec(selectany) const wchar_t aSSS[] = L"%s%s-%s";
const wchar_t aSystemWpa[] = L"System\\WPA\\";
//extern __declspec(selectany) const wchar_t aKey[] = L"Key";
extern "C" const wchar_t aKey[];
const void* ScpProtectedData_10_1_0_10_00_00 = &aSystemWpa;

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() Begin_Vspweb_Scp_Segment_10_2();
#endif
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_10_2() {
__asm {
                mov     eax, 0Ah
BEGIN_SCP_SEGMENT_10_2_0_10_00_00:
                mov     ebx, 2
                retn
}
}
#endif
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() End_Vspweb_Scp_Segment_10_2();
#endif
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_10_2() {
__asm {
                mov     ecx, 0Ah
END_SCP_SEGMENT_10_2:
                mov     edx, 2
                retn
}
}
#endif
#pragma warning(pop)

extern "C" HRESULT sub_105ED41(PCWSTR lpSubKey, DWORD arg_4, LPVOID lpData, DWORD cbData) {
	AutoHKEY var_10;
	DWORD err = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		lpSubKey,
		0,
		KEY_READ,
		&var_10);
	if (err != ERROR_SUCCESS) {
		return HRESULT_FROM_WIN32(err);
	}
	DWORD Type = (arg_4 == 2) ? REG_SZ : REG_BINARY;
	err = RegQueryValueEx(var_10,
		arg_4 == 2
			? CWPAStringsDecryptor(szBackupProductID, sizeof(szBackupProductID) / sizeof(szBackupProductID[0]), unk_1019768)
			: CWPAStringsDecryptor(szBackupDigitalProductID, sizeof(szBackupDigitalProductID) / sizeof(szBackupDigitalProductID[0]), unk_1019768),
		NULL,
		&Type,
		(LPBYTE)lpData,
		&cbData);
	return HRESULT_FROM_WIN32(err);
}

extern "C" HRESULT sub_105EFAA(DWORD arg_0, PCWSTR lpSubKey, LPVOID lpData, DWORD cbData) {
	DWORD dwDisposition;
	AutoHKEY var_10;
	DWORD err = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		lpSubKey,
		0,
		NULL,
		0,
		KEY_ALL_ACCESS,
		NULL,
		&var_10,
		&dwDisposition);
	if (err != ERROR_SUCCESS) {
		return HRESULT_FROM_WIN32(err);
	}
	DWORD Type = (arg_0 == 2) ? REG_SZ : REG_BINARY;
	err = RegSetValueEx(var_10,
		arg_0 == 2
			? CWPAStringsDecryptor(szBackupProductID, sizeof(szBackupProductID) / sizeof(szBackupProductID[0]), unk_1019768)
			: CWPAStringsDecryptor(szBackupDigitalProductID, sizeof(szBackupDigitalProductID) / sizeof(szBackupDigitalProductID[0]), unk_1019768),
		NULL,
		Type,
		(LPBYTE)lpData,
		cbData);
	return HRESULT_FROM_WIN32(err);
}

struct CWPABackupKeyNameGeneratorInput {
	WORD field_0;
	WORD field_2;
	DWORD field_4;
	DWORD field_8;
};

extern "C" BOOL GetKeyName(LPWSTR lpszResult, DWORD dwResultSize, LPWSTR lpszPrefix, DWORD arg_C) {
	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*)&VersionInfo);
	CWPABackupKeyNameGeneratorInput BinarySuffix;
	ZeroMemory(&BinarySuffix, sizeof(BinarySuffix));
	BinarySuffix.field_2 = 0xE7A;
	BinarySuffix.field_8 = 6;
	BinarySuffix.field_4 = arg_C;
	if (VersionInfo.wSuiteMask & VER_SUITE_PERSONAL || VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) {
		BinarySuffix.field_0 = 1;
	} else {
		BinarySuffix.field_0 = 0;
	}
	WPAEncrypt((LPBYTE)&BinarySuffix, sizeof(BinarySuffix), dword_1019778);
	CWPABigNumBase24Converter Converter;
	AutoHeapPtr<WCHAR> lpszSuffix;
	Converter.CalculateDigitCountAndByteSize(sizeof(BinarySuffix) * 8);
	DWORD err = Converter.ConvertByteDataToWideString((LPBYTE)&BinarySuffix, &lpszSuffix);
	if (err != ERROR_SUCCESS) {
		return FALSE;
	}
	lpszResult[dwResultSize - 1] = 0;
	if (_snwprintf(lpszResult, dwResultSize - 1, L"%s%s-%s", aSystemWpa, lpszPrefix, (WCHAR*)lpszSuffix) < 0) {
		return FALSE;
	}
	return TRUE;
}

extern "C" HRESULT GetLastRegKeyName(PWSTR lpszName, DWORD cchName, PDWORD arg_8) {
	DWORD idx = 0;
	ZeroMemory(lpszName, MAX_PATH * sizeof(lpszName[0]));
	WCHAR String2[MAX_PATH];
	while (GetKeyName(String2, MAX_PATH, L"Key", idx)) {
		if (!WPAKeyExists(HKEY_LOCAL_MACHINE, String2)) {
			*arg_8 = idx;
			return S_OK;
		}
		++idx;
		lstrcpyn(lpszName, String2, cchName);
	}
	return E_FAIL;
}

extern "C" HRESULT RestorePIDRegValues() {
	WCHAR var_33C[MAX_PATH];
	union {
		DIGITALPID Pid;
		BYTE Buffer[0x100];
	} var_134;
	BYTE var_34[0x30];
	DWORD var_4 = 0;
	HRESULT hr = GetLastRegKeyName(var_33C, MAX_PATH, &var_4);
	if (FAILED(hr) || var_4 == 0) {
		return hr;
	}
	ZeroMemory(&var_134, sizeof(var_134));
	hr = sub_105ED41(var_33C, 3, var_134.Buffer, sizeof(var_134));
	if (FAILED(hr)) {
		return hr;
	}
	hr = sub_105ED41(var_33C, 2, var_34, sizeof(var_34));
	if (FAILED(hr)) {
		return hr;
	}
	hr = sub_105E511(2, var_34, sizeof(var_34));
	if (FAILED(hr)) {
		return hr;
	}
	hr = sub_105E511(3, var_134.Buffer, var_134.Pid.dwLength);
	return hr;
}

extern "C" int IsAlreadyBackedup(LPBYTE lpDigitalPid, DWORD cbDigitalPid, PDWORD arg_8, PBOOL arg_C) {
	*arg_8 = 0;
	*arg_C = FALSE;
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_10_1_0_10_00_00 ; void const * * ScpProtectedData_10_1_0_10_00_00
                pop     eax
                cmp     eax, offset Begin_Vspweb_Scp_Segment_10_2 ; Begin_Vspweb_Scp_Segment_10_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_10_2 ; End_Vspweb_Scp_Segment_10_2(void)
	}
#endif
	WCHAR var_308[MAX_PATH];
	HRESULT hr = GetLastRegKeyName(var_308, MAX_PATH, arg_8);
	if (FAILED(hr)) {
		return hr;
	}
	if (!*arg_8) {
		return S_OK;
	}
	union {
		DIGITALPID Pid;
		BYTE Buffer[0x100];
	} var_100;
	ZeroMemory(&var_100, sizeof(var_100));
	hr = sub_105ED41(var_308, 3, var_100.Buffer, sizeof(var_100));
	if (FAILED(hr)) {
		return hr;
	}
	if (0 == memcmp(var_100.Pid.abCdKey, ((DIGITALPID*)lpDigitalPid)->abCdKey, sizeof(var_100.Pid.abCdKey))) {
		*arg_C = TRUE;
	}
	return S_OK;
}

extern "C" HRESULT BackupPIDRegValues() {
	union {
		DIGITALPID Pid;
		BYTE Buffer[0x100];
	} var_13C;
	ZeroMemory(&var_13C, sizeof(var_13C));
	HRESULT hr = sub_105E224(3, &var_13C, sizeof(var_13C));
	if (FAILED(hr)) {
		return hr;
	}
	BYTE var_3C[48];
	hr = sub_105E224(2, &var_3C, sizeof(var_3C));
	if (FAILED(hr)) {
		return hr;
	}
	DWORD var_8 = 0;
	BOOL var_4 = 0;
	DWORD tmp;
	hr = IsAlreadyBackedup(var_13C.Buffer, sizeof(var_13C), &var_8, &var_4);
	if (FAILED(hr)) {
		return hr;
	}
	if (!var_4) {
		WCHAR var_344[MAX_PATH];
		if (!GetKeyName(var_344, MAX_PATH, L"Key", var_8)) {
			return E_FAIL;
		}
		hr = sub_105EFAA(2, var_344, &var_3C, sizeof(var_3C));
		if (FAILED(hr)) {
			return hr;
		}
		hr = sub_105EFAA(3, var_344, var_13C.Buffer, sizeof(var_13C));
		if (FAILED(hr)) {
			return hr;
		}
		tmp = 0xE7A;
		NtLockProductActivationKeys(&tmp, NULL);
	}
	return S_OK;
}
