#include "precomp.h"
#pragma hdrstop

void checkstatus_do_nothing();
void checkstatus_do_nothing2();
void checkstatus_do_nothing3();
void checkstatus_do_nothing4();

#include <ntlsa.h>
#include <winsta.h>
#include <psapi.h>
#include <rpc.h>
#include <wincrypt.h>
#include <stddef.h>
#include <xutility>

#include "../lib/lichwid.h"
#include "../liclib/bios.h"
#include "../liclib/bl.h"
#include "../liclib/crypthelper.h"
#include "../pidlib/pidrecovery.h"
#include "../pidlib/pidutil.h"
#include "times.h"
#include "regtime.h"
#include "rearm.h"
#include "../include/dummy.h"
#include "../include/fusion.h"
#include "../include/errors.h"
#include "checkstatus.h"

const __int64 qword_1018ED0 = 10000000;
const __int64 qword_1018ED8 = 600000000;
const __int64 qword_1018EE0 = 36000000000;
const __int64 qword_1018EE8 = 864000000000;
const __int64 qword_1018EF0 = 1440;
const __int64 qword_1018EF8 = 60;
const BYTE byte_1018F00[9] = {0xC0, 0x10, 0x14, 0xF4, 0xB3, 0x78, 0x34, 0x29, 0x40};
extern const DWORD dword_1018F0C[][3] = {
	{30, 15, 3},
	{14, 1, 1},
	{0, 0, 1},
};
extern const DWORD dword_1018F30[][3] = {
	{90, 31, 30},
	{30, 15, 3},
	{14, 1, 1},
	{0, 0, 1},
};
extern const DWORD dword_1018F60 = 4;

// L"LicenseInfo"
WORD unk_1075168[] = {0x8921,0xEB88,0x7CB3,0xA4D3,0xB09C,0xBF44,0x4861,0xF726,0x4B28,0x3E1B,0x2B3D,0xBA0A,0xD4E5,0xB80A,0,0};
// L"Software\\Microsoft\\Windows NT\\CurrentVersion"
WORD unk_1075188[] = {0x2CDE,0xCDBD,0xA402,0xC5A3,0x0A36,0xDA5C,0xA5DF,0x03F5,0xF5B2,0xA065,0xDBE2,0x4086,0x03F4,0x2BDA,0x0E37,0x56C1,0x3BBB,0x76B0,0x2D1C,0x978A,0xF494,0x91D4,0x99E1,0x3EBD,0xE952,0x041D,0x77CD,0x30D6,0x8B22,0x919B,0xD9DE,0x18FF,0xB040,0xA119,0xA1E5,0xE240,0xF925,0x5DB3,0xC64B,0x81EE,0x5F65,0xC290,0xC255,0x79DC,0xF720,0x4B0A,0xCF9D,0};
// L"Software\\Microsoft\\Windows NT\\CurrentVersion\\WPAEvents"
WORD unk_10751E8[] = {0x2CDE,0xCDBD,0xA402,0xC5A3,0x0A36,0xDA5C,0xA5DF,0x03F5,0xF5B2,0xA065,0xDBE2,0x4086,0x03F4,0x2BDA,0x0E37,0x56C1,0x3BBB,0x76B0,0x2D1C,0x978A,0xF494,0x91D4,0x99E1,0x3EBD,0xE952,0x041D,0x77CD,0x30D6,0x8B22,0x919B,0xD9DE,0x18FF,0xB040,0xA119,0xA1E5,0xE240,0xF925,0x5DB3,0xC64B,0x81EE,0x9965,0xBF82,0x3DC5,0x0D32,0x1B91,0xCE7D,0xDD95,0x8BDD,0xF3ED,0xF88D,0x79CF,0x5A9A,0x1F76,0x035B,0x4A03,0xA6A8,0x4676,0,0,0};
// L"Software\\Microsoft\\Windows NT\\CurrentVersion\\RRWPA"
WCHAR szRRWPA[] = {0x2CDE,0xCDBD,0xA402,0xC5A3,0x0A36,0xDA5C,0xA5DF,0x03F5,0xF5B2,0xA065,0xDBE2,0x4086,0x03F4,0x2BDA,0x0E37,0x56C1,0x3BBB,0x76B0,0x2D1C,0x978A,0xF494,0x91D4,0x99E1,0x3EBD,0xE952,0x041D,0x77CD,0x30D6,0x8B22,0x919B,0xD9DE,0x18FF,0xB040,0xA119,0xA1E5,0xE240,0xF925,0x5DB3,0xC64B,0x81EE,0x9965,0x3D82,0x44F2,0xBF0A,0xBA6E,0x4880,0x9943,0x637E,0x7FA7,0x9480,0x17BA,0x8AF0,0x4B41,0x0000,0x0000,0x0000};
WCHAR szRWPA[] = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\WPAReminders";
WCHAR szSetRem[] = L"DisableReminder";
// L"RemoveReminder"
WCHAR szActDone[] = {0xAF42,0x6280,0xB023,0xD491,0xB2E8,0x50A1,0xCB10,0x0F27,0x1AD3,0xB128,0x8369,0xDA94,0x08EE,0xFAD0,0x98BA,0xD905,0xA0CD,0};
// L"\\licdll.dll"
WCHAR unk_1075388[] = {0x94E4,0xF776,0x5141,0x1602,0x1348,0x01FF,0x4EF2,0xCAAF,0x368D,0x9A70,0x4358,0x8AE6,0x0064,0x818D};
// L"\\dpcdll.dll"
WCHAR unk_10753A4[] = {0x2D02,0x48FC,0x03FA,0xC38B,0xE29B,0x31FC,0xAA8C,0x9CF7,0x2732,0x1633,0x57D0,0xEA49,0xFE7A,0x95B6};
// L"\\xpsp1res.dll"
WCHAR wszXpSp1Resdll[] = {0x027F,0x0ECB,0x1CF6,0x3EFE,0xAF48,0x1726,0xC17A,0x5965,0x3C4D,0x0ABA,0xFEB9,0x93ED,0xA752,0xC406,0xB04E,0x8550};
const void* ScpProtectedData_1_11_0_10_00_00[] = {
&byte_1018F00,
&dword_1018F0C,
&dword_1018F30,
&dword_1018F60,
&unk_10751E8,
&unk_1075188,
&unk_1075168,
&unk_1075388,
&unk_10753A4,
wszXpSp1Resdll,
&qword_1018ED0,
&qword_1018ED8,
&qword_1018EE0,
&qword_1018EE8,
&qword_1018EF0,
&qword_1018EF8,
};

DWORD dword_1075D18 = 0;
HWND hWnd = NULL;
HANDLE hThread = NULL;
DWORD dword_1075D24 = 0;
DWORD dword_1075D28 = 0;
DWORD dword_1075D2C = 0;

#include "checkstatus-x1.inc"

extern int GetSafeMode(DWORD* arg_0) {
	ULONG var_4, var_8;
	var_4 = 0xE7A;
	NTSTATUS ntstatus = NtLockProductActivationKeys(&var_4, &var_8);
	HRESULT status = HRESULT_FROM_NT(ntstatus);
	*arg_0 = 0;
	if (FAILED(status)) {
		return status;
	}
	if (var_4 < 0xE69) {
		return E_WPA_KERNEL_TOO_OLD;
	}
	DWORD tmp = GetSystemMetrics(SM_CLEANBOOT);
	if (var_8 != tmp) {
		return E_WPA_GETSAFEMODE_HACKED;
	}
	*arg_0 = var_8;
	return S_OK;
}

#ifdef _X86_
#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
extern void __declspec() Begin_Vspweb_Scp_Segment_1_2();
/*
void __declspec(naked) Begin_Vspweb_Scp_Segment_1_2() {
__asm {
                mov     eax, 1
BEGIN_SCP_SEGMENT_1_2_0_10_00_00:
                mov     ebx, 2
                retn
}
}
*/
#pragma warning(pop)
#endif

ULONGLONG sub_104009E(const SYSTEMTIME* lpSystemTime) {
	FILETIME FileTime;
	SystemTimeToFileTime(lpSystemTime, &FileTime);
	return FileTime.dwHighDateTime * 0x100000000i64 + FileTime.dwLowDateTime;
}

SYSTEMTIME sub_104018D(ULONGLONG ullFileTime) {
	FILETIME FileTime;
	FileTime.dwHighDateTime = (DWORD)(ullFileTime >> 32);
	FileTime.dwLowDateTime = (DWORD)ullFileTime;
	SYSTEMTIME SystemTime;
	FileTimeToSystemTime(&FileTime, &SystemTime);
	return SystemTime;
}

bool operator==(const SYSTEMTIME& left, const SYSTEMTIME& right) {
	if (left.wYear == right.wYear
		&& left.wMonth == right.wMonth
		&& left.wDay == right.wDay
		&& left.wDayOfWeek == right.wDayOfWeek
		&& left.wHour == right.wHour
		&& left.wMinute == right.wMinute
		&& left.wSecond == right.wSecond
		&& left.wMilliseconds == right.wMilliseconds)
	{
		return true;
	} else {
		return false;
	}
}

bool sub_1040343(const SYSTEMTIME& left, const SYSTEMTIME& right);
bool operator<(const SYSTEMTIME& left, const SYSTEMTIME& right) {
	ULONGLONG LeftAsFileTime = sub_104009E(&left);
	ULONGLONG RightAsFileTime = sub_104009E(&right);
	return LeftAsFileTime < RightAsFileTime;
}

extern SYSTEMTIME sub_104046A(const SYSTEMTIME& left, const SYSTEMTIME& right);
extern SYSTEMTIME sub_10405A0(SYSTEMTIME& left, const SYSTEMTIME& right);
SYSTEMTIME operator-(const SYSTEMTIME& left, const SYSTEMTIME& right) {
	ULONGLONG leftNanoseconds = sub_104009E(&left);
	ULONGLONG rightNanoseconds = sub_104009E(&right);
	return sub_104018D(leftNanoseconds - rightNanoseconds);
}
SYSTEMTIME operator-=(SYSTEMTIME& left, const SYSTEMTIME& right) {
	SYSTEMTIME diff = left - right;
	left = diff;
	return left;
}

int sub_1040667(SYSTEMTIME* left, SYSTEMTIME* right) {
	ULONGLONG leftAsFileTime = sub_104009E(left);
	ULONGLONG rightAsFileTime = sub_104009E(right);
	if (rightAsFileTime > leftAsFileTime) {
		return (int)((rightAsFileTime - leftAsFileTime) / 864000000000i64);
	} else {
		return (int)((leftAsFileTime - rightAsFileTime) / 864000000000i64);
	}
}

ULONGLONG sub_10407CB(const SYSTEMTIME* Time1, const SYSTEMTIME* Time2) {
	ULONGLONG AsFileTime1 = sub_104009E(Time1);
	ULONGLONG AsFileTime2 = sub_104009E(Time2);
	if (AsFileTime2 > AsFileTime1) {
		return (AsFileTime2 - AsFileTime1) / 600000000;
	} else {
		return (AsFileTime1 - AsFileTime2) / 600000000;
	}
}

void sub_1040949(const TIME_FIELDS* TimeFields, SYSTEMTIME* SystemTime) {
	SystemTime->wYear = TimeFields->Year;
	SystemTime->wMonth = TimeFields->Month;
	SystemTime->wDay = TimeFields->Day;
	SystemTime->wDayOfWeek = TimeFields->Weekday;
	SystemTime->wHour = TimeFields->Hour;
	SystemTime->wMinute = TimeFields->Minute;
	SystemTime->wSecond = TimeFields->Second;
	SystemTime->wMilliseconds = TimeFields->Milliseconds;
}

HRESULT sub_10409FC(LPSYSTEMTIME lpSystemTime) {
	SYSTEM_TIMEOFDAY_INFORMATION SystemInformation;
	NTSTATUS status = NtQuerySystemInformation(SystemTimeOfDayInformation, &SystemInformation, sizeof(SystemInformation), NULL);
	if (!NT_SUCCESS(status)) {
		return HRESULT_FROM_NT(status);
	}
	TIME_FIELDS TimeFields;
	RtlTimeToTimeFields(&SystemInformation.CurrentTime, &TimeFields);
	SYSTEMTIME var_20;
	sub_1040949(&TimeFields, &var_20);
	GetSystemTime(lpSystemTime);
	if (sub_10407CB(&var_20, lpSystemTime) > 5) {
		return E_WPA_SYSTIME_HACKED;
	}
	return S_OK;
}

void sub_1040B54(CWPATimes* arg_0) {
	arg_0->dwSize = 0x38;
	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*)&VersionInfo);
	DWORD dwMask;
	if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
		dwMask = 0x10000;
	} else {
		dwMask = 0;
	}
	DWORD dwProductId = 0x80000E7A | dwMask;
	arg_0->dwProductId = dwProductId;
	sub_104E349(arg_0, offsetof(CWPATimes, Signature), arg_0->Signature);
	WPAEncrypt((LPBYTE)&arg_0->Signature, sizeof(arg_0->Signature), dword_1019778);
}

