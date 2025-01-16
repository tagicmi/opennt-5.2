#include "precomp.h"
#pragma hdrstop
#include <setupapi.h>
#include <devguid.h>
#include <iphlpapi.h>
#include "lichwid.h"
#include "../liclib/bios.h" // sub_104E349, probably should be in a separate include

HWID dword_1075D38 = {0};
BOOL dword_1075D40 = FALSE;
BOOL dword_1075D44 = FALSE;
HWID g_hwidLastVerified = {0};
BOOL g_fhwidLastVerifiedWasCreeping = FALSE;
BOOL g_fSystemIsDockable = FALSE;
BOOL g_fSystemTypeDetected = FALSE;


#ifndef _X86_
extern BOOL WPAHasCPUID(void);
extern void GetCPUID(DWORD vendor1, DWORD vendor2, DWORD vendor3);
extern void GetCPUIDModel(DWORD vendor1, DWORD vendor2);
extern void GetCPUIDStepping(DWORD vendor1, DWORD vendor2);
#endif

struct struc_1 {
	char field_0[12];
	int field_C, field_10, field_14, field_18;
};
const struc_1 stru_1019ED0[] = {
	{"CDROM", 0, 7, 16, 11},
	{"DiskDrive", 0, 7, 5, 1},
	{"Display", 1, 5, 0, 1},
	{"hdc", 1, 4, 0, 1},
	{"SCSIAdapter", 1, 5, 23, 1},
};

void sub_10584F3(LPCWSTR arg_0, LPSTR pszResult, DWORD cchResult) {
	pszResult[cchResult - 1] = 0;
	_snprintf(pszResult, cchResult - 1, "%S", arg_0);
}

void sub_10585B2(LPCSTR arg_0, LPWSTR pszResult, DWORD cchResult) {
	pszResult[cchResult - 1] = 0;
	_snwprintf(pszResult, cchResult - 1, L"%S", arg_0);
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_7() {
__asm {
                mov     eax, 3
BEGIN_SCP_SEGMENT_3_7_0_10_00_00:
                mov     ebx, 7
                retn
}
}
#endif
#pragma warning(pop)

DWORD sub_105867E(HWID* arg_0) {
	if (!dword_1075D40) {
		return 0;
	}
	if (memcmp(&dword_1075D38, arg_0, sizeof(*arg_0)) == 0) {
		return 2;
	}
	BOOL esi = FALSE;
	int _arg_0 = 7;
	if (g_fSystemIsDockable || arg_0->dockable) {
		_arg_0 = 4;
		esi = TRUE;
	}
	int edx = 0;
	if (arg_0->ver == 1) {
		if (!esi) {
			edx += (arg_0->scsi_adapter_id == dword_1075D38.scsi_adapter_id);
			edx += (arg_0->hdc_id == dword_1075D38.hdc_id);
			edx += (arg_0->display_id == dword_1075D38.display_id);
		}
		edx += (arg_0->cpu_model == dword_1075D38.cpu_model);
		edx += (arg_0->cdrom_id == dword_1075D38.cdrom_id);
		edx += (arg_0->volume_serial == dword_1075D38.volume_serial);
		edx += (arg_0->cpu_serial == dword_1075D38.cpu_serial);
		edx += (arg_0->disk_id == dword_1075D38.disk_id);
		edx += (arg_0->mem == dword_1075D38.mem);
		if (dword_1075D44) {
			edx += 3 * (arg_0->network_mac == dword_1075D38.network_mac);
		}
	}
	return edx >= _arg_0;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_7() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_7:
                mov     edx, 7
                retn
}
}
#endif
#pragma warning(pop)

DWORD WPAGetPhysMemAmountLog()
{
	MEMORYSTATUS status = {0};
	GlobalMemoryStatus(&status);
	SIZE_T megabytes = (status.dwTotalPhys >> 25);
	megabytes = (megabytes + 1) << 5;
	if (megabytes > 1024 || megabytes == 0)
		return 7;
	if (megabytes > 512)
		return 6;
	if (megabytes > 256)
		return 5;
	if (megabytes > 128)
		return 4;
	if (megabytes > 64)
		return 3;
	if (megabytes > 32)
		return 2;
	return 1;
}

struct CWPAHWIDCollector
{
	DWORD field_0;
	int field_4;
	HWID field_8;
	HWID field_10;
	HWID field_18;
	HWID* field_20;
	BOOL (*field_24)(LPCVOID, LPDWORD, CWPAHWIDCollector*);
};