__forceinline bool WPAValidateTimes(CWPATimes* Data) {
	if (Data->dwSize == sizeof(*Data)) {
		OSVERSIONINFOEX VersionInfo;
		VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
		GetVersionEx((OSVERSIONINFO*)&VersionInfo);
		DWORD dwMask;
		if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			dwMask = 0x10000;
		} else {
			dwMask = 0;
		}
		DWORD dwProductId = 0x80000E7A | dwMask;
		if (Data->dwProductId == dwProductId) {
			return true;
		}
	}
	return false;
}

bool sub_1040D9D(CWPATimes* Data) {
	BYTE var_1C[16];
	sub_104E349(Data, offsetof(CWPATimes, Signature), var_1C);
	WPADecrypt(Data->Signature, sizeof(Data->Signature), dword_1019778);
	if (memcmp(var_1C, Data->Signature, sizeof(Data->Signature)) == 0) {
		if (WPAValidateTimes(Data)) {
			return true;
		}
	}
	return false;
}

class CWPAClass5 {
public:
    int sub_1040FFA(CWPALicenseManager* arg_0, CWPATimes* arg_4);
};

int CWPAClass5::sub_1040FFA(CWPALicenseManager* arg_0, CWPATimes* arg_4) {
	CWPATimes var_54 = *arg_4;
	BYTE var_1C[16];
	if (SUCCEEDED(GetPerMachine128BitSeed(var_1C))) {
		WPAEncrypt((PBYTE)&var_54, sizeof(var_54), var_1C);
	}
	DWORD err = arg_0->sub_1054285(0x33, &var_54, sizeof(var_54), TRUE);
	if (err) {
		return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
	}
	return S_OK;
}

static __forceinline void sub_10411F8_WriteResult(DWORD edi, PWSTR arg_0, PDWORD arg_8) {
	if (arg_0) {
		_itow(edi, arg_0, 10);
	}
	if (arg_8) {
		*arg_8 = edi;
	}
}

HRESULT sub_10411F8(PWSTR arg_0, DWORD arg_4, PDWORD arg_8) {
	if (arg_0) {
		ZeroMemory(arg_0, arg_4 * sizeof(WCHAR));
	}
	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	if (GetVersionEx((OSVERSIONINFO*)&VersionInfo)) {
		if (VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			sub_10411F8_WriteResult(55041, arg_0, arg_8);
		} else if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) {
			sub_10411F8_WriteResult(55039, arg_0, arg_8);
		} else if (VersionInfo.wSuiteMask & VER_SUITE_DATACENTER) {
			sub_10411F8_WriteResult(55037, arg_0, arg_8);
		} else if (VersionInfo.wProductType == VER_NT_WORKSTATION) {
			sub_10411F8_WriteResult(55034, arg_0, arg_8);
		} else if (VersionInfo.wProductType == VER_NT_SERVER) {
			sub_10411F8_WriteResult(55038, arg_0, arg_8);
		}
		return S_OK;
	} else {
		return HRESULT_FROM_WIN32(GetLastError());
	}
}

void FixupNewLine(PWSTR arg_0) {
	PWSTR p = wcsstr(arg_0, L"\\n");
	if (p) {
		p[0] = L' ';
		p[1] = L'\n';
	}
}

DWORD sub_10414F0(DWORD dwMessageId, LPWSTR* ppMessage, DWORD dwMaxSize, BOOL arg_C) {
	WCHAR Buffer[0x122];
	DWORD status = 0;
	HINSTANCE hLib = NULL;
	DWORD szSysDirSize = GetSystemDirectory(Buffer, sizeof(Buffer) / sizeof(Buffer[0]));
	if (!szSysDirSize) {
		return GetLastError();
	}
	DWORD szPathSize = arg_C ? 0x10 : 0xE;
	if (szSysDirSize + szPathSize + 1 >= sizeof(Buffer) / sizeof(Buffer[0])) {
		return ERROR_INSUFFICIENT_BUFFER;
	}
	if (arg_C) {
		lstrcat(Buffer, CWPAStringsDecryptor(wszXpSp1Resdll, 0x10, unk_1019768));
	} else {
		lstrcat(Buffer, CWPAStringsDecryptor(unk_1075388, 0xE, unk_1019768));
	}
	hLib = LoadLibraryEx(Buffer, NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (hLib) {
		*ppMessage = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwMaxSize * sizeof(WCHAR));
		if (!*ppMessage) {
			status = ERROR_OUTOFMEMORY;
		} else {
			if (arg_C) {
				if (FormatMessage(FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS, hLib, dwMessageId, 0, *ppMessage, dwMaxSize, NULL)) {
					FixupNewLine(*ppMessage);
				} else {
					status = GetLastError();
				}
			} else {
				if (!LoadString(hLib, dwMessageId, *ppMessage, dwMaxSize)) {
					status = GetLastError();
				}
			}
		}
	} else {
		*ppMessage = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WCHAR));
		if (!*ppMessage) {
			status = ERROR_OUTOFMEMORY;
		}
	}
	if (hLib) {
		FreeLibrary(hLib);
	}
	return status;
}

HRESULT sub_10417B4(DWORD arg_0, DWORD arg_4, PDWORD arg_8, PDWORD arg_C) {
	if (dword_1075D24 || WinStationIsHelpAssistantSession(0, 0xFFFFFFFF)) {
		*arg_8 = 2;
		return S_OK;
	}
	DWORD error;
	{
	LPWSTR lpCaption = NULL;
	LPWSTR lpText = NULL;
	error = sub_10414F0(0x66, &lpCaption, 0x40, FALSE);
	if (!error) {
		BOOL cbData_;
		{
		DWORD Data = 0;
		HKEY phkResult = NULL;
		DWORD Type = 0;
		DWORD cbData = 0;
		if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_READ, &phkResult)) {
			cbData = sizeof(Data);
			RegQueryValueEx(phkResult, L"ShutdownWithoutLogon", NULL, &Type, (LPBYTE)&Data, &cbData);
			RegCloseKey(phkResult);
		}
		// !IsActiveConsoleSession
		if (USER_SHARED_DATA->ActiveConsoleId != NtCurrentPeb()->SessionId) {
			Data = 0;
		}
		cbData_ = (Data == 0);
		}
		{
		BOOL edi = GetSystemMetrics(SM_CLEANBOOT) == 2;
		DWORD esi = cbData_ ? MB_YESNOCANCEL : MB_YESNO;
		DWORD eax;
		if (arg_0 && edi) {
			if (cbData_) {
				eax = 118;
				esi = MB_YESNO;
			} else {
				eax = 119;
				esi = MB_OK;
			}
		} else if (arg_4 & 4) {
			if (arg_0) {
				if (cbData_) {
					eax = 115;
				} else {
					eax = 103;
				}
			} else {
				eax = 104;
			}
		} else if (arg_0) {
			if (cbData_) {
				eax = 116;
			} else {
				eax = 106;
			}
		} else {
			eax = 107;
		}
		error = sub_10414F0(eax, &lpText, 0x800, FALSE);
		if (!error) {
			DWORD ret = Fusion_MessageBox(GetDesktopWindow(), lpText, lpCaption, MB_TOPMOST | MB_SYSTEMMODAL | MB_ICONERROR | (arg_0 ? esi : MB_OK));
			if (ret == IDYES) {
				if (!edi || !cbData_) {
					*arg_8 = 0;
				} else {
					*arg_8 = 3;
					*arg_C = 5;
				}
			} else if (ret == IDNO) {
				*arg_8 = 2;
			} else if (ret == IDOK) {
				*arg_8 = 2;
			} else if (ret == IDCANCEL) {
				*arg_8 = 3;
				*arg_C = 5;
			}
		}
		}
	}
	if (lpCaption) {
		HeapFree(GetProcessHeap(), 0, lpCaption);
	}
	if (lpText) {
		HeapFree(GetProcessHeap(), 0, lpText);
	}
	}
	return HRESULT_FROM_WIN32(error);
}

HRESULT sub_1041B36(DWORD arg_0, DWORD arg_4, DWORD arg_8) {
	LPWSTR lpMem = NULL;
	LPWSTR uType = NULL;
	DWORD error = sub_10414F0(0x66, &lpMem, 0x40, FALSE);
	if (!error) {
		error = sub_10414F0(arg_0, &uType, 0x800, arg_4);
		if (!error) {
			Fusion_MessageBox(GetDesktopWindow(), uType, lpMem, arg_8 | MB_TOPMOST | MB_SYSTEMMODAL);
		}
	}
	if (lpMem) {
		HeapFree(GetProcessHeap(), 0, lpMem);
	}
	if (uType) {
		HeapFree(GetProcessHeap(), 0, uType);
	}
	return HRESULT_FROM_WIN32(error);
}

void DisplayNagMessage() {
	sub_1041B36(4004, 1, 16);
}

DWORD sub_1041DE6(HANDLE hProcess, LPDWORD lpExitCode, DWORD dwMilliseconds) {
	DWORD var_4 = 0;
	BOOL var_8 = FALSE;
	MSG Msg;
	while (!var_8) {
		DWORD status = MsgWaitForMultipleObjects(1, &hProcess, FALSE, dwMilliseconds, QS_ALLINPUT);
		switch (status) {
		case WAIT_OBJECT_0:
			if (GetExitCodeProcess(hProcess, lpExitCode)) {
				var_4 = 0;
			} else {
				var_4 = GetLastError();
			}
			var_8 = TRUE;
			break;
		case WAIT_OBJECT_0 + 1:
			while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) != FALSE) {
				if (Msg.wParam == 8) {
					var_8 = TRUE;
					TerminateProcess(hProcess, 0);
					var_4 = ERROR_LOGIN_TIME_RESTRICTION;
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				} else {
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
			}
			break;
		case WAIT_TIMEOUT:
			*lpExitCode = WAIT_TIMEOUT;
			var_4 = ERROR_TIMEOUT;
			var_8 = TRUE;
			break;
		default:
			var_4 = GetLastError();
			var_8 = TRUE;
			break;
		}
	}
	return var_4;
}

HRESULT sub_104201C(HDESK arg_0, HDESK hDesktop, LPWSTR arg_8, LPVOID lpEnvironment, HANDLE hToken, DWORD arg_14) {
	WCHAR CommandLine[282];
	WCHAR Buffer[277];
	JOBOBJECT_BASIC_LIMIT_INFORMATION JobObjectInformation;
	STARTUPINFO StartupInfo;
	HANDLE hObject;
	PROCESS_INFORMATION ProcessInformation;
	DWORD SysDirLen = GetSystemDirectory(Buffer, 277);
	if (!SysDirLen || SysDirLen + 18 >= 277) {
		return E_FAIL;
	}
	lstrcat(Buffer, L"\\oobe\\msoobe.exe");
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	ZeroMemory(&ProcessInformation, sizeof(ProcessInformation));
	wsprintf(CommandLine, L"%s %s", Buffer, L"/a");
	hObject = CreateJobObject(NULL, L"OOBE Job");
	if (!hObject) {
		return E_FAIL;
	}
	ZeroMemory(&JobObjectInformation, sizeof(JobObjectInformation));
	JobObjectInformation.LimitFlags = JOB_OBJECT_LIMIT_ACTIVE_PROCESS;
	JobObjectInformation.ActiveProcessLimit = 1;
	if (!SetInformationJobObject(hObject, JobObjectBasicLimitInformation, &JobObjectInformation, sizeof(JobObjectInformation))) {
		CloseHandle(hObject);
		return E_FAIL;
	}
	if (!SwitchDesktop(hDesktop)) {
		DWORD err = GetLastError();
		CloseHandle(hObject);
		return HRESULT_FROM_WIN32(err);
	}
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.lpDesktop = arg_8;
	StartupInfo.cb = sizeof(StartupInfo);
	StartupInfo.lpTitle = NULL;
	StartupInfo.dwXSize = StartupInfo.dwYSize = 0;
	StartupInfo.dwX = StartupInfo.dwY = 0;
	StartupInfo.dwFlags = 0;
	StartupInfo.wShowWindow = SW_SHOW;
	StartupInfo.lpReserved2 = NULL;
	StartupInfo.cbReserved2 = 0;
	if (CreateProcessAsUser(
		hToken,
		Buffer,
		CommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_UNICODE_ENVIRONMENT | CREATE_SUSPENDED,
		lpEnvironment,
		NULL,
		&StartupInfo,
		&ProcessInformation))
	{
		DWORD edi;
		if (AssignProcessToJobObject(hObject, ProcessInformation.hProcess)) {
			ResumeThread(ProcessInformation.hThread);
			DWORD tmp = 0;
			edi = sub_1041DE6(ProcessInformation.hProcess, &tmp, 3600000);
		} else {
			edi = GetLastError();
			TerminateProcess(ProcessInformation.hProcess, 5);
		}
		CloseHandle(ProcessInformation.hThread);
		CloseHandle(ProcessInformation.hProcess);
		CloseHandle(hObject);
		SwitchDesktop(arg_0);
		if (edi) {
			return HRESULT_FROM_WIN32(edi);
		}
		return S_OK;
	} else {
		CloseHandle(hObject);
		SwitchDesktop(arg_0);
		return E_FAIL;
	}
}