void sub_10589DB(CWPAHWIDCollector* arg_0) {
	char logicalDrives[MAX_PATH];
	arg_0->field_4 = 1;
	int ret = GetLogicalDriveStringsA(MAX_PATH - 1, logicalDrives);
	if (ret == 0 || ret >= MAX_PATH) {
		return;
	}
	char* p = logicalDrives;
	do {
		if (GetDriveTypeA(p) == DRIVE_FIXED) {
			WCHAR RootPathName[4];
			sub_10585B2(p, RootPathName, 4);
			DWORD volumeSerialNumber;
			if (GetVolumeInformation(RootPathName, NULL, 0, &volumeSerialNumber, NULL, NULL, NULL, 0)) {
				char text[10];
				wsprintfA(text, "%04X-%04X", volumeSerialNumber >> 16, volumeSerialNumber & 0xFFFF);
				if (arg_0->field_24(text, NULL, arg_0)) {
					--arg_0->field_4;
				}
			}
		}
		if (arg_0->field_4 != 0) {
			p += lstrlenA(p) + 1;
		}
	} while (*p && arg_0->field_4);
}

void sub_1058BA5(CWPAHWIDCollector* arg_0) {
	arg_0->field_4 = 1;
	char iphlpapi[] = "\\iphlpapi.dll";
	char dllname[MAX_PATH+14];
	DWORD size = 0;
	DWORD ret = GetSystemDirectoryA(dllname, sizeof(dllname) / sizeof(dllname[0]));
	if (ret == 0 || ret + 15 >= sizeof(dllname) / sizeof(dllname[0])) {
		return;
	}
	lstrcatA(dllname, iphlpapi);
	HMODULE hDll = LoadLibraryA(dllname);
	if (hDll != NULL) {
		typedef DWORD (WINAPI *GetIfTable_t)(MIB_IFTABLE*, ULONG*, BOOL);
		GetIfTable_t GetIfTable = (GetIfTable_t)GetProcAddress(hDll, "GetIfTable");
		if (GetIfTable != NULL) {
			DWORD err = GetIfTable(NULL, &size, TRUE);
			if (size != 0 && err == ERROR_INSUFFICIENT_BUFFER) {
				MIB_IFTABLE* data = (MIB_IFTABLE*)HeapAlloc(GetProcessHeap(), 0, size);
				if (data != NULL) {
					if (!GetIfTable(data, &size, TRUE)) {
						for (DWORD i = 0; i < data->dwNumEntries; i++) {
							if (arg_0->field_4 <= 0) {
								break;
							}
							if (data->table[i].dwPhysAddrLen && lstrcmpA((LPCSTR)data->table[i].bPhysAddr, "DEST") != 0) {
								if (arg_0->field_24(data->table[i].bPhysAddr, NULL, arg_0)) {
									--arg_0->field_4;
								}
							}
						}
					}
					HeapFree(GetProcessHeap(), 0, data);
				}
			}
		}
		FreeLibrary(hDll);
	}
}
#ifdef _X86_
BOOL WPAHasCPUID() {
	BOOL cpuidFlag = 0;
	__asm {
                pushfd
                pop     eax
                mov     ebx, eax
                xor     eax, 200000h
                push    eax
                popfd
                pushfd
                pop     eax
                push    ebx
                popfd
                xor     eax, ebx
                mov     cpuidFlag, eax
	}
	if (cpuidFlag != 0) {
		cpuidFlag = TRUE;
	}
	return cpuidFlag;
}
#endif

void sub_1058EF8(LPCWSTR arg_0, LPWSTR arg_4, DWORD arg_8) {
	arg_4[0] = 0;
	DWORD eax = (arg_8 > (DWORD)lstrlen(arg_0) + 1) ? lstrlen(arg_0) + 1 : arg_8;
	lstrcpyn(arg_4, arg_0, eax);
	_wcsupr(arg_4);
}

DWORD sub_105905A(LPCSTR arg_0, LONG dwCount, LONG dwFirst, LONG dwStep) {
	BYTE hash[16];
	sub_104E349(arg_0, lstrlenA(arg_0), hash);
	DWORD result = 0;
	BYTE masks[8] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80};
	LONG bit = dwFirst;
	for (LONG i = 0; i < dwCount; i++, bit += dwStep) {
		result <<= 1;
		if (hash[bit / 8] & masks[(bit / 8 * 8 - bit + 7) % 8]) {
			result |= 1;
		}
	}
	return result % ((1 << dwCount) - 1) + 1;
}