HRESULT sub_10423EA(DWORD arg_0) {
	if (dword_1075D24 || WinStationIsHelpAssistantSession(0, 0xFFFFFFFF)) {
		return S_OK;
	}
	LPWSTR lpCaption = NULL;
	LPWSTR Format = NULL;
	LPWSTR lpMem = NULL;
	DWORD var_C = sub_10414F0(0x66, &lpCaption, 0x40, 0);
	if (!var_C) {
		var_C = sub_10414F0(0x6F, &Format, 0x800, 0);
		lpMem = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x840 * sizeof(WCHAR));
		if (lpMem) {
			lpMem[0x83F] = 0;
			_snwprintf(lpMem, 0x83F, Format, arg_0);
			Fusion_MessageBox(GetDesktopWindow(), lpMem, lpCaption, MB_TOPMOST | MB_SYSTEMMODAL | MB_ICONWARNING | MB_OK);
		}
	}
	if (lpCaption) {
		HeapFree(GetProcessHeap(), 0, lpCaption);
	}
	if (Format) {
		HeapFree(GetProcessHeap(), 0, Format);
	}
	if (lpMem) {
		HeapFree(GetProcessHeap(), 0, lpMem);
	}
	return S_OK;
}

HRESULT sub_10425F4(DWORD arg_0, DWORD arg_4, PDWORD arg_8, DWORD arg_C, PDWORD arg_10) {
	if (dword_1075D24 || WinStationIsHelpAssistantSession(0, 0xFFFFFFFF)) {
		*arg_8 = 1;
		return S_OK;
	}
	LPWSTR lpCaption = NULL;
	LPWSTR Format = NULL;
	LPWSTR lpMem = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x840 * sizeof(WCHAR));
	if (!lpMem) {
		*arg_8 = 1;
		return S_OK;
	}
	DWORD var_C = sub_10414F0(0x66, &lpCaption, 0x40, 0);
	if (!var_C) {
		if (arg_0) {
			DWORD _arg_0 = (GetSystemMetrics(SM_CLEANBOOT) != 2);
			DWORD eax;
			if (_arg_0) {
				if (arg_4) {
					eax = 4001;
				} else {
					eax = 108;
				}
			} else {
				if (arg_4) {
					eax = 4000;
				} else {
					eax = 117;
				}
			}
			var_C = sub_10414F0(eax, &Format, 0x800, arg_4);
			if (!var_C) {
				lpMem[0x83F] = 0;
				_snwprintf(lpMem, 0x83F, Format, arg_C);
				DWORD MsgBoxResult = Fusion_MessageBox(GetDesktopWindow(), lpMem, lpCaption, MB_TOPMOST | MB_SYSTEMMODAL | MB_ICONWARNING | MB_YESNO);
				if (MsgBoxResult == IDYES) {
					if (_arg_0) {
						*arg_8 = 0;
					} else {
						*arg_8 = 3;
						*arg_10 = 5;
					}
				} else if (MsgBoxResult == IDNO) {
					*arg_8 = 1;
				}
			} else {
				*arg_8 = 1;
			}
		} else {
			DWORD eax;
			if (arg_4)
				eax = 4003;
			else
				eax = 109;
			var_C = sub_10414F0(eax, &Format, 0x800, arg_4);
			if (!var_C) {
				lpMem[0x83F] = 0;
				_snwprintf(lpMem, 0x83F, Format, arg_C);
				Fusion_MessageBox(GetDesktopWindow(), lpMem, lpCaption, MB_TOPMOST | MB_SYSTEMMODAL | MB_ICONINFORMATION | MB_OK);
			}
			*arg_8 = 1;
		}
	} else {
		*arg_8 = 1;
	}
	if (lpCaption) {
		HeapFree(GetProcessHeap(), 0, lpCaption);
	}
	if (Format) {
		HeapFree(GetProcessHeap(), 0, Format);
	}
	HeapFree(GetProcessHeap(), 0, lpMem);
	return HRESULT_FROM_WIN32(var_C);
}

static HRESULT __forceinline WPACanUseEmbeddedLicense() {
		OSVERSIONINFOEX VersionInformation;
			ZeroMemory(&VersionInformation, sizeof(VersionInformation));
			VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
			VersionInformation.wSuiteMask = VER_SUITE_EMBEDDEDNT;
			ULONGLONG ConditionMask = 0;
			ConditionMask = VerSetConditionMask(ConditionMask, VER_SUITENAME, VER_AND);
			if (!VerifyVersionInfo(&VersionInformation, VER_SUITENAME, ConditionMask)) {
				// embedded license only valid on embedded NT
				return HRESULT_FROM_WIN32(ERROR_OLD_WIN_VERSION);
			}
			ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
			if (!GetDiskFreeSpaceEx(NULL, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes)) {
				return E_ACCESSDENIED;
			}
			// 1Gb
			if ((ULONGLONG)1 * 1024 * 1024 * 1024 < TotalNumberOfBytes.QuadPart && !sub_104F0CA(WPAFileType1, 0, 0, 0, 0, 0)) {
				return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
			}
			WCHAR SystemDirectory[MAX_PATH];
			if (!GetSystemDirectory(SystemDirectory, MAX_PATH)) {
				return HRESULT_FROM_WIN32(GetLastError());
			}
				WCHAR Dest[MAX_PATH];
				Dest[MAX_PATH - 1] = 0;
				if (_snwprintf(Dest, MAX_PATH - 1, L"%s\\EmbdTrst.dll", SystemDirectory) < 0) {
					return HRESULT_FROM_WIN32(0x502); // ERROR_STACK_BUFFER_OVERRUN
				}
					HMODULE hEmbdTrst = LoadLibrary(Dest);
					if (!hEmbdTrst) {
						return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
					}
					typedef NTSTATUS (WINAPI *ImageOkToRunOnEmbeddedNT_t)(LPCWSTR);
					ImageOkToRunOnEmbeddedNT_t ImageOkToRunOnEmbeddedNT = (ImageOkToRunOnEmbeddedNT_t)GetProcAddress(hEmbdTrst, "ImageOkToRunOnEmbeddedNT");
					if (!ImageOkToRunOnEmbeddedNT) {
						return E_ACCESSDENIED;
					}
					if (!ImageOkToRunOnEmbeddedNT(NULL)) {
						return E_ACCESSDENIED;
					}
			return S_OK;
}

static HRESULT __forceinline WPACanUseVolumeLicense() {
		OSVERSIONINFOEX VersionInformation;
			ZeroMemory(&VersionInformation, sizeof(VersionInformation));
			VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
			VersionInformation.wProductType = VER_NT_WORKSTATION;
			VersionInformation.wSuiteMask = VER_SUITE_PERSONAL;
			ULONGLONG ConditionMask = 0;
			ConditionMask = VerSetConditionMask(ConditionMask, VER_SUITENAME, VER_AND);
			ConditionMask = VerSetConditionMask(ConditionMask, VER_PRODUCT_TYPE, VER_EQUAL);
			if (VerifyVersionInfo(&VersionInformation, VER_SUITENAME | VER_PRODUCT_TYPE, ConditionMask)) {
				// VL license invalid for Home edition
				return E_WPA_VOLUME_LICENSE_BLOCKED;
			}
			if (CheckNewSKUVLHack(L"MediaCenter", L"Installed", 1)) {
				// VL license invalid if MediaCenter installed?
				return E_WPA_VOLUME_LICENSE_BLOCKED;
			}
			//HRESULT CheckLangStatus = WPAValidateSysLangForVolumeLicense();
			//if (FAILED(CheckLangStatus)) {
			//	return CheckLangStatus;
			//}
			HRESULT CheckLangStatus = S_OK;
			LANGID SystemLang = GetSystemDefaultUILanguage();
			if (PRIMARYLANGID(SystemLang) == LANG_RUSSIAN ||
				PRIMARYLANGID(SystemLang) == LANG_CHINESE && SUBLANGID(SystemLang) == SUBLANG_CHINESE_SIMPLIFIED)
			{
				// VL license invalid for Russians and Chinese
				return E_WPA_VOLUME_LICENSE_BLOCKED;
			}
				WCHAR shell32[] = L"shell32.dll";
				DWORD dwHandle;
				LPVOID pVersionInfo;
				DWORD dwVersionInfoSize = GetFileVersionInfoSize(shell32, &dwHandle);
				if (dwVersionInfoSize
					&& (pVersionInfo = HeapAlloc(GetProcessHeap(), 0, dwVersionInfoSize)))
				{
					PDWORD pLanguages;
					UINT dwLanguagesSize;
					if (GetFileVersionInfo(shell32, 0, dwVersionInfoSize, pVersionInfo)
						&& VerQueryValue(pVersionInfo, L"\\VarFileInfo\\Translation", (LPVOID*)&pLanguages, &dwLanguagesSize))
					{
						for (DWORD i = 0; i < dwLanguagesSize / 4; i++) {
							LANGID LangId = LOWORD(pLanguages[i]);
							if (PRIMARYLANGID(LangId) == LANG_RUSSIAN ||
								PRIMARYLANGID(LangId) == LANG_CHINESE && SUBLANGID(LangId) == SUBLANG_CHINESE_SIMPLIFIED)
							{
								// russian or chinese hackers are trying to pass their system as not-their
								CheckLangStatus = E_WPA_VOLUME_LICENSE_BLOCKED;
							}
						}
					}
					HeapFree(GetProcessHeap(), 0, pVersionInfo);
				}
				if (!sub_104F0CA(WPAFileType1, 0, 0, 0, 0, 0)) {
					return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
				}
					return CheckLangStatus;
}

void sub_1042932(CWPAProductChannelInfo* arg_0, DWORD arg_4, DWORD arg_8, PDWORD arg_C, PDWORD arg_10, bool* arg_14) {
	DWORD tmp;
	if (arg_0->dwLicenseType == 1) {
		*arg_14 = false;
		*arg_C = 0x7FFFFFFF;
		tmp = 0x7FFFFFFF;
		if (arg_0->dwDaysForEval != 0x7FFFFFFF) {
			if (arg_0->dwDaysForEval > arg_8) {
				tmp = arg_0->dwDaysForEval - arg_8;
			} else {
				tmp = 0;
			}
		}
		*arg_10 = tmp;
	} else if (arg_0->dwLicenseType == 0) {
		*arg_14 = true;
		*arg_C = 0;
		tmp = 0x7FFFFFFF;
		if (arg_0->dwDaysForEval != 0x7FFFFFFF) {
			if (arg_0->dwDaysForEval > arg_8) {
				tmp = arg_0->dwDaysForEval - arg_8;
			} else {
				tmp = 0;
			}
		}
		*arg_10 = tmp;
	} else {
		DWORD edx;
		if (arg_4 == 0x452) {
			edx = 0x7FFFFFFF;
		} else if (*arg_C > arg_8) {
			edx = *arg_C - arg_8;
		} else {
			edx = 0;
		}
		*arg_C = edx;
		tmp = 0x7FFFFFFF;
		if (arg_0->dwDaysForEval != 0x7FFFFFFF) {
			if (arg_0->dwDaysForEval > arg_8) {
				tmp = arg_0->dwDaysForEval - arg_8;
			} else {
				tmp = 0;
			}
		}
		*arg_10 = tmp;
	}
}

int sub_1042A82() {
	PSID pSid;
	SID_IDENTIFIER_AUTHORITY IdentifierAuthority = {0, 0, 0, 0, 0, 5};
	BOOL IsMember = FALSE;
	if (!AllocateAndInitializeSid(&IdentifierAuthority, 2, 32, 544, 0, 0, 0, 0, 0, 0, &pSid)) {
		return FALSE;
	}
	if (!CheckTokenMembership(NULL, pSid, &IsMember)) {
		IsMember = FALSE;
	}
	FreeSid(pSid);
	return IsMember;
}

extern BOOL IsLocalSystem() {
	PSID pSid;
	SID_IDENTIFIER_AUTHORITY IdentifierAuthority = {0, 0, 0, 0, 0, 5};
	BOOL IsMember = FALSE;
	if (!AllocateAndInitializeSid(&IdentifierAuthority, 1, 18, 0, 0, 0, 0, 0, 0, 0, &pSid)) {
		return FALSE;
	}
	if (!CheckTokenMembership(NULL, pSid, &IsMember)) {
		IsMember = FALSE;
	}
	FreeSid(pSid);
	return IsMember;
}

BOOLEAN sub_1042CE7(LPWSTR lpExeName) {
	BYTE decryptKey[] = {0xCC, 0xC3, 0x8B, 0xFF, 0xCC, 0xC3, 0x8B, 0xFF, 0x8B, 0x44, 0x24, 4, 0xCC, 0xC2, 4, 0};
	// L"explorer.exe"
	WCHAR ExplorerExe[] = {0x7C76, 0x2879, 0x7E6D, 0xCE13, 0x552C, 0xCDD1, 0x8D36, 0xA1B9, 0x1A50, 0x0B15, 0x8CC0, 0x68FA, 0xF152, 0x8860, 0xA4C0};
	// L"taskmgr.exe"
	WCHAR TaskmgrExe[] = {0xC977, 0xA3DC, 0x7620, 0xF444, 0x265D, 0x7D2B, 0x8158, 0x2B73, 0x4FF2, 0xF4A4, 0x3B26, 0x237D, 0x0830, 0x36D0};
	// L"cmd.exe"
	WCHAR CmdExe[] = {0x8B28, 0xE1A6, 0x6CB2, 0x22B4, 0xF488, 0x57CC, 0x799A, 0xF98F, 0x0806, 0x5201};
	struct {
		WCHAR* Data;
		DWORD Size;
	} DisallowedExes[3] = {
		{ExplorerExe, sizeof(ExplorerExe) / sizeof(ExplorerExe[0])},
		{TaskmgrExe, sizeof(TaskmgrExe) / sizeof(TaskmgrExe[0])},
		{CmdExe, sizeof(CmdExe) / sizeof(CmdExe[0])},
	};
	DWORD i, j;
	for (i = 0; i < 3; i++) {
		if (!_wcsicmp(lpExeName, CWPAStringsDecryptor(DisallowedExes[i].Data, DisallowedExes[i].Size, decryptKey))) {
			return true;
		}
	}
	bool result = false;
	LPVOID pVersionInfo;
	DWORD dwHandle;
	DWORD dwVersionInfoSize = GetFileVersionInfoSize(lpExeName, &dwHandle);
	if (dwVersionInfoSize
		&& (pVersionInfo = HeapAlloc(GetProcessHeap(), 0, dwVersionInfoSize)) != NULL)
	{
		PDWORD pLanguages;
		UINT dwLanguagesSize;
		if (GetFileVersionInfo(lpExeName, NULL, dwVersionInfoSize, pVersionInfo)
			&& VerQueryValue(pVersionInfo, L"\\VarFileInfo\\Translation", (LPVOID*)&pLanguages, &dwLanguagesSize))
		{
			for (j = 0; !result && j < dwLanguagesSize / 4; j++) {
				WCHAR VersionSubBlock[0x400];
				wsprintf(VersionSubBlock, L"\\StringFileInfo\\%04x%04x\\OriginalFilename", LOWORD(pLanguages[j]), HIWORD(pLanguages[j]));
				LPCWSTR pOriginalFileName;
				UINT nOriginalFileNameSize;
				if (VerQueryValue(pVersionInfo, VersionSubBlock, (LPVOID*)&pOriginalFileName, &nOriginalFileNameSize)) {
					for (i = 0; i < 3; i++) {
						if (!_wcsicmp(pOriginalFileName, CWPAStringsDecryptor(DisallowedExes[i].Data, DisallowedExes[i].Size, decryptKey))) {
							result = true;
							break;
						}
					}
				}
			}
		}
		HeapFree(GetProcessHeap(), 0, pVersionInfo);
	}
	return result;
}

extern DWORD sub_1043104(DWORD timerId, DWORD* val) {
	if (val) {
		*val = 0;
	}
	DWORD esi = 0x88933;
	DWORD eax = esi;
	for (DWORD edx = 0x43AD; edx ^ 0x56E; edx--) {
		eax += (edx << 2) ^ 0x3EB;
	}
	if (eax > 0)
		eax = esi;
	if (0x3CA == timerId) {
		eax = 0x85BB;
	} else if (0x88D05 - eax == timerId) {
		if (val) {
			*val = dword_1075D2C;
			eax = 0;
		}
	} else if (0xC2 == timerId) {
		eax = 0;
	} else if (0x1E5 == timerId) {
		eax = 0xBA52;
	} else if (0x88D04 - eax == timerId) {
		if (val) {
			*val = dword_1075D28;
			eax = 0;
		}
	} else {
		eax = 2;
	}
	return eax;
}

extern DWORD sub_10432CC(int arg_0, int arg_4) {
	DWORD edx = 0x88933;
	DWORD ecx = edx;
	for (DWORD eax = 0x43AD; eax ^ 0x56E; eax--) {
		ecx += (eax << 2) ^ 0x3EB;
	}
	if (ecx > 0)
		ecx = edx;
	DWORD result;
	if (0xC2 == arg_0) {
		result = 0x5EB5;
	} else if (0x88D04 - ecx == arg_0) {
		dword_1075D28 = arg_4;
		return 0;
	} else if (0x3CA == arg_0) {
		result = 0x85BB;
	} else if (0x88D05 - ecx == arg_0) {
		dword_1075D2C = arg_4;
		return 0;
	} else if (0x1E5 == arg_0) {
		result = 0xBA52;
	} else {
		result = 2;
	}
	dword_1075D28 = 0;
	dword_1075D2C = 0;
	return result;
}

#ifdef _X86_
#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
extern void __declspec() End_Vspweb_Scp_Segment_1_2();
/*
void __declspec(naked) End_Vspweb_Scp_Segment_1_2() {
__asm {
                mov     ecx, 1
END_SCP_SEGMENT_1_2:
                mov     edx, 2
                retn
}
}
*/
#pragma warning(pop)
#endif

class CLSATimer : public CWPALockable { // WPA_LT_MUTEX
public:
	HRESULT sub_10438E7(CWPATimes* Data);
	HRESULT sub_1043D0C(CWPATimes* Data);
};

HRESULT CLSATimer::sub_10438E7(CWPATimes* Data) {
		CWPALockGuard var_20(L"Global\\WPA_LT_MUTEX", this);
		if (!var_20.sub_104360E()) {
			return E_FAIL;
		}
		// L"L${6B3E6424-AF3E-4bff-ACB6-DA535F0DDC0A}"
		WCHAR var_78[] = {0xD017, 0xAE9C, 0x4B5B, 0x7994, 0xB5A3, 0x7FAF, 0xE90E, 0xF419, 0x9E47, 0x370E, 0x8B93, 0xAD9D, 0x0793, 0xA573, 0xF141, 0xA684, 0x8C42, 0x2028, 0x4713, 0x20F4, 0x9425, 0xE8BE, 0xBFE3, 0xE213, 0xA875, 0x0306, 0x71BD, 0xC627, 0x6F30, 0x4A42, 0xC841, 0x4657, 0xD91E, 0x6227, 0x99F7, 0x67CE, 0x3E38, 0xCCAB, 0x9531, 0xF559, 0xFB43, 0x0EC0, 0x6670};
		WCHAR String1[0x2A];
		lstrcpyn(String1, CWPAStringsDecryptor(var_78, sizeof(var_78) / sizeof(var_78[0]), unk_1019768), sizeof(String1) / sizeof(String1[0]) - 1);
		CLSAStoreForWPA var_9C(NULL, POLICY_GET_PRIVATE_INFORMATION, String1);
		DWORD dwSize = sizeof(*Data);
		HRESULT status = var_9C.LoadData((LPBYTE)Data, &dwSize);
		WPADecrypt((LPBYTE)Data, sizeof(*Data), dword_1019778);
		if (SUCCEEDED(status) && !WPAValidateTimes(Data))
			status = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
		return status;
	}

HRESULT CLSATimer::sub_1043D0C(CWPATimes* Data) {
		CWPALockGuard var_20(L"Global\\WPA_LT_MUTEX", this);
		if (!var_20.sub_104360E()) {
			return E_FAIL;
		}
		// L"L${6B3E6424-AF3E-4bff-ACB6-DA535F0DDC0A}"
		WCHAR var_78[] = {0xD017, 0xAE9C, 0x4B5B, 0x7994, 0xB5A3, 0x7FAF, 0xE90E, 0xF419, 0x9E47, 0x370E, 0x8B93, 0xAD9D, 0x0793, 0xA573, 0xF141, 0xA684, 0x8C42, 0x2028, 0x4713, 0x20F4, 0x9425, 0xE8BE, 0xBFE3, 0xE213, 0xA875, 0x0306, 0x71BD, 0xC627, 0x6F30, 0x4A42, 0xC841, 0x4657, 0xD91E, 0x6227, 0x99F7, 0x67CE, 0x3E38, 0xCCAB, 0x9531, 0xF559, 0xFB43, 0x0EC0, 0x6670};
		WCHAR String1[0x2A];
		lstrcpyn(String1, CWPAStringsDecryptor(var_78, sizeof(var_78) / sizeof(var_78[0]), unk_1019768), sizeof(String1) / sizeof(String1[0]) - 1);
		CLSAStoreForWPA var_9C(0, POLICY_CREATE_SECRET, String1);
		CWPATimes EncryptedData = *Data;
		WPAEncrypt((LPBYTE)&EncryptedData, sizeof(EncryptedData), dword_1019778);
		return var_9C.StoreData((LPBYTE)&EncryptedData, sizeof(EncryptedData));
	}

void unused4() { CWPAClass4 x; }

HRESULT sub_10438E7(CWPATimes* Data);
HRESULT sub_1043D0C(CWPATimes* Data);

class CProtectedRegistry : public CWPALockable { // WPA_PR_MUTEX
public:
	HRESULT sub_10440B7(CWPATimes* Data);
	HRESULT sub_1044224(CWPATimes* Data);
};
HRESULT CProtectedRegistry::sub_10440B7(CWPATimes* Data) {
	CWPALockGuard var_18(L"Global\\WPA_PR_MUTEX", this);
	if (!var_18.sub_104360E()) {
		return E_FAIL;
	}
	return sub_104B34F(0, Data);
}
HRESULT CProtectedRegistry::sub_1044224(CWPATimes* Data) {
	CWPALockGuard var_18(L"Global\\WPA_PR_MUTEX", this);
	if (!var_18.sub_104360E()) {
		return E_FAIL;
	}
	return sub_104B689(0, Data);
}

class CProtectedRegistryEx : public CWPALockable { // WPA_HWID_MUTEX
public:
	HRESULT sub_1044389(CWPATimes* Data);
	HRESULT sub_104453D(CWPATimes* Data);
};

HRESULT CProtectedRegistryEx::sub_1044389(CWPATimes* Data) {
	CWPALockGuard var_18(L"Global\\WPA_HWID_MUTEX", this);
	if (!var_18.sub_104360E()) {
		return E_FAIL;
	}
	return sub_104B34F(1, Data);
}
HRESULT CProtectedRegistryEx::sub_104453D(CWPATimes* Data) {
	CWPALockGuard var_18(L"Global\\WPA_HWID_MUTEX", this);
	if (!var_18.sub_104360E()) {
		return E_FAIL;
	}
	return sub_104B689(1, Data);
}

void use_CProtectedRegistry() { CProtectedRegistry r; }

DWORD sub_10446D6(LPSYSTEMTIME arg_0) {
	DWORD result = 0x7FFFFFFF;
	CProtectedRegistry var_14;
	CWPATimes var_5C;
	if (SUCCEEDED(var_14.sub_10440B7(&var_5C)) && sub_1040D9D(&var_5C)) {
		if (arg_0) {
			*arg_0 = var_5C.InstallTime;
		}
		SYSTEMTIME var_24;
		if (SUCCEEDED(sub_10409FC(&var_24))) {
			result = sub_1040667(&var_5C.InstallTime, &var_24);
		}
	}
	return result;
}

void unused5() { AutoHeapPtr<BYTE> x; }

class CWPAClass3 {
public:
	int sub_10449C9(CWPALicenseManager* arg_0, CWPATimes* Data);
};

int CWPAClass3::sub_10449C9(CWPALicenseManager* arg_0, CWPATimes* Data) {
	DWORD var_10 = 0;
	AutoHeapPtr<BYTE> var_1C;
	DWORD err = arg_0->sub_1054386(0x33, (LPVOID*)&var_1C, &var_10);
	if (err) {
		return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
	}
	memcpy(Data, var_1C, (var_10 > sizeof(CWPATimes) ? sizeof(CWPATimes) : var_10));
	BYTE var_30[16];
	if (SUCCEEDED(GetPerMachine128BitSeed(var_30))) {
		WPADecrypt((LPBYTE)Data, sizeof(CWPATimes), var_30);
	}
	if (Data->dwSize == sizeof(*Data)) {
		OSVERSIONINFOEX VersionInfo;
		VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
		GetVersionEx((OSVERSIONINFO*)&VersionInfo);
		DWORD dwMask;
		if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			dwMask = 0x10000;
		} else {
			dwMask = 0;
		}
		DWORD dwProductId = 0x80000E7A | dwMask;
		if (Data->dwProductId == dwProductId) {
			return S_OK;
		}
	}
	return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

class CRegistryTimer : public CWPALockable { // WPA_RT_MUTEX
public:
	HRESULT sub_1044C92(CWPATimes* Data);
	HRESULT sub_1044FB6(CWPATimes* Data);
};

HRESULT CRegistryTimer::sub_1044C92(CWPATimes* Data) {
	CWPALockGuard var_1C(L"Global\\WPA_RT_MUTEX", this);
	if (!var_1C.sub_104360E()) {
		return E_FAIL;
	}
	CWPACryptHelper var_3C;
	HRESULT status = var_3C.sub_104FD06(byte_1018F00, sizeof(byte_1018F00), 0);
	if (FAILED(status)) {
		return status;
	}
	AutoHKEY var_28;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_1075188, 0x2F, unk_1019768), 0, KEY_READ, &var_28) != 0) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	status = var_3C.sub_105021B(var_28, CWPAStringsDecryptor(unk_1075168, 0xE, unk_1019768), (LPBYTE)Data, sizeof(*Data));
	if (FAILED(status)) {
		return status;
	}
	if (Data->dwSize == sizeof(*Data)) {
		OSVERSIONINFOEX VersionInfo;
		VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
		GetVersionEx((OSVERSIONINFO*)&VersionInfo);
		DWORD dwMask;
		if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			dwMask = 0x10000;
		} else {
			dwMask = 0;
		}
		DWORD dwProductId = 0x80000E7A | dwMask;
		if (Data->dwProductId != dwProductId) {
			status = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
		}
	} else {
		status = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	return status;
}