BOOL FIsComputerDockableNT()
{
	BOOL ret = TRUE;
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfile(&hwProfileInfo)) {
		DWORD tmp1 = (hwProfileInfo.dwDockInfo & DOCKINFO_USER_SUPPLIED);
		DWORD tmp2 = (hwProfileInfo.dwDockInfo & DOCKINFO_DOCKED);
		DWORD tmp3 = (hwProfileInfo.dwDockInfo & DOCKINFO_UNDOCKED);
		if (tmp1 || tmp2 && tmp3) {
			ret = FALSE;
			HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PCMCIA, NULL, NULL, DIGCF_PRESENT);
			if (hDevInfo != INVALID_HANDLE_VALUE) {
				SP_DEVINFO_DATA data;
				data.cbSize = sizeof(data);
				if (SetupDiEnumDeviceInfo(hDevInfo, 0, &data)) {
					ret = TRUE;
				}
				SetupDiDestroyDeviceInfoList(hDevInfo);
				return ret;
			}
		}
	} else {
		ret = FALSE;
	}
	return ret;
}

BOOL sub_10593A3(LPCVOID arg_0, LPDWORD ignored, CWPAHWIDCollector* arg_8) {
	DWORD eax = sub_105905A((LPCSTR)arg_0, 10, 3, 1);
	if (arg_8->field_0) {
		if (!arg_8->field_8.volume_serial) {
			arg_8->field_20->volume_serial = eax;
			arg_8->field_8.volume_serial = 1;
			return TRUE;
		}
	} else {
		arg_8->field_10.volume_serial = 1;
		if (!arg_8->field_18.volume_serial) {
			dword_1075D38.volume_serial = eax;
			arg_8->field_18.volume_serial = 1;
		}
		if (arg_8->field_20->volume_serial == eax) {
			arg_8->field_8.volume_serial = 1;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL sub_1059512(LPCVOID arg_0, LPDWORD ignored, CWPAHWIDCollector* arg_8) {
	CONST BYTE* pMac = (CONST BYTE*)arg_0;
	char var_104[MAX_PATH];
	wsprintfA(var_104, "%02X%02X%02X%02X%02X%02X", pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5]);
	DWORD eax = sub_105905A(var_104, 10, 1, 1);
	if (arg_8->field_0) {
		if (!arg_8->field_8.network_mac) {
			arg_8->field_20->network_mac = eax;
			arg_8->field_8.network_mac = 1;
			return TRUE;
		}
	} else {
		arg_8->field_10.network_mac = 1;
		if (!arg_8->field_18.network_mac) {
			dword_1075D38.network_mac = eax;
			arg_8->field_18.network_mac = 1;
		}
		if (arg_8->field_20->network_mac == eax) {
			arg_8->field_8.network_mac = 1;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL sub_10596EA(LPCVOID arg_0, LPDWORD arg_4, CWPAHWIDCollector* arg_8) {
	DWORD eax = sub_105905A((LPCSTR)arg_0, stru_1019ED0[*arg_4].field_10, stru_1019ED0[*arg_4].field_14, stru_1019ED0[*arg_4].field_18);
	BOOL result = FALSE;
	if (g_fSystemIsDockable && *arg_4 >= 2 && *arg_4 <= 4) {
		return FALSE;
	}
	if (arg_8->field_0) {
		switch (*arg_4) {
		case 4:
			if (!arg_8->field_8.scsi_adapter_id) {
				arg_8->field_20->scsi_adapter_id = eax;
				arg_8->field_8.scsi_adapter_id = 1;
				result = TRUE;
			}
			break;
		case 3:
			if (!arg_8->field_8.hdc_id) {
				arg_8->field_20->hdc_id = eax;
				arg_8->field_8.hdc_id = 1;
				result = TRUE;
			}
			break;
		case 2:
			if (!arg_8->field_8.display_id) {
				arg_8->field_20->display_id = eax;
				arg_8->field_8.display_id = 1;
				result = TRUE;
			}
			break;
		case 1:
			if (!arg_8->field_8.disk_id) {
				arg_8->field_20->disk_id = eax;
				arg_8->field_8.disk_id = 1;
				result = TRUE;
			}
			break;
		case 0:
			if (!arg_8->field_8.cdrom_id) {
				arg_8->field_20->cdrom_id = eax;
				arg_8->field_8.cdrom_id = 1;
				result = TRUE;
			}
			break;
		default:
			return FALSE;
		}
		return result;
	} else {
		switch (*arg_4) {
		case 0:
			arg_8->field_10.cdrom_id = 1;
			if (!arg_8->field_18.cdrom_id) {
				dword_1075D38.cdrom_id = eax;
				arg_8->field_18.cdrom_id = 1;
			}
			if (!arg_8->field_8.cdrom_id) {
				result = (arg_8->field_20->cdrom_id == eax);
				arg_8->field_8.cdrom_id = result;
			}
			break;
		case 1:
			arg_8->field_10.disk_id = 1;
			if (!arg_8->field_18.disk_id) {
				dword_1075D38.disk_id = eax;
				arg_8->field_18.disk_id = 1;
			}
			if (!arg_8->field_8.disk_id) {
				result = (arg_8->field_20->disk_id == eax);
				arg_8->field_8.disk_id = result;
			}
			break;
		case 2:
			arg_8->field_10.display_id = 1;
			if (!arg_8->field_18.display_id) {
				dword_1075D38.display_id = eax;
				arg_8->field_18.display_id = 1;
			}
			if (!arg_8->field_8.display_id) {
				result = (arg_8->field_20->display_id == eax);
				arg_8->field_8.display_id = result;
			}
			break;
		case 3:
			arg_8->field_10.hdc_id = 1;
			if (!arg_8->field_18.hdc_id) {
				dword_1075D38.hdc_id = eax;
				arg_8->field_18.hdc_id = 1;
			}
			if (!arg_8->field_8.hdc_id) {
				result = (arg_8->field_20->hdc_id == eax);
				arg_8->field_8.hdc_id = result;
			}
			break;
		case 4:
			arg_8->field_10.scsi_adapter_id = 1;
			if (!arg_8->field_18.scsi_adapter_id) {
				dword_1075D38.scsi_adapter_id = eax;
				arg_8->field_18.scsi_adapter_id = 1;
			}
			if (!arg_8->field_8.scsi_adapter_id) {
				result = (arg_8->field_20->scsi_adapter_id == eax);
				arg_8->field_8.scsi_adapter_id = result;
			}
			break;
		default:
			return FALSE;
		}
		return result;
	}
}

struct CWPACPUInfo {
	char m_Model[MAX_PATH];
	DWORD m_Serial;
};

BOOL sub_1059B88(LPCVOID arg_0, LPDWORD ignored, CWPAHWIDCollector* arg_8) {
	CWPACPUInfo* info = (CWPACPUInfo*)arg_0;
	DWORD eax = sub_105905A(info->m_Model, 3, 0, 1);
	if (arg_8->field_0) {
		if (!arg_8->field_8.cpu_serial) {
			arg_8->field_20->cpu_serial = info->m_Serial;
			arg_8->field_8.cpu_serial = 1;
			arg_8->field_20->cpu_model = eax;
			arg_8->field_8.cpu_model = 1;
			return TRUE;
		}
	} else {
		arg_8->field_10.cpu_serial = 1;
		arg_8->field_10.cpu_model = 1;
		if (!arg_8->field_18.cpu_model) {
			dword_1075D38.cpu_model = eax;
			arg_8->field_18.cpu_model = 1;
		}
		if (!arg_8->field_18.cpu_serial) {
			dword_1075D38.cpu_serial = info->m_Serial;
			arg_8->field_18.cpu_serial = 1;
		}
		if (arg_8->field_20->cpu_model == eax) {
			arg_8->field_8.cpu_model = 1;
		}
		if (arg_8->field_20->cpu_serial == info->m_Serial || !arg_8->field_20->cpu_serial || !info->m_Serial) {
			arg_8->field_8.cpu_serial = 1;
		}
		if (arg_8->field_8.cpu_model && arg_8->field_8.cpu_serial) {
			return TRUE;
		}
	}
	return FALSE;
}

DWORD CALLBACK WPAGetSingleCPUInfo(LPVOID lpThreadParameter)
{
	CWPAHWIDCollector* arg_0 = (CWPAHWIDCollector*)lpThreadParameter;
	CWPACPUInfo CPUInfo;
	CPUInfo.m_Model[0] = 0;
	CPUInfo.m_Serial = 0;
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	int arch = systemInfo.wProcessorArchitecture;
	if (arch != PROCESSOR_ARCHITECTURE_INTEL) {
		if (arch > 0 && arch <= 3) {
			lstrcpyA(CPUInfo.m_Model, "Non-x86");
		}
	} else {
		if (WPAHasCPUID()) {
			DWORD vendor[4] = {0x0, 0x0, 0x0, 0x0};
#ifdef _X86_
			__asm {
				xor     eax, eax
				xor     ebx, ebx
				xor     ecx, ecx
				xor     edx, edx
				cpuid
				mov	vendor[0*TYPE vendor], ebx
				mov	vendor[1*TYPE vendor], edx
				mov	vendor[2*TYPE vendor], ecx
			}
#else
			GetCPUID(vendor[0], vendor[1], vendor[2]);
#endif
			vendor[3] = 0;
			DWORD var_4 = 0x0, var_1C = 0x0;
#ifdef _X86_
			__asm {
				mov     eax, 1
				xor     ebx, ebx
				xor     ecx, ecx
				xor     edx, edx
				cpuid
				mov     var_4, eax
				mov     var_1C, edx
			}
#else
			GetCPUIDModel(var_4, var_1C);
#endif
			wsprintfA(CPUInfo.m_Model, "%s Family %d Model %d", (char*)vendor, (var_4 >> 8) & 0xF, (var_4 >> 4) & 0xF);
			DWORD var_8 = 0, _var_4 = 0;
			if (!lstrcmpA((char*)vendor, "GenuineIntel") && var_1C & 0x40000) {
#ifdef	_X86_
			__asm {
					mov     eax, 3
					xor     ebx, ebx
					xor     ecx, ecx
					xor     edx, edx
					cpuid
					mov     var_8, ecx
					mov     _var_4, edx
			}
#else
				GetCPUIDStepping(var_8, _var_4);
#endif
				char tmp[MAX_PATH];
				wsprintfA(tmp, "%08X%08X", _var_4, var_8);
				CPUInfo.m_Serial = sub_105905A(tmp, 6, 52, 5);
			}
		} else {
			lstrcpyA(CPUInfo.m_Model, "386/486");
		}
	}
	return arg_0->field_24(&CPUInfo, NULL, arg_0) ? 1 : 0;
}

DWORD sub_105A024(HDEVINFO hDevInfo, const GUID* pClassGuid, CWPAHWIDCollector* arg_8) {
	DWORD err = ERROR_SUCCESS;
	SP_DEVINFO_DATA data;
	data.cbSize = sizeof(data);
	int index;
	for (index = 0; SetupDiEnumDeviceInfo(hDevInfo, index, &data); index++) {
		LPVOID propData = NULL;
		DWORD size = 0;
		if (*pClassGuid != data.ClassGuid) {
			continue;
		}
		for (;;) {
			DWORD propType;
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &data, SPDRP_HARDWAREID, &propType, (BYTE*)propData, size, &size))
				break;
			err = GetLastError();
			if (err != ERROR_INSUFFICIENT_BUFFER)
				break;
			if (propData != NULL) {
				HeapFree(GetProcessHeap(), 0, propData);
			}
			propData = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
			err = ERROR_SUCCESS;
		}
		WCHAR szPropW[MAX_PATH] = {0};
		if (err != ERROR_INVALID_DATA && propData != NULL) {
			sub_1058EF8((LPCWSTR)propData, szPropW, MAX_PATH);
		} else {
			lstrcpy(szPropW, L"..");
		}
		char szPropA[MAX_PATH];
		sub_10584F3(szPropW, szPropA, MAX_PATH);
		DWORD dwDeviceType;
		if (GUID_DEVCLASS_SCSIADAPTER == *pClassGuid) {
			dwDeviceType = 4;
		} else if (GUID_DEVCLASS_HDC == *pClassGuid) {
			dwDeviceType = 3;
		} else if (GUID_DEVCLASS_CDROM == *pClassGuid) {
			dwDeviceType = 0;
		} else if (GUID_DEVCLASS_DISKDRIVE == *pClassGuid) {
			dwDeviceType = 1;
		} else if (GUID_DEVCLASS_DISPLAY == *pClassGuid) {
			dwDeviceType = 2;
		}
		if (arg_8->field_24(szPropA, &dwDeviceType, arg_8)) {
			--arg_8->field_4;
		}
		if (propData != NULL) {
			HeapFree(GetProcessHeap(), 0, propData);
		}
	}
	if (err == ERROR_SUCCESS || err == ERROR_NO_MORE_ITEMS || err == ERROR_INVALID_DATA) {
		err = ERROR_SUCCESS;
	}
	return err;
}

void sub_105A361(CWPAHWIDCollector* arg_0) {
	arg_0->field_4 = 1;
	unsigned long long dwSystemAffinityMask = 0x0, dwProcessAffinityMask = 0x0;
	HANDLE hSelfProcess = GetCurrentProcess();
	if (GetProcessAffinityMask(hSelfProcess, (PDWORD_PTR)dwProcessAffinityMask, (PDWORD_PTR)dwSystemAffinityMask)) {
		DWORD result = 0;
		DWORD dwThreadAffinityMask = 1;
		DWORD dwProcessAffinityMaskCopy = (DWORD)dwProcessAffinityMask;
		do {
			if (dwProcessAffinityMaskCopy == 1) {
				result = WPAGetSingleCPUInfo(arg_0);
			} else {
				DWORD dwThreadId;
				HANDLE hThread = CreateThread(NULL, 0, WPAGetSingleCPUInfo, arg_0, CREATE_SUSPENDED, &dwThreadId);
				if (hThread != NULL) {
					SetThreadAffinityMask(hThread, dwThreadAffinityMask);
					ResumeThread(hThread);
					WaitForSingleObject(hThread, INFINITE);
					GetExitCodeThread(hThread, &result);
					CloseHandle(hThread);
				}
				dwThreadAffinityMask <<= 1;
			}
			dwProcessAffinityMask >>= 1;
			if (result == 1) {
				--arg_0->field_4;
			}
		} while (dwProcessAffinityMask != 0 && arg_0->field_4);
	}
}

void sub_105A573(CWPAHWIDCollector* arg_0) {
	arg_0->field_4 = 5;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hDevInfo != INVALID_HANDLE_VALUE) {
		sub_105A024(hDevInfo, &GUID_DEVCLASS_DISPLAY, arg_0);
		sub_105A024(hDevInfo, &GUID_DEVCLASS_HDC, arg_0);
		sub_105A024(hDevInfo, &GUID_DEVCLASS_SCSIADAPTER, arg_0);
		sub_105A024(hDevInfo, &GUID_DEVCLASS_CDROM, arg_0);
		sub_105A024(hDevInfo, &GUID_DEVCLASS_DISKDRIVE, arg_0);
		SetupDiDestroyDeviceInfoList(hDevInfo);
	}
}

void sub_105A6CC(HWID* arg_0, BOOL arg_4, CWPAHWIDCollector* arg_8) {
	arg_8->field_0 = arg_4;
	arg_8->field_4 = 0;
	arg_8->field_20 = arg_0;
	arg_8->field_8.AsQword = 0;
	arg_8->field_18.AsQword = 0;
	arg_8->field_10.AsQword = 0;
	arg_8->field_24 = sub_10593A3;
	sub_10589DB(arg_8);
	arg_8->field_24 = sub_1059B88;
	sub_105A361(arg_8);
	arg_8->field_24 = sub_10596EA;
	sub_105A573(arg_8);
	if (!arg_4) {
		arg_8->field_8.volume_serial |= 0 == arg_8->field_10.volume_serial && 0 == arg_0->volume_serial;
		arg_8->field_8.cdrom_id |= 0 == arg_8->field_10.cdrom_id && 0 == arg_0->cdrom_id;
		arg_8->field_8.display_id |= 0 == arg_8->field_10.display_id && 0 == arg_0->display_id;
		arg_8->field_8.cpu_serial |= 0 == arg_8->field_10.cpu_serial && 0 == arg_0->cpu_serial;
		arg_8->field_8.disk_id |= 0 == arg_8->field_10.disk_id && 0 == arg_0->disk_id;
		arg_8->field_8.scsi_adapter_id |= 0 == arg_8->field_10.scsi_adapter_id && 0 == arg_0->scsi_adapter_id;
		arg_8->field_8.hdc_id |= 0 == arg_8->field_10.hdc_id && 0 == arg_0->hdc_id;
		arg_8->field_8.cpu_model |= 0 == arg_8->field_10.cpu_model && 0 == arg_0->cpu_model;
		dword_1075D38.mem = WPAGetPhysMemAmountLog();
		arg_8->field_18.mem = 1;
		if (dword_1075D38.mem == arg_0->mem) {
			arg_8->field_8.mem = 1;
		}
		dword_1075D38.dockable = g_fSystemIsDockable;
		arg_8->field_18.dockable = 1;
		if (dword_1075D38.dockable == arg_0->dockable) {
			arg_8->field_8.dockable = 1;
		}
		dword_1075D38.ver = 1;
		arg_8->field_18.ver = 1;
		if (dword_1075D38.ver == arg_0->ver) {
			arg_8->field_8.ver = 1;
		}
		int edx = 0;
		int _arg_0 = 7;
		BOOL esi = FALSE;
		if (g_fSystemIsDockable || arg_0->dockable) {
			_arg_0 = 4;
			esi = TRUE;
		}
		if (arg_8->field_8.ver) {
			if (!esi) {
				edx += arg_8->field_8.scsi_adapter_id;
				edx += arg_8->field_8.hdc_id;
				edx += arg_8->field_8.display_id;
			}
			edx += arg_8->field_8.cpu_model;
			edx += arg_8->field_8.cdrom_id;
			edx += arg_8->field_8.volume_serial;
			edx += arg_8->field_8.cpu_serial;
			edx += arg_8->field_8.disk_id;
			edx += arg_8->field_8.mem;
		}
		if (edx >= _arg_0 || edx < _arg_0 - 3) {
			return;
		}
	}
	arg_8->field_24 = sub_1059512;
	sub_1058BA5(arg_8);
	if (!arg_4) {
		arg_8->field_8.network_mac |= !arg_8->field_10.network_mac && !arg_0->network_mac;
	}
}

void sub_105AB66(HWID* arg_0) {
	if (dword_1075D40 && dword_1075D44) {
		*arg_0 = dword_1075D38;
	} else {
		if (!g_fSystemTypeDetected) {
			g_fSystemIsDockable = FIsComputerDockableNT();
			g_fSystemTypeDetected = TRUE;
		}
		arg_0->AsQword = 0;
		CWPAHWIDCollector Collector;
		sub_105A6CC(arg_0, TRUE, &Collector);
		arg_0->mem = WPAGetPhysMemAmountLog();
		arg_0->dockable = g_fSystemIsDockable;
		arg_0->ver = 1;
	}
	dword_1075D38 = *arg_0;
	dword_1075D40 = TRUE;
	dword_1075D44 = TRUE;
}

BOOL sub_105ACAD(HWID* arg_0) {
	g_hwidLastVerified = *arg_0;
	g_fhwidLastVerifiedWasCreeping = FALSE;
	if (arg_0->ver != 1) {
		return FALSE;
	}
	if (!g_fSystemTypeDetected) {
		g_fSystemIsDockable = FIsComputerDockableNT();
		g_fSystemTypeDetected = 1;
	}
	if (dword_1075D40 && sub_105867E(arg_0)) {
		return TRUE;
	}
	CWPAHWIDCollector Collector;
	sub_105A6CC(arg_0, FALSE, &Collector);
	if (GetSystemMetrics(SM_CLEANBOOT) != 0) {
		return TRUE;
	}
	dword_1075D40 = TRUE;
	if (Collector.field_18.network_mac) {
		dword_1075D44 = TRUE;
	}
	bool dockable = false;
	int edx = 0;
	int v5 = 10;
	int _arg_0 = 7;
	if (g_fSystemIsDockable || arg_0->dockable) {
		v5 = 7;
		_arg_0 = 4;
		dockable = true;
	}
	if (!dockable) {
		edx += Collector.field_8.scsi_adapter_id;
		edx += Collector.field_8.hdc_id;
		edx += Collector.field_8.display_id;
	}
	edx += Collector.field_8.cpu_model;
	edx += Collector.field_8.cdrom_id;
	edx += Collector.field_8.volume_serial;
	edx += Collector.field_8.cpu_serial;
	edx += Collector.field_8.disk_id;
	edx += Collector.field_8.mem;
	if (edx < v5 - 1) {
		g_fhwidLastVerifiedWasCreeping = TRUE;
	}
	edx += 3 * Collector.field_8.network_mac;
	if (edx >= _arg_0) {
		return TRUE;
	} else {
		g_fhwidLastVerifiedWasCreeping = FALSE;
		return FALSE;
	}
}