HRESULT CRegistryTimer::sub_1044FB6(CWPATimes* Data) {
	CWPALockGuard var_1C(L"Global\\WPA_RT_MUTEX", this);
	if (!var_1C.sub_104360E()) {
		return E_FAIL;
	}
	CWPACryptHelper var_3C;
	HRESULT status = var_3C.sub_104FD06(byte_1018F00, sizeof(byte_1018F00), 0);
	if (FAILED(status)) {
		return status;
	}
	AutoHKEY var_28;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_1075188, 0x2F, unk_1019768), 0, KEY_READ | KEY_WRITE, &var_28) != 0) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	status = var_3C.sub_105068E(var_28, CWPAStringsDecryptor(unk_1075168, 0xE, unk_1019768), (LPBYTE)Data, sizeof(*Data));
	return status;
}

extern DWORD CALLBACK sub_1045263(LPVOID ThreadParam) {
	CWPATimes* arg_0 = (CWPATimes*)ThreadParam;
	CLSATimer var_C;
	BOOL var_4 = FALSE;
	CWPATimes* esi = arg_0;
	CWPATimes var_74;
	HRESULT status;
	if (!esi) {
		var_4 = TRUE;
		status = var_C.sub_10438E7(&var_74);
		if (SUCCEEDED(status)) {
			if (sub_1040D9D(&var_74)) {
				SYSTEMTIME var_1C;
				status = sub_10409FC(&var_1C);
				if (SUCCEEDED(status)) {
					if (var_1C < var_74.LastUsageTime) {
						SYSTEMTIME var_2C = var_74.LastUsageTime - var_1C;
						var_74.InstallTime -= var_2C;
					}
					var_74.LastUsageTime = var_1C;
					sub_1040B54(&var_74);
					esi = &var_74;
				}
			} else {
				status = E_WPA_ERROR_0501;
			}
		}
		if (FAILED(status)) {
			return status;
		}
	}
	status = var_C.sub_1043D0C(esi);
	if (SUCCEEDED(status)) {
		DWORD TimeInterval = 3600000 * (GetTickCount() % 8 + 1);
		SetTimer(hWnd, 976, TimeInterval, NULL);
	}
	if (!var_4 && esi) {
		HeapFree(GetProcessHeap(), 0, esi);
	}
	return status;
}

HRESULT sub_10454C4(CWPALicenseManager* arg_0, DWORD arg_4, DWORD arg_8, CWPATimes* arg_C) {
	CWPATimes var_15C;
	CWPATimes var_124;
	CWPATimes var_EC;
	CWPATimes var_B4;
	CWPATimes var_7C;
	if (!arg_C) {
		return E_POINTER;
	}
	ZeroMemory(arg_C, sizeof(*arg_C));
	int var_14 = 0;
	DWORD var_10 = 0;
	CRegistryTimer var_34;
	CLSATimer var_2C;
	CProtectedRegistry var_3C;
	CProtectedRegistryEx var_44;
	if (arg_4 && SUCCEEDED(var_44.sub_1044389(&var_B4)) && sub_1040D9D(&var_B4)) {
		var_10 = 0x10;
	}
	if (SUCCEEDED(var_3C.sub_10440B7(&var_124))) {
		var_14 = 1;
		if (sub_1040D9D(&var_124)) {
			var_10 |= 8;
		}
	}
	if (SUCCEEDED(var_34.sub_1044C92(&var_7C))) {
		var_14++;
		if (sub_1040D9D(&var_7C)) {
			var_10 |= 1;
		}
	}
	if (SUCCEEDED(var_2C.sub_10438E7(&var_EC))) {
		var_14++;
		if (sub_1040D9D(&var_EC)) {
			var_10 |= 2;
		}
	}
	CWPAClass3 unusedthis;
	if (SUCCEEDED(unusedthis.sub_10449C9(arg_0, &var_15C))) {
		++var_14;
		if (sub_1040D9D(&var_15C)) {
			var_10 |= 4;
		}
	}
	if (!(var_10 & 8)) {
		return E_WPA_ERROR_0508;
	}
	SYSTEMTIME var_24 = {1968, 8, 1, 9, 13, 16, 0, 0};
	arg_C->dwSize = sizeof(*arg_C);
	OSVERSIONINFOEX VersionInformation;
	VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
	GetVersionEx((OSVERSIONINFO*)&VersionInformation);
	DWORD dwMask;
	if (VersionInformation.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInformation.wSuiteMask & VER_SUITE_PERSONAL) {
		dwMask = 0x10000;
	} else {
		dwMask = 0;
	}
	arg_C->dwProductId = 0x80000E7A | dwMask;
	arg_C->InstallTime = var_124.InstallTime;
	arg_C->LastUsageTime = var_24;
	if (var_10 & 1) {
		arg_C->InstallTime = std::_cpp_min(arg_C->InstallTime, var_7C.InstallTime);
		arg_C->LastUsageTime = std::_cpp_max(arg_C->LastUsageTime, var_7C.LastUsageTime);
	}
	if (var_10 & 2) {
		arg_C->InstallTime = std::_cpp_min(arg_C->InstallTime, var_EC.InstallTime);
		arg_C->LastUsageTime = std::_cpp_max(arg_C->LastUsageTime, var_EC.LastUsageTime);
	}
	if (var_10 & 4) {
		arg_C->InstallTime = std::_cpp_min(arg_C->InstallTime, var_15C.InstallTime);
		arg_C->LastUsageTime = std::_cpp_max(arg_C->LastUsageTime, var_15C.LastUsageTime);
	}
	if (var_10 & 0x10) {
		if (var_B4.LastUsageTime == arg_C->InstallTime || arg_8) {
			arg_C->InstallTime = std::_cpp_max(var_124.InstallTime, var_B4.InstallTime);
		}
	}
	sub_1040B54(arg_C);
	if (var_14 < 4) {
		return E_WPA_ERROR_0501;
	}
	return S_OK;
}

HRESULT sub_104590D(CWPALicenseManager* arg_0, CWPATimes* arg_4, int arg_8, DWORD* arg_C) {
	CWPAClass5 unusedthis;
	*arg_C = 0x7FFFFFFF;
	BOOL var_10 = TRUE;
	SYSTEMTIME var_34 = {2001, 1, 1, 1, 1, 1, 1, 1};
	SYSTEMTIME var_44;
	HRESULT status = sub_10409FC(&var_44);
	if (FAILED(status)) {
		return status;
	}
	if (arg_8 != 0x7FFFFFFF && var_44 < var_34 && var_34 < arg_4->InstallTime) {
		*arg_C = 0;
		return E_WPA_ERROR_0502;
	}
	if (var_44 < arg_4->LastUsageTime) {
		SYSTEMTIME var_54 = arg_4->LastUsageTime - var_44;
		arg_4->InstallTime -= var_54;
	} else {
		if (!sub_1040667(&var_44, &arg_4->LastUsageTime)) {
			var_10 = FALSE;
		}
	}
	arg_4->LastUsageTime = var_44;
	sub_1040B54(arg_4);
	CRegistryTimer var_24;
	CProtectedRegistry var_1C;
	status = var_1C.sub_1044224(arg_4);
	if (FAILED(status) && status != E_ACCESSDENIED)
		goto done;
	status = var_24.sub_1044FB6(arg_4);
	if (FAILED(status) || !var_10)
		goto done;
	status = unusedthis.sub_1040FFA(arg_0, arg_4);
	if (FAILED(status))
		goto done;
	CWPATimes* tmp = (CWPATimes*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CWPATimes));
	if (tmp) {
		*tmp = *arg_4;
		hThread = CreateThread(NULL, 0, &sub_1045263, tmp, CREATE_SUSPENDED, NULL);
		if (!hThread) {
			status = HRESULT_FROM_WIN32(GetLastError());
		}
	} else {
		status = E_OUTOFMEMORY;
	}
done:
	if (FAILED(status)) {
		return E_WPA_ERROR_0504;
	}
	*arg_C = sub_1040667(&var_44, &arg_4->InstallTime);
	return status;
}

HRESULT sub_1045C98(CWPALicenseManager* arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C, PDWORD arg_10, BOOL arg_14) {
	CWPATimes var_38;
	HRESULT hr = sub_10454C4(arg_0, arg_4, arg_8, &var_38);
	if (!arg_14 && FAILED(hr)) {
		return hr;
	}
	if (FAILED(hr) && hr != E_WPA_ERROR_0502 && hr != E_WPA_ERROR_0501) {
		return hr;
	}
	hr = sub_104590D(arg_0, &var_38, arg_C, arg_10);
	return hr;
}

extern HRESULT GetReminder(DWORD* arg_0) {
	AutoHKEY var_18;
	DWORD cbData;
	DWORD Data = 0;
	DWORD Type = 4;
	*arg_0 = 0;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRWPA, 0, KEY_ALL_ACCESS, &var_18) == 0) {
		cbData = sizeof(Data);
		if (RegQueryValueEx(var_18, szSetRem, NULL, &Type, (LPBYTE)&Data, &cbData) == 0) {
			*arg_0 = Data;
		}
	}
	return S_OK;
}

void sub_1045FAC() {
	sub_104B9E5(1);
	DWORD var_10 = 0;
	if (GetReminder(&var_10) == S_OK && var_10 == 1) {
		return;
	}
	AutoHKEY var_1C;
	DWORD err = RegOpenKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(szRRWPA, 0x35, unk_1019768), 0, KEY_ALL_ACCESS, &var_1C);
	if (err) {
		return;
	}
	RegDeleteValue(var_1C, CWPAStringsDecryptor(szActDone, 0x11, unk_1019768));
}

struct COOBETimer
{
	DWORD field_0;
	DWORD field_4;
	DWORD field_8;
};

extern void sub_10461F2(DWORD arg_0, DWORD arg_4, DWORD arg_8) {
	DWORD dwDisposition;
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_1_11_0_10_00_00 ; void const * * ScpProtectedData_1_11_0_10_00_00
                pop     eax
        }
#endif
	COOBETimer Data;
#ifdef _X86_
	__asm   cmp     eax, offset Begin_Vspweb_Scp_Segment_1_2 ; Begin_Vspweb_Scp_Segment_1_2(void)
	{} // this splits ASM block in two; a hack to enforce the correct stack layout
        __asm   cmp     eax, offset End_Vspweb_Scp_Segment_1_2 ; End_Vspweb_Scp_Segment_1_2(void)
#endif
	Data.field_0 = 0;
	Data.field_4 = 0;
	Data.field_8 = 0x7FFFFFFF;
	if (arg_4 == 0x7FFFFFFF && arg_8 == 0x7FFFFFFF) {
		AutoHKEY var_40;
		DWORD Type = 3;
		DWORD cbData = sizeof(Data);
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_10751E8, 0x39, unk_1019768), 0, KEY_READ, &var_40) == 0) {
			if (RegQueryValueEx(var_40, L"OOBETimer", NULL, &Type, (LPBYTE)&Data, &cbData) == 0) {
				WPADecrypt((LPBYTE)&Data, sizeof(Data), dword_1019778);
			}
		}
	} else {
		Data.field_4 = arg_4;
		Data.field_8 = arg_8;
	}
	Data.field_0 = arg_0;
	WPAEncrypt((LPBYTE)&Data, sizeof(Data), dword_1019778);
	AutoHKEY var_30;
	DWORD status = RegCreateKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_10751E8, 0x39, unk_1019768), NULL, NULL, 0, KEY_ALL_ACCESS, NULL, &var_30, &dwDisposition);
	if (status == 0) {
		RegSetValueEx(var_30, L"OOBETimer", NULL, 3, (LPBYTE)&Data, sizeof(Data));
	}
	if (arg_0 == 0x7FFFFFFF) {
		KillTimer(hWnd, 975);
		if (arg_4 == 0x7FFFFFFF) {
			if (arg_8 != 0x7FFFFFFF) {
				KillTimer(hWnd, 976);
			}
		}
	} else if (arg_0) {
		SetTimer(hWnd, 975, 120000, NULL);
	}
}

BOOL sub_10467BF(BOOL arg_0) {
	DWORD var_10 = 0;
	// L"LastWPAEventLogged"
	WCHAR var_74[] = {0x22F3,0xABF0,0x1FF2,0xA07D,0x4B28,0x5463,0x5681,0xDF1E,0xBD35,0x6728,0x3569,0xEE80,0xB48D,0x47FD,0xBE46,0xC5C3,0x8298,0xF86E,0x81B1,0x05F2,0x524C};
	// L"LastTBEventLogged"
	WCHAR var_48[] = {0xAAF3,0xD1D7,0xEFE6,0x37A1,0x1E95,0x4605,0x5DE4,0x1D1F,0xEC3C,0x52C1,0x5026,0xD0A3,0x361B,0xFCBC,0xF234,0x5943,0x3E5F,0x2F7C,0x4288,0x3723};
	AutoHKEY var_1C;
	DWORD var_8C;
	DWORD err = RegCreateKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_10751E8, 0x39, unk_1019768), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &var_1C, &var_8C);
	if (err) {
		return FALSE;
	}
	SYSTEMTIME Data;
	SYSTEMTIME var_88;
	DWORD Type = 3;
	DWORD cbData = sizeof(Data);
	HRESULT status = sub_10409FC(&var_88);
	if (FAILED(status)) {
		return FALSE;
	}
	err = RegQueryValueEx(var_1C,
		arg_0 == FALSE
			? CWPAStringsDecryptor(var_74, sizeof(var_74) / sizeof(var_74[0]), unk_1019768)
			: CWPAStringsDecryptor(var_48, sizeof(var_48) / sizeof(var_48[0]), unk_1019768),
		NULL, &Type, (LPBYTE)&Data, &cbData);
	if (err == 2) {
		RegSetValueEx(var_1C,
			arg_0 == FALSE
				? CWPAStringsDecryptor(var_74, sizeof(var_74) / sizeof(var_74[0]), unk_1019768)
				: CWPAStringsDecryptor(var_48, sizeof(var_48) / sizeof(var_48[0]), unk_1019768),
			NULL, 3, (LPBYTE)&var_88, sizeof(var_88));
		return FALSE;
	}
	if (!sub_1040667(&var_88, &Data)) {
		return TRUE;
	}
	RegSetValueEx(var_1C,
		arg_0 == FALSE
			? CWPAStringsDecryptor(var_74, sizeof(var_74) / sizeof(var_74[0]), unk_1019768)
			: CWPAStringsDecryptor(var_48, sizeof(var_48) / sizeof(var_48[0]), unk_1019768),
		NULL, Type, (LPBYTE)&var_88, sizeof(var_88));
	return FALSE;
}

void sub_1046D74(DWORD arg_0, DWORD arg_4, PBOOL arg_8, PBOOL arg_C) {
	if (!arg_0 || !arg_4) {
		*arg_8 = TRUE;
		*arg_C = TRUE;
		return;
	}
	*arg_8 = FALSE;
	*arg_C = FALSE;
	for (DWORD i = 0; i < 3; i++) {
		if (dword_1018F0C[i][0] < arg_0) {
			continue;
		}
		if (dword_1018F0C[i][1] > arg_0) {
			continue;
		}
		if (arg_0 % dword_1018F0C[i][2]) {
			continue;
		}
		if (sub_10467BF(FALSE)) {
			break;
		}
		*arg_8 = TRUE;
	}
	for (DWORD i = 0; i < 4; i++) {
		if (dword_1018F30[i][0] < arg_4) {
			continue;
		}
		if (dword_1018F30[i][1] > arg_4) {
			continue;
		}
		if (arg_4 % dword_1018F30[i][2]) {
			continue;
		}
		if (sub_10467BF(TRUE)) {
			break;
		}
		*arg_C = TRUE;
	}
}

#define MAX_EVENT_STRINGS 5

HRESULT sub_1046EB1(int arg_0, int arg_4, WORD EventType, DWORD EventId, DWORD SizeOfRawData, PVOID RawData, DWORD NumberOfStrings, ...) {
	va_list arglist;
	ULONG i;
	PCWSTR Strings[ MAX_EVENT_STRINGS ];
	BOOL var_4 = FALSE, var_8 = FALSE;
	sub_1046D74(arg_0, arg_4, &var_4, &var_8);
	if (!var_4 && !var_8) {
		return S_OK;
	}
	va_start(arglist, NumberOfStrings);
	if (NumberOfStrings > MAX_EVENT_STRINGS) {
		NumberOfStrings = MAX_EVENT_STRINGS;
	}
	for (i = 0; i < NumberOfStrings; i++) {
		Strings[i] = va_arg(arglist, PCWSTR);
	}
	HRESULT result = S_OK;
	HANDLE hEventLog = RegisterEventSource(NULL, L"Windows Product Activation");
	if (!hEventLog) {
		result = HRESULT_FROM_WIN32(GetLastError());
		goto done;
	}
	if (!ReportEvent(hEventLog, EventType, 0, EventId, NULL, (WORD)NumberOfStrings, SizeOfRawData, Strings, RawData)) {
		result = HRESULT_FROM_WIN32(GetLastError());
		goto cleanup;
	}
cleanup:
	DeregisterEventSource(hEventLog);
done:
	return result;
}

extern DWORD CALLBACK sub_10470D2(LPVOID arg_0) {
#ifdef _X86_
	__asm   push    eax
        __asm   lea     eax, ScpProtectedData_1_11_0_10_00_00 ; void const * * ScpProtectedData_1_11_0_10_00_00
        __asm   pop     eax
#endif
	HANDLE hDoneEvent = (HANDLE)arg_0;
	WCHAR var_26C[MAX_PATH];
#ifdef _X86_
        __asm   cmp     eax, offset Begin_Vspweb_Scp_Segment_1_2 ; Begin_Vspweb_Scp_Segment_1_2(void)
        __asm   cmp     eax, offset End_Vspweb_Scp_Segment_1_2 ; End_Vspweb_Scp_Segment_1_2(void)
#endif
	WPADummy();
	CreateAndHoldWPAGlobalMutex();
	AutoPtr<CWPALicenseManager> var_18(new CWPALicenseManager);
	if (!var_18) {
		SetEvent(hDoneEvent);
		return E_OUTOFMEMORY;
	}
	DWORD keyPart1 = 0xFCD7E8A8;
	if (var_18.get()->sub_1053728(&keyPart1, 4)) {
		SetEvent(hDoneEvent);
		return E_WPA_ERROR_0507;
	}
	BOOL ebx = FALSE;
	CProtectedRegistry var_C;
	CWPATimes var_64;
	HRESULT status = var_C.sub_10440B7(&var_64);
	if (FAILED(status)) {
		SYSTEMTIME var_28 = {2001,1,1,1,1,1,1,1};
		status = sub_10409FC(&var_28);
		if (FAILED(status)) {
			wsprintf(var_26C, L"3 0x%x", status);
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_26C);
		}
		var_64.LastUsageTime = var_28;
		var_64.InstallTime = var_28;
		sub_1040B54(&var_64);
		status = var_C.sub_1044224(&var_64);
		if (FAILED(status)) {
			wsprintf(var_26C, L"4 0x%x", status);
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_26C);
		} else {
			ebx = TRUE;
		}
	}
	{
		DWORD var_2C;
		status = sub_1045C98(var_18, 0, 0, ebx ? 0x7FFFFFFF : 185, &var_2C, 1);
	}
	if (hThread) {
		ResumeThread(hThread);
		CloseHandle(hThread);
		hThread = NULL;
	}
	SetEvent(hDoneEvent);
	return status;
}

HRESULT sub_1047539(CWPALicenseManager* arg_0, CWPAProductChannelInfo* arg_4, PDWORD arg_8, PDWORD arg_C, PDWORD arg_10, bool* arg_14, PDWORD arg_18) {
	WCHAR var_80[0x40];
	*arg_18 = 0x452;
	*arg_14 = false;
	if (*arg_C != 0x7FFFFFFF) {
		HRESULT status = sub_1045C98(arg_0, 0, 0, *arg_C, arg_10, 1);
		if (FAILED(status)) {
			if (status == E_WPA_ERROR_0502) {
				sub_1041B36(0x78, 0, 0x10);
				status = E_WPA_ERROR_B012;
			}
			return status;
		}
		sub_1042932(arg_4, *arg_18, *arg_10, arg_8, arg_C, arg_14);
		sub_10461F2(*arg_8, *arg_C, *arg_10);
		if (*arg_C == 0) {
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1003, 0, 0, 0, 0);
			sub_1041B36(0x69, 0, 0);
			TerminateProcess(GetCurrentProcess(), STATUS_EVALUATION_EXPIRATION);
			return E_WPA_ERROR_0505;
		}
		if (*arg_C <= 35) {
			DWORD edi = *arg_C >= 5 ? *arg_C - 5 : 0;
			wsprintf(var_80, L"%u", edi);
			sub_1046EB1(0x7FFFFFFF, *arg_C, 2, 0x80000000 | 1007, 0, 0, 1, var_80);
			sub_10423EA(edi);
		}
	} else {
		sub_10461F2(0x7FFFFFFF, 0x7FFFFFFF, 0);
	}
	return S_OK;
}

extern HRESULT ExtendGracePeriod(CWPALicenseManager* arg_0) {
	WCHAR var_290[MAX_PATH];
	CProtectedRegistryEx var_18;
	DWORD ebx = 1;
	SYSTEMTIME var_10 = {2001, 1, 1, 1, 1, 1, 1, 1};
	HRESULT status = sub_10409FC(&var_10);
	if (FAILED(status)) {
		wsprintf(var_290, L"5 0x%x", status);
		sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_290);
	}
	CWPATimes var_50;
	if (FAILED(var_18.sub_1044389(&var_50))) {
		CWPATimes var_88;
		if (sub_10454C4(arg_0, 0, 0, &var_88) != E_POINTER) {
			var_50.LastUsageTime = var_88.InstallTime;
		}
		var_50.InstallTime = var_10;
		sub_1040B54(&var_50);
		status = var_18.sub_104453D(&var_50);
		if (FAILED(status)) {
			wsprintf(var_290, L"6 0x%x", status);
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_290);
		}
		return status;
	} else {
		return E_FAIL;
	}
}

extern int sub_10479E9(PDWORD arg_0, PDWORD arg_4, BOOL arg_8) {
	COOBETimer Data;
	CWPATimes var_A8;
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_1_11_0_10_00_00 ; void const * * ScpProtectedData_1_11_0_10_00_00
                pop     eax
        }
        {}
        __asm {
                cmp     eax, offset Begin_Vspweb_Scp_Segment_1_2 ; Begin_Vspweb_Scp_Segment_1_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_1_2 ; End_Vspweb_Scp_Segment_1_2(void)
	}
#endif
	WPADummy();
	if (!arg_0 || !arg_4) {
		return E_POINTER;
	}
	*arg_0 = 0;
	*arg_4 = 0;
	SYSTEMTIME var_4C;
	BOOL var_2C = TRUE;
	HRESULT status = sub_10409FC(&var_4C);
	if (FAILED(status)) {
		return status;
	}
	BOOL var_C;
	if (arg_8) {
		var_C = FALSE;
	} else {
		var_C = IsLocalSystem();
	}
	DWORD var_10 = FALSE;
	DWORD _arg_8 = 0;
	if (var_C) {
		var_2C = FALSE;
	}
	CRegistryTimer var_28;
	status = var_28.sub_1044C92(&var_A8);
	DWORD edi = 0x7FFFFFFF;
	if (SUCCEEDED(status) && sub_1040D9D(&var_A8)) {
		var_10 = TRUE;
		if (var_4C < var_A8.LastUsageTime) {
			SYSTEMTIME var_B8 = var_A8.LastUsageTime - var_4C;
			var_A8.InstallTime -= var_B8;
		}
		_arg_8 = sub_1040667(&var_4C, &var_A8.InstallTime);
		AutoHKEY var_3C;
		DWORD error = RegOpenKeyEx(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(unk_10751E8, 0x39, unk_1019768), 0, KEY_READ, &var_3C);
		if (error) {
			return HRESULT_FROM_WIN32(error);
		}
		DWORD Type = 3;
		DWORD cbData = sizeof(Data);
		if (RegQueryValueEx(var_3C, L"OOBETimer", NULL, &Type, (LPBYTE)&Data, &cbData) == 2) {
			return E_WPA_ERROR_B012;
		}
		WPADecrypt((LPBYTE)&Data, sizeof(Data), dword_1019778);
		if (Data.field_0 == 0x7FFFFFFF) {
			*arg_0 = 0x7FFFFFFF;
		} else if (Data.field_0 > _arg_8 - Data.field_8) {
			*arg_0 = Data.field_8 - _arg_8 + Data.field_0;
		} else {
			*arg_0 = 0;
		}
		if (Data.field_4 == 0x7FFFFFFF) {
			*arg_4 = 0x7FFFFFFF;
		} else if (Data.field_4 > _arg_8 - Data.field_8) {
			*arg_4 = Data.field_8 - _arg_8 + Data.field_4;
		} else {
			*arg_4 = 0;
		}
	}
	if (var_C || !var_10) {
		DWORD var_8 = 0;
		DWORD var_14 = 0;
		BOOL _arg_0 = FALSE;
		WCHAR var_E8[0x18];
		CWPAProductChannelInfo var_68;
		status = sub_105E81B(var_E8, 0x18, &var_8, &var_14, &_arg_0, &var_68);
		if (SUCCEEDED(status)) {
			if (!var_10) {
				*arg_4 = var_68.dwDaysForEval;
				if (var_68.dwLicenseType == 5 || var_68.dwDaysForActivation > var_68.dwDaysForEval && var_68.dwDaysForActivation != 0x7FFFFFFF) {
					*arg_0 = 0x7FFFFFFF;
				} else {
					*arg_0 = var_68.dwDaysForActivation;
				}
			} else if (var_C && *arg_0 == 0x7FFFFFFF) {
				if (var_68.dwLicenseType != 5 && var_68.dwLicenseType != 1 && var_68.dwDaysForActivation < var_68.dwDaysForEval) {
					if (var_68.dwDaysForActivation >= _arg_8)
						*arg_0 = var_68.dwDaysForActivation - _arg_8;
					else
						*arg_0 = 0;
				}
			} else if (var_68.dwDaysForActivation > var_68.dwDaysForEval && var_68.dwDaysForActivation != 0x7FFFFFFF) {
				dword_1075D24 = 1;
				*arg_0 = 0x7FFFFFFF;
			} else if (var_68.dwLicenseType == 1 || var_68.dwLicenseType == 5) {
				*arg_0 = 0x7FFFFFFF;
			}
		} else {
			return status;
		}
	}
	if (var_2C && SUCCEEDED(status) && *arg_0 != 0x7FFFFFFF) {
		if (*arg_0) {
			WCHAR var_168[0x40];
			wsprintf(var_168, L"%u", *arg_0);
			sub_1046EB1(*arg_0, *arg_4, 2, 0x80000000 | 1005, 0, 0, 1, var_168);
		} else {
			sub_1046EB1(*arg_0, *arg_4, 2, 0xC0000000 | 1011, 0, 0, 0, 0);
		}
	}
	return S_OK;
}

extern HRESULT sub_1047F5F(HANDLE hUserToken, LPWSTR lpDesktop) {
	WCHAR CommandLine[0x152];
	WCHAR Buffer[0x111];
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInformation;

	if (dword_1075D24) {
		return S_OK;
	}
	DWORD var_4_ = 0, var_8 = 0;
	HRESULT status = sub_10479E9(&var_4_, &var_8, 1);
	if (FAILED(status)) {
		return status;
	}
	DWORD var_4 = var_4_;
	if (var_4 == 0x7FFFFFFF) {
		KillTimer(hWnd, 975);
		return S_OK;
	}
	DWORD szSysDir = GetSystemDirectory(Buffer, sizeof(Buffer) / sizeof(Buffer[0]));
	if (!szSysDir || szSysDir + 14 >= sizeof(Buffer) / sizeof(Buffer[0])) {
		return E_FAIL;
	}
	lstrcat(Buffer, L"\\wpabaln.exe");
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	ZeroMemory(&ProcessInformation, sizeof(ProcessInformation));
	wsprintf(CommandLine, L"%s %u", Buffer, var_4);
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	StartupInfo.lpDesktop = lpDesktop;
	StartupInfo.lpTitle = NULL;
	StartupInfo.dwX = StartupInfo.dwY = StartupInfo.dwXSize = StartupInfo.dwYSize = 0;
	StartupInfo.dwFlags = 0;
	StartupInfo.wShowWindow = SW_SHOW;
	StartupInfo.lpReserved2 = NULL;
	StartupInfo.cbReserved2 = 0;
	if (CreateProcessAsUser(hUserToken, Buffer, CommandLine, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &StartupInfo, &ProcessInformation)) {
		CloseHandle(ProcessInformation.hThread);
		CloseHandle(ProcessInformation.hProcess);
	}
	DWORD Interval = 0;
	if (var_4 == 0) {
		Interval = 15;
	} else if (var_4 <= 7) {
		Interval = 240;
	} else if (var_4 <= 14) {
		Interval = 1440;
	} else if (var_4 <= 120) {
		Interval = 4320;
	}
	SetTimer(hWnd, 975, Interval * 60000, NULL);
	return S_OK;
}

HRESULT sub_104820A(CWPALicenseManager* arg_0, PDWORD arg_4, DWORD arg_8, HWID* arg_C, PDWORD arg_10, LPCWSTR arg_14) {
	// lpString2 = arg_14
	if (!arg_4) {
		return E_POINTER;
	}
	WORD String1[24];
	BYTE var_14[0x14];
	HRESULT status = S_OK;
	CWPAClass4 var_CC;
	DWORD result = arg_0->ValidateActivation(arg_8, &var_CC);
	if (result == 0x53) {
		*arg_4 = 1;
		status = S_OK;
	} else {
		if (result) {
			goto status_from_result;
		}
		if (arg_14) {
			lstrcpyn(String1, arg_14, sizeof(String1) / sizeof(String1[0]));
		} else {
			status = sub_105EAF9(String1, sizeof(String1) / sizeof(String1[0]));
			if (FAILED(status)) {
				goto done;
			}
		}
		WCHAR var_108[30];
		status = GetFullPKAndHash(var_108, sizeof(var_108), var_14, sizeof(var_14));
		if (FAILED(status)) {
			goto done;
		}
		bool processed = false;
		if (0 == memcmp(var_CC.field_14, String1, (lstrlen(var_CC.field_14) - 3) * sizeof(WCHAR)) &&
			(var_CC.field_6C == 0 || 0 == memcmp(var_CC.field_70, var_14, var_CC.field_84)))
		{
			DWORD tmp;
			status = GetSafeMode(&tmp);
			if (FAILED(status)) {
				goto done;
			}
			bool processed = false;
			if (tmp == 2 || sub_105ACAD((HWID*)&var_CC.field_56)) {
				*arg_4 = 0x452;
				status = S_OK;
				goto done;
			}
			status = ExtendGracePeriod(arg_0);
			if (SUCCEEDED(status) && arg_10)
				*arg_10 = TRUE;
			result = arg_0->sub_1053D0D(arg_8);
			if (result) {
status_from_result:
				status = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, result);
				goto done;
			}
			sub_1045FAC();
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1012, 0, 0, 0, 0);
			*arg_4 = 1;
		} else {
			result = arg_0->sub_1053D0D(arg_8);
			if (result) {
				status = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, result);
				goto done;
			}
			sub_1045FAC();
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1012, 0, 0, 0, 0);
			status = TRUE;
			*arg_4 = 1;
		}
	}
done:
	return status;
}

HRESULT sub_10484DF(CWPALicenseManager* arg_0, HWID* arg_4, DWORD arg_8, DWORD arg_C) {
	WCHAR var_98[0x40];
	WCHAR Dest[10];
	DWORD var_4 = 0xA28;
	HRESULT status = sub_104820A(arg_0, &var_4, dword_1075D18, arg_4, 0, 0);
	if (FAILED(status)) {
		wsprintf(var_98, L"0x%x", status);
		_itow(arg_8, Dest, 10);
		sub_1046EB1(arg_8, arg_C, 2, 0xC0000000 | 1008, 0, 0, 2, Dest, var_98);
		return S_OK;
	}
	if (var_4 == 1) {
		if (arg_8) {
			wsprintf(var_98, L"%u", arg_8);
			sub_1046EB1(arg_8, arg_C, 2, 0x80000000 | 1005, 0, 0, 1, var_98);
		} else {
			sub_1046EB1(arg_8, arg_C, 2, 0xC0000000 | 1011, 0, 0, 0, 0);
		}
	} else {
		DWORD tmp = 0;
		status = sub_1045C98(arg_0, 0, 0, arg_C, &tmp, 1);
		if (FAILED(status)) {
			wsprintf(var_98, L"1 0x%x", status);
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_98);
		} else {
			sub_10461F2(0x7FFFFFFF, arg_C, tmp);
		}
	}
	return S_OK;
}

HRESULT sub_1048717(CWPALicenseManager* arg_0, HWID* arg_4, DWORD arg_8, DWORD arg_C) {
	WCHAR var_20C[MAX_PATH];
	DWORD var_4 = 0xA28;
	HRESULT status = sub_104820A(arg_0, &var_4, dword_1075D18, arg_4, 0, 0);
	if (FAILED(status)) {
		wsprintf(var_20C, L"0x%x", status);
		sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_20C);
		return status;
	}
	if (var_4 == 1) {
		sub_1046EB1(0, 0, 1, arg_8, 0, 0, 0, 0);
		return E_WPA_ERROR_B012;
	}
	if (var_4 == 0x452) {
		DWORD tmp = 0;
		status = sub_1045C98(arg_0, 0, 0, arg_C, &tmp, 1);
		if (FAILED(status)) {
			wsprintf(var_20C, L"2 0x%x", status);
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_20C);
		} else {
			sub_10461F2(0x7FFFFFFF, arg_C, tmp);
		}
		return S_OK;
	} else {
		return E_WPA_ERROR_B012;
	}
}

static bool __forceinline WPAInline2(HDESK arg_0, HDESK arg_4, LPWSTR arg_8, LPVOID arg_C, HANDLE hUserToken, DWORD arg_24, DWORD* arg_28, DWORD FreeBytesAvailableToCaller_Hi, DWORD var_30, HRESULT* _arg_18, DWORD* _arg_24, DWORD* edi)
{
	if (!ImpersonateLoggedOnUser(hUserToken)) {
		return false;
	}
	*edi = sub_1042A82();
	RevertToSelf();
	sub_10417B4(*edi, var_30, _arg_24, arg_28);
	if (*_arg_24) {
		return false;
	}
	*_arg_18 = sub_104201C(arg_0, arg_4, arg_8, arg_C, hUserToken, FreeBytesAvailableToCaller_Hi);
	if (FAILED(*_arg_18)) {
		return false;
	}
	return true;
}

HRESULT sub_10488DC(HDESK arg_0, HDESK arg_4, LPWSTR arg_8, LPVOID arg_C, HANDLE hUserToken, HWND hWnd_, int arg_18, int arg_1C, DWORD* arg_20, DWORD* arg_24, DWORD* arg_28, DWORD* arg_2C) {
	if (!arg_20 || !arg_24) {
		return E_POINTER;
	}
	*arg_20 = 0;
	*arg_24 = 0;
	hWnd = hWnd_;
	sub_10461F2(0, 0, 0x7FFFFFFF);
	AutoPtr<CWPALicenseManager> var_20 = new CWPALicenseManager;
	if (!var_20) {
		return E_OUTOFMEMORY;
	}
	DWORD var_58 = 0xFCD7E8A8;
	DWORD errcode = var_20.get()->sub_1053728(&var_58, sizeof(var_58));
	if (errcode) {
		return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, errcode);
	}
	if (!dword_1075D18) {
		HRESULT status = sub_10411F8(0, 0, &dword_1075D18);
		if (FAILED(status)) {
			return status;
		}
	}
	{
	bool _arg_14 = false;
	DWORD var_24 = 0xA28;
	DWORD var_10 = 0;
	DWORD FreeBytesAvailableToCaller_Hi = 0;
	DWORD var_30 = 0;
	DWORD TotalNumberOfBytes_Hi = 0;
	DWORD var_50 = 0;
	DWORD var_54 = 0;
	BOOL var_34 = FALSE;
	DWORD TotalNumberOfFreeBytes_Hi = 0;
	HRESULT var_14;
	WCHAR var_2D8[0x40];
	WCHAR Str[0x18];
	CWPAProductChannelInfo var_74;
	HWID var_4C;
	do {
		++TotalNumberOfFreeBytes_Hi;
		var_14 = sub_105E81B(Str, 0x18, &var_50, &var_54, &var_34, &var_74);
		if (FAILED(var_14)) {
			HRESULT status2 = RestorePIDRegValues();
			if (FAILED(status2)) {
				wsprintf(var_2D8, L"1: 0x%x", status2);
				sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_2D8);
			}
		} else {
			if (TotalNumberOfFreeBytes_Hi == 1) {
				BackupPIDRegValues();
			}
		}
	} while (TotalNumberOfFreeBytes_Hi != 2 && FAILED(var_14));
	if (FAILED(var_14)) {
		wsprintf(var_2D8, L"8: 0x%x", var_14);
		sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_2D8);
		if (var_14 != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) && var_14 != E_WPA_ERROR_B039) {
			return var_14;
		}
		var_30 = 2;
		_arg_14 = true;
		FreeBytesAvailableToCaller_Hi = 1;
		sub_1045FAC();
	} else {
		dword_1075D18 = _wtol(Str);
		*arg_20 = var_74.dwDaysForActivation;
		*arg_24 = var_74.dwDaysForEval;
		if (*arg_20 > *arg_24 && *arg_20 != 0x7FFFFFFF) {
			dword_1075D24 = 1;
		}
		if (var_74.dwLicenseType == 5 && sub_104F0CA(WPAFileType0, 0, 0, 0, 0, 0)) {
			return sub_1047539(var_20, &var_74, arg_20, arg_24, &var_10, &_arg_14, &var_24);
		}
		if (var_74.dwLicenseType == 1 && var_74.dwDaysForActivation == 0x7FFFFFFF) {
			HRESULT status = WPACanUseVolumeLicense();
			if (FAILED(status)) {
				return status;
			}
			if (arg_2C) {
				status = sub_1051879(0, Str, var_34, arg_2C);
				if (FAILED(status)) {
					*arg_2C = -1;
				}
			}
			return sub_1047539(var_20, &var_74, arg_20, arg_24, &var_10, &_arg_14, &var_24);
		}
		if (var_74.dwLicenseType == 6) {
			HRESULT status = WPACanUseEmbeddedLicense();
			if (FAILED(status)) {
				return status;
			}
			return sub_1047539(var_20, &var_74, arg_20, arg_24, &var_10, &_arg_14, &var_24);
		}
		sub_105AB66(&var_4C);
		if (!sub_105ACAD(&var_4C)) {
			return E_WPA_ERROR_0500;
		}
		if (var_34)
			sub_105DB4E(Str, var_50);
		DWORD err = var_20.get()->sub_1053A3C(&var_4C, 8);
		if (err) {
			return E_WPA_ERROR_0507;
		}
		err = var_20.get()->sub_10552D8(dword_1075D18, Str, 0x30);
		if (err) {
			return E_WPA_ERROR_0507;
		}
		do { // not a real loop, just introduce a block
			DWORD _arg_2C = 0;
			var_14 = sub_104820A(var_20, &var_24, dword_1075D18, &var_4C, &_arg_2C, Str);
			if (FAILED(var_14)) {
				var_30 = 1;
				_arg_14 = true;
				break;
			}
			BOOL _arg_24 = (var_24 == 0x452 || *arg_20 >= sub_10446D6(0));
			CProtectedRegistryEx TotalNumberOfFreeBytes_;
			CWPATimes var_310;
			if (_arg_2C || SUCCEEDED(TotalNumberOfFreeBytes_.sub_1044389(&var_310))) {
				TotalNumberOfBytes_Hi = 1;
				_arg_24 = TRUE;
				*arg_20 = 3;
			}
			var_14 = sub_1045C98(var_20, TotalNumberOfBytes_Hi, _arg_2C, *arg_24, &var_10, _arg_24);
			if (arg_18) {
				if (var_14 == E_WPA_ERROR_0502) {
					sub_1041B36(0x78, 0, 0x10);
					return E_WPA_ERROR_B012;
				}
				if ((var_14 == E_WPA_ERROR_0501 || SUCCEEDED(var_14)) && *arg_24 <= sub_10446D6(0)) {
					sub_1041B36(0x69, 0, 0);
					TerminateProcess(GetCurrentProcess(), STATUS_EVALUATION_EXPIRATION);
					return E_WPA_ERROR_0505;
				}
			}
			bool good;
			if (_arg_24 || SUCCEEDED(var_14)) {
				sub_1042932(&var_74, var_24, var_10, arg_20, arg_24, &_arg_14);
				sub_10461F2(*arg_20, *arg_24, var_10);
				good = true;
			} else {
				var_30 = 4;
				_arg_14 = true;
				sub_10461F2(0, *arg_24 - var_10, var_10);
				good = false;
			}
			if (!good) {
				*arg_20 = 0;
				*arg_24 = (*arg_24 > var_10 ? *arg_24 - var_10 : 0);
			}
		} while (0);
	}
	if (*arg_20 == 0x7FFFFFFF && *arg_24 == 0x7FFFFFFF || !arg_18 && !FreeBytesAvailableToCaller_Hi) {
		return 0;
	}
	{
	HRESULT _arg_18 = E_WPA_ERROR_B012;
	DWORD __arg_24 = 2;
	DWORD edi;
	if (_arg_14) {
		var_20.get()->sub_1053D0D(dword_1075D18);
		if (!WPAInline2(arg_0, arg_4, arg_8, arg_C, hUserToken, *arg_24, arg_28, FreeBytesAvailableToCaller_Hi, var_30, &_arg_18, &__arg_24, &edi))
			return _arg_18;
		if (edi) {
			_arg_18 = sub_1048717(var_20, &var_4C, 0xC0000000 | 1002, *arg_24);
		} else {
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1001, 0, 0, 0, 0);
			_arg_18 = E_WPA_ERROR_B012;
		}
		return _arg_18;
	}
	if (!*arg_24) {
		sub_1046EB1(0, 0, 1, 0xC0000000 | 1003, 0, 0, 0, 0);
		sub_1041B36(0x69, 0, 0);
		TerminateProcess(GetCurrentProcess(), STATUS_EVALUATION_EXPIRATION);
		return E_WPA_ERROR_0505;
	}
	if (dword_1075D24) {
		sub_10461F2(0x7FFFFFFF, *arg_24, var_10);
	}
	if (!*arg_20) {
		if (!WPAInline2(arg_0, arg_4, arg_8, arg_C, hUserToken, *arg_24, arg_28, FreeBytesAvailableToCaller_Hi, var_30, &_arg_18, &__arg_24, &edi))
			return _arg_18;
		if (edi) {
			_arg_18 = sub_1048717(var_20, &var_4C, 0xC0000000 | 1009, *arg_24);
		} else {
			sub_1046EB1(0, 0, 1, 0xC0000000 | 1004, 0, 0, 0, 0);
			_arg_18 = E_WPA_ERROR_B012;
		}
		return _arg_18;
	}
	WCHAR var_13C[0x40];
	if (*arg_20 <= 7) {
		sub_10432CC(977, 1);
		DWORD _arg_20 = 0;
		do {
			if (!ImpersonateLoggedOnUser(hUserToken)) break;
			_arg_20 = sub_1042A82();
			RevertToSelf();
			sub_10425F4(_arg_20, TotalNumberOfBytes_Hi, &__arg_24, *arg_20, arg_28);
			bool x = false;
			HRESULT eax = 0;
			if (__arg_24 == 0) {
				eax = sub_104201C(arg_0, arg_4, arg_8, arg_C, hUserToken, FreeBytesAvailableToCaller_Hi);
			} else if (__arg_24 == 3) {
				x = true;
			}
			if (x) return E_WPA_ERROR_B012;
			if (eax == HRESULT_FROM_WIN32(ERROR_LOGIN_TIME_RESTRICTION))
				return HRESULT_FROM_WIN32(ERROR_LOGIN_TIME_RESTRICTION);
		} while (0);
		if (_arg_20) {
			sub_10484DF(var_20, &var_4C, *arg_20, *arg_24);
		} else if (*arg_20) {
			wsprintf(var_13C, L"%u", *arg_20);
			sub_1046EB1(*arg_20, *arg_24, 2, 0x80000000 | 1005, 0, 0, 1, var_13C);
		} else {
			sub_1046EB1(*arg_20, *arg_24, 2, 0xC0000000 | 1011, 0, 0, 0, 0);
		}
		return S_OK;
	}
	if (*arg_24 <= 35) {
		volatile DWORD _pBlock;
		bool set;
		if (dword_1075D24) {
			_pBlock = *arg_24;
			set = true;
		} else {
			set = false;
		}
		if (!set) {
			if (*arg_24 >= 5) {
				_pBlock = *arg_24 - 5;
			} else {
				_pBlock = 0;
			}
		}
		sub_10423EA(_pBlock);
		wsprintf(var_13C, L"%u", _pBlock);
		sub_1046EB1(*arg_20, *arg_24, 2, 0x80000000 | 1007, 0, 0, 1, var_13C);
		return S_OK;
	}
		if (!dword_1075D24 && *arg_20 != 0x7FFFFFFF) {
			wsprintf(var_13C, L"%u", *arg_20);
			sub_1046EB1(*arg_20, *arg_24, 2, 0x80000000 | 1005, 0, 0, 1, var_13C);
		}
		if (!dword_1075D24 && *arg_24 != 0x7FFFFFFF) {
			wsprintf(var_13C, L"%u", *arg_24 >= 5 ? *arg_24 - 5 : 0);
			sub_1046EB1(*arg_20, *arg_24, 2, 0x80000000 | 1007, 0, 0, 1, var_13C);
		}
	}
	}
	return S_OK;
}

extern BOOL sub_10498CE(void) {
	DWORD var_4 = 0;
	DWORD cbNeeded = 0;
	DWORD var_10 = 0x400;
	LPDWORD var_C = (LPDWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, var_10);
	while (!EnumProcesses(var_C, var_10, &cbNeeded)) {
		var_4 = GetLastError();
		if (var_4 != ERROR_INSUFFICIENT_BUFFER) {
			break;
		}
		if (var_C) {
			HeapFree(GetProcessHeap(), 0, var_C);
		}
		var_C = (LPDWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbNeeded);
		if (var_C) {
			var_10 = cbNeeded;
			var_4 = 0;
		}
	}
	if (!var_C) {
		return FALSE;
	}
	if (var_4) {
		HeapFree(GetProcessHeap(), 0, var_C);
		return FALSE;
	}
	DWORD dwTheirSessionId = 0xFFFFFFFF;
	DWORD dwOurSessionId = 0xFFFFFFFF;
	HMODULE hModule = NULL;
	BOOL result = FALSE;
	WCHAR ModuleBaseName[MAX_PATH];
	if (ProcessIdToSessionId(GetCurrentProcessId(), &dwOurSessionId)) {
		for (DWORD i = 0, ProcessCount = cbNeeded / 4; i < ProcessCount; i++) {
			dwTheirSessionId = 0xFFFFFFFF;
			if (!ProcessIdToSessionId(var_C[i], &dwTheirSessionId)) {
				continue;
			}
			if (dwTheirSessionId != dwOurSessionId) {
				continue;
			}
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, var_C[i]);
			if (hProcess
				&& EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded)
				&& GetModuleBaseName(hProcess, hModule, ModuleBaseName, MAX_PATH))
			{
				DWORD tmp = sub_1042CE7(ModuleBaseName);
				// looks weird, functionally equivalent to just if (tmp),
				// but gives slightly different compiled code that matches the target binary
				if (tmp ? tmp : tmp) {
					DWORD var1 = 0, var2 = 0, var3;
					HRESULT r = sub_10488DC(0, 0, 0, 0, 0, NULL, 0, 0, &var1, &var2, &var3, 0);
					if (FAILED(r) || var1 == 0 || var2 == 0) {
						result = TRUE;
						TerminateProcess(hProcess, 1);
					}
				}
			}
			CloseHandle(hProcess);
		}
	}
	HeapFree(GetProcessHeap(), 0, var_C);
	return result;
}

extern HRESULT sub_1049CA1(HDESK arg_0, HDESK arg_4, LPWSTR arg_8, LPVOID arg_C, HANDLE hUserToken, HWND hWnd, int arg_18, int arg_1C, DWORD* arg_20, DWORD* arg_24, DWORD* arg_28) {
	DWORD var_4 = 0;
	HRESULT result = sub_10488DC(arg_0, arg_4, arg_8, arg_C, hUserToken, hWnd, arg_18, arg_1C, arg_20, arg_24, arg_28, &var_4);
	if (hThread) {
		ResumeThread(hThread);
		CloseHandle(hThread);
		hThread = NULL;
	}
	if (SUCCEEDED(result)) {
		if (*arg_20 == 0x7FFFFFFF && *arg_24 == 0x7FFFFFFF) {
			KillTimer(hWnd, 976);
		} else {
			DWORD TimeInterval = 3600000 * ((GetTickCount() & 7) + 1);
			SetTimer(hWnd, 976, TimeInterval, NULL);
		}
		if (var_4 == 0xFFFFFFFF || var_4 & 1) {
			DisplayNagMessage();
		}
		goto exit;
	}
	if (result == HRESULT_FROM_WIN32(ERROR_LOGIN_TIME_RESTRICTION) || result == E_WPA_ERROR_B012) {
		goto exit;
	}
	WCHAR var_20C[MAX_PATH];
	wsprintf(var_20C, L"0x%x", result);
	// TODO: create wpaevents.mc, MessageId=1000 Severity=Error SymbolicName=???
	sub_1046EB1(0, 0, 1, 0xC0000000 | 1000, 0, 0, 1, var_20C);
	if (WinStationIsHelpAssistantSession(NULL, 0xFFFFFFFF)) {
		goto exit;
	}
	{
		DWORD edi;
		if (result == 0x80040507 || result == 0x80040508) {
			edi = 0x71;
		} else if (result == 0x80040509) {
			edi = 0x70;
		} else {
			edi = 0x72;
		}
		LPWSTR lpCaption = NULL;
		LPWSTR lpMsgFormat = NULL;
		LPWSTR lpMsg = NULL;
		DWORD MaxMsgSize = 0x840;
		if (!sub_10414F0(0x66, &lpCaption, 0x40, 0)
			&& !sub_10414F0(edi, &lpMsgFormat, 0x800, 0)
			&& (lpMsg = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MaxMsgSize * sizeof(WCHAR))) != NULL)
		{
			lpMsg[MaxMsgSize - 1] = 0;
			_snwprintf(lpMsg, MaxMsgSize - 1, lpMsgFormat, result);
			Fusion_MessageBox(GetDesktopWindow(), lpMsg, lpCaption, MB_TOPMOST | MB_SYSTEMMODAL | MB_ICONSTOP);
		}
		if (lpCaption) {
			HeapFree(GetProcessHeap(), 0, lpCaption);
		}
		if (lpMsgFormat) {
			HeapFree(GetProcessHeap(), 0, lpMsgFormat);
		}
		if (lpMsg) {
			HeapFree(GetProcessHeap(), 0, lpMsg);
		}
	}
exit:
	return result;
}

void checkstatus_do_nothing4() { checkstatus_do_nothing3(); }
void checkstatus_do_nothing3() { checkstatus_do_nothing2(); }
void checkstatus_do_nothing2() { checkstatus_do_nothing(); }
void checkstatus_do_nothing() {}
