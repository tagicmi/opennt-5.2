#include "precomp.h"
#pragma hdrstop
#include <sddl.h>
#include <wchar.h>
#include <math.h>
#include <stddef.h>
#include "lichwid.h"
#include "cidiid.h"
#include "licstoreacl.h"

// license from internet activation must be a certificate chain with this certificate as root
const BYTE byte_1019960[] = {
0x30,0x82,0x04,0x12,0x30,0x82,0x02,0xFA,0xA0,0x03,0x02,0x01,0x02,0x02,0x0F,0x00,
0xC1,0x00,0x8B,0x3C,0x3C,0x88,0x11,0xD1,0x3E,0xF6,0x63,0xEC,0xDF,0x40,0x30,0x0D,
0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x04,0x05,0x00,0x30,0x70,0x31,
0x2B,0x30,0x29,0x06,0x03,0x55,0x04,0x0B,0x13,0x22,0x43,0x6F,0x70,0x79,0x72,0x69,
0x67,0x68,0x74,0x20,0x28,0x63,0x29,0x20,0x31,0x39,0x39,0x37,0x20,0x4D,0x69,0x63,
0x72,0x6F,0x73,0x6F,0x66,0x74,0x20,0x43,0x6F,0x72,0x70,0x2E,0x31,0x1E,0x30,0x1C,
0x06,0x03,0x55,0x04,0x0B,0x13,0x15,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,
0x20,0x43,0x6F,0x72,0x70,0x6F,0x72,0x61,0x74,0x69,0x6F,0x6E,0x31,0x21,0x30,0x1F,
0x06,0x03,0x55,0x04,0x03,0x13,0x18,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,
0x20,0x52,0x6F,0x6F,0x74,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x30,
0x1E,0x17,0x0D,0x39,0x37,0x30,0x31,0x31,0x30,0x30,0x37,0x30,0x30,0x30,0x30,0x5A,
0x17,0x0D,0x32,0x30,0x31,0x32,0x33,0x31,0x30,0x37,0x30,0x30,0x30,0x30,0x5A,0x30,
0x70,0x31,0x2B,0x30,0x29,0x06,0x03,0x55,0x04,0x0B,0x13,0x22,0x43,0x6F,0x70,0x79,
0x72,0x69,0x67,0x68,0x74,0x20,0x28,0x63,0x29,0x20,0x31,0x39,0x39,0x37,0x20,0x4D,
0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,0x20,0x43,0x6F,0x72,0x70,0x2E,0x31,0x1E,
0x30,0x1C,0x06,0x03,0x55,0x04,0x0B,0x13,0x15,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,
0x66,0x74,0x20,0x43,0x6F,0x72,0x70,0x6F,0x72,0x61,0x74,0x69,0x6F,0x6E,0x31,0x21,
0x30,0x1F,0x06,0x03,0x55,0x04,0x03,0x13,0x18,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,
0x66,0x74,0x20,0x52,0x6F,0x6F,0x74,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,
0x79,0x30,0x82,0x01,0x22,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,
0x01,0x01,0x05,0x00,0x03,0x82,0x01,0x0F,0x00,0x30,0x82,0x01,0x0A,0x02,0x82,0x01,
0x01,0x00,0xA9,0x02,0xBD,0xC1,0x70,0xE6,0x3B,0xF2,0x4E,0x1B,0x28,0x9F,0x97,0x78,
0x5E,0x30,0xEA,0xA2,0xA9,0x8D,0x25,0x5F,0xF8,0xFE,0x95,0x4C,0xA3,0xB7,0xFE,0x9D,
0xA2,0x20,0x3E,0x7C,0x51,0xA2,0x9B,0xA2,0x8F,0x60,0x32,0x6B,0xD1,0x42,0x64,0x79,
0xEE,0xAC,0x76,0xC9,0x54,0xDA,0xF2,0xEB,0x9C,0x86,0x1C,0x8F,0x9F,0x84,0x66,0xB3,
0xC5,0x6B,0x7A,0x62,0x23,0xD6,0x1D,0x3C,0xDE,0x0F,0x01,0x92,0xE8,0x96,0xC4,0xBF,
0x2D,0x66,0x9A,0x9A,0x68,0x26,0x99,0xD0,0x3A,0x2C,0xBF,0x0C,0xB5,0x58,0x26,0xC1,
0x46,0xE7,0x0A,0x3E,0x38,0x96,0x2C,0xA9,0x28,0x39,0xA8,0xEC,0x49,0x83,0x42,0xE3,
0x84,0x0F,0xBB,0x9A,0x6C,0x55,0x61,0xAC,0x82,0x7C,0xA1,0x60,0x2D,0x77,0x4C,0xE9,
0x99,0xB4,0x64,0x3B,0x9A,0x50,0x1C,0x31,0x08,0x24,0x14,0x9F,0xA9,0xE7,0x91,0x2B,
0x18,0xE6,0x3D,0x98,0x63,0x14,0x60,0x58,0x05,0x65,0x9F,0x1D,0x37,0x52,0x87,0xF7,
0xA7,0xEF,0x94,0x02,0xC6,0x1B,0xD3,0xBF,0x55,0x45,0xB3,0x89,0x80,0xBF,0x3A,0xEC,
0x54,0x94,0x4E,0xAE,0xFD,0xA7,0x7A,0x6D,0x74,0x4E,0xAF,0x18,0xCC,0x96,0x09,0x28,
0x21,0x00,0x57,0x90,0x60,0x69,0x37,0xBB,0x4B,0x12,0x07,0x3C,0x56,0xFF,0x5B,0xFB,
0xA4,0x66,0x0A,0x08,0xA6,0xD2,0x81,0x56,0x57,0xEF,0xB6,0x3B,0x5E,0x16,0x81,0x77,
0x04,0xDA,0xF6,0xBE,0xAE,0x80,0x95,0xFE,0xB0,0xCD,0x7F,0xD6,0xA7,0x1A,0x72,0x5C,
0x3C,0xCA,0xBC,0xF0,0x08,0xA3,0x22,0x30,0xB3,0x06,0x85,0xC9,0xB3,0x20,0x77,0x13,
0x85,0xDF,0x02,0x03,0x01,0x00,0x01,0xA3,0x81,0xA8,0x30,0x81,0xA5,0x30,0x81,0xA2,
0x06,0x03,0x55,0x1D,0x01,0x04,0x81,0x9A,0x30,0x81,0x97,0x80,0x10,0x5B,0xD0,0x70,
0xEF,0x69,0x72,0x9E,0x23,0x51,0x7E,0x14,0xB2,0x4D,0x8E,0xFF,0xCB,0xA1,0x72,0x30,
0x70,0x31,0x2B,0x30,0x29,0x06,0x03,0x55,0x04,0x0B,0x13,0x22,0x43,0x6F,0x70,0x79,
0x72,0x69,0x67,0x68,0x74,0x20,0x28,0x63,0x29,0x20,0x31,0x39,0x39,0x37,0x20,0x4D,
0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,0x20,0x43,0x6F,0x72,0x70,0x2E,0x31,0x1E,
0x30,0x1C,0x06,0x03,0x55,0x04,0x0B,0x13,0x15,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,
0x66,0x74,0x20,0x43,0x6F,0x72,0x70,0x6F,0x72,0x61,0x74,0x69,0x6F,0x6E,0x31,0x21,
0x30,0x1F,0x06,0x03,0x55,0x04,0x03,0x13,0x18,0x4D,0x69,0x63,0x72,0x6F,0x73,0x6F,
0x66,0x74,0x20,0x52,0x6F,0x6F,0x74,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,
0x79,0x82,0x0F,0x00,0xC1,0x00,0x8B,0x3C,0x3C,0x88,0x11,0xD1,0x3E,0xF6,0x63,0xEC,
0xDF,0x40,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x04,0x05,
0x00,0x03,0x82,0x01,0x01,0x00,0x95,0xE8,0x0B,0xC0,0x8D,0xF3,0x97,0x18,0x35,0xED,
0xB8,0x01,0x24,0xD8,0x77,0x11,0xF3,0x5C,0x60,0x32,0x9F,0x9E,0x0B,0xCB,0x3E,0x05,
0x91,0x88,0x8F,0xC9,0x3A,0xE6,0x21,0xF2,0xF0,0x57,0x93,0x2C,0xB5,0xA0,0x47,0xC8,
0x62,0xEF,0xFC,0xD7,0xCC,0x3B,0x3B,0x5A,0xA9,0x36,0x54,0x69,0xFE,0x24,0x6D,0x3F,
0xC9,0xCC,0xAA,0xDE,0x05,0x7C,0xDD,0x31,0x8D,0x3D,0x9F,0x10,0x70,0x6A,0xBB,0xFE,
0x12,0x4F,0x18,0x69,0xC0,0xFC,0xD0,0x43,0xE3,0x11,0x5A,0x20,0x4F,0xEA,0x62,0x7B,
0xAF,0xAA,0x19,0xC8,0x2B,0x37,0x25,0x2D,0xBE,0x65,0xA1,0x12,0x8A,0x25,0x0F,0x63,
0xA3,0xF7,0x54,0x1C,0xF9,0x21,0xC9,0xD6,0x15,0xF3,0x52,0xAC,0x6E,0x43,0x32,0x07,
0xFD,0x82,0x17,0xF8,0xE5,0x67,0x6C,0x0D,0x51,0xF6,0xBD,0xF1,0x52,0xC7,0xBD,0xE7,
0xC4,0x30,0xFC,0x20,0x31,0x09,0x88,0x1D,0x95,0x29,0x1A,0x4D,0xD5,0x1D,0x02,0xA5,
0xF1,0x80,0xE0,0x03,0xB4,0x5B,0xF4,0xB1,0xDD,0xC8,0x57,0xEE,0x65,0x49,0xC7,0x52,
0x54,0xB6,0xB4,0x03,0x28,0x12,0xFF,0x90,0xD6,0xF0,0x08,0x8F,0x7E,0xB8,0x97,0xC5,
0xAB,0x37,0x2C,0xE4,0x7A,0xE4,0xA8,0x77,0xE3,0x76,0xA0,0x00,0xD0,0x6A,0x3F,0xC1,
0xD2,0x36,0x8A,0xE0,0x41,0x12,0xA8,0x35,0x6A,0x1B,0x6A,0xDB,0x35,0xE1,0xD4,0x1C,
0x04,0xE4,0xA8,0x45,0x04,0xC8,0x5A,0x33,0x38,0x6E,0x4D,0x1C,0x0D,0x62,0xB7,0x0A,
0xA2,0x8C,0xD3,0xD5,0x54,0x3F,0x46,0xCD,0x1C,0x55,0xA6,0x70,0xDB,0x12,0x3A,0x87,
0x93,0x75,0x9F,0xA7,0xD2,0xA0,
};

//extern /*__declspec(selectany)*/ const double const115 = 115.0;
//extern /*__declspec(selectany)*/ const double const2 = 2.0;
//extern /*__declspec(selectany)*/ const wchar_t aWindowsProduct[] = L"Windows Product Activation";
extern const wchar_t aWindowsProduct[];
//extern __declspec(selectany) const wchar_t asc_1014AC0[] = L"-";
extern const wchar_t asc_1014AC0[];

// L"\\licdll.dll"
WCHAR word_10759D8[] = {0x94E4, 0xF776, 0x5141, 0x1602, 0x1348, 0x1FF, 0x4EF2, 0xCAAF, 0x368D, 0x9A70, 0x4358, 0x8AE6, 0x64, 0x818D};
const void* ScpProtectedData_3_1_0_10_00_00[] = {
	&byte_1019960,
	&word_10759D8,
};
// L"\\wpa.dbl"
WCHAR szWPAStoreFileName[] = {0xA64D, 0x1644, 0x477E, 0x3C21, 0x281F, 0x7A31, 0xF2B4, 0x668F, 0x711F, 0xF8D3, 0x8337};

//#include "licmgr_eh.inc"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_2() {
	__asm {
		mov eax, 3
	BEGIN_SCP_SEGMENT_3_2_0_10_00_00:
		mov ebx, 2
		retn
	}
}
#endif
#pragma warning(pop)

#include "licmgr.h"
#include "lmcrypt.h"
#include "../include/trivialencrypt.h"

CWPALicenseManager::CWPALicenseManager() {
	field_220 = 0;
	ZeroMemory(field_118, sizeof(field_118));
#ifdef _X86_
	void Begin_Vspweb_Scp_Segment_3_2();
	void End_Vspweb_Scp_Segment_3_2();
	void Begin_Vspweb_Scp_Segment_3_4();
	void End_Vspweb_Scp_Segment_3_4();
	void Begin_Vspweb_Scp_Segment_3_5();
	void End_Vspweb_Scp_Segment_3_5();
	void Begin_Vspweb_Scp_Segment_3_6();
	void End_Vspweb_Scp_Segment_3_6();
	void Begin_Vspweb_Scp_Segment_3_7();
	void End_Vspweb_Scp_Segment_3_7();
	void Begin_Vspweb_Scp_Segment_3_8();
	void End_Vspweb_Scp_Segment_3_8();
	__asm {
                push    eax
                lea     eax, ScpProtectedData_3_1_0_10_00_00 ; void const * * ScpProtectedData_3_1_0_10_00_00
                pop     eax
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_2 ; Begin_Vspweb_Scp_Segment_3_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_2 ; End_Vspweb_Scp_Segment_3_2(void)
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_4 ; Begin_Vspweb_Scp_Segment_3_4(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_4 ; End_Vspweb_Scp_Segment_3_4(void)
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_5 ; Begin_Vspweb_Scp_Segment_3_5(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_5 ; End_Vspweb_Scp_Segment_3_5(void)
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_6 ; Begin_Vspweb_Scp_Segment_3_6(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_6 ; End_Vspweb_Scp_Segment_3_6(void)
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_7 ; Begin_Vspweb_Scp_Segment_3_7(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_7 ; End_Vspweb_Scp_Segment_3_7(void)
                cmp     eax, offset Begin_Vspweb_Scp_Segment_3_8 ; Begin_Vspweb_Scp_Segment_3_8(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_3_8 ; End_Vspweb_Scp_Segment_3_8(void)
	}
#endif
#ifdef _x64
	extern "C" void Begin_Vspweb_Scp_Segment_3_2();
	extern "C" void End_Vspweb_Scp_Segment_3_2();
	extern "C" void Begin_Vspweb_Scp_Segment_3_4();
	extern "C" void End_Vspweb_Scp_Segment_3_4();
	extern "C" void Begin_Vspweb_Scp_Segment_3_5();
	extern "C" void End_Vspweb_Scp_Segment_3_5();
	extern "C" void Begin_Vspweb_Scp_Segment_3_6();
	extern "C" void End_Vspweb_Scp_Segment_3_6();
	extern "C" void Begin_Vspweb_Scp_Segment_3_7();
	extern "C" void End_Vspweb_Scp_Segment_3_7();
	extern "C" void Begin_Vspweb_Scp_Segment_3_8();
	extern "C" void End_Vspweb_Scp_Segment_3_8();
#endif
}

CWPALicenseManager::~CWPALicenseManager() {
}

DWORD FormatDefaultLSFileName(char* lpName, DWORD cbName) {
	DWORD err = ERROR_SUCCESS;
	char szSysDir[MAX_PATH] = {0};
	WCHAR szRelativeName[MAX_PATH] = {0};
	if (lpName == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	if (!GetSystemDirectoryA(szSysDir, MAX_PATH)) {
		err = GetLastError();
		goto Done;
	}
	lstrcat(szRelativeName, CWPAStringsDecryptor(szWPAStoreFileName, sizeof(szWPAStoreFileName) / sizeof(szWPAStoreFileName[0]), unk_1019768));
	lpName[cbName - 1] = 0;
	if (_snprintf(lpName, cbName - 1, "%s%ls", szSysDir, szRelativeName) < 0) {
		err = 0x502 /*ERROR_STACK_BUFFER_OVERRUN*/;
		goto Done;
	}
Done:
	return err;
}

DWORD SetLSFileAcl(LPCSTR lpFileName) {
	PSECURITY_DESCRIPTOR SecurityDescriptor = NULL;
	DWORD err;
	char szDefaultFileName[MAX_PATH];
	LPCSTR lpUsedFileName = lpFileName;
	BOOL fUseDefaultFileName = FALSE;
	if (lpUsedFileName == NULL) {
		err = FormatDefaultLSFileName(szDefaultFileName, MAX_PATH);
		if (err != ERROR_SUCCESS) {
			goto Done;
		}
		lpUsedFileName = szDefaultFileName;
		fUseDefaultFileName = TRUE;
	}
	if (!ConvertStringSecurityDescriptorToSecurityDescriptorA(
		"D:PAR(A;OICI;FA;;;BA)(A;OICI;FA;;;SY)",
		SDDL_REVISION_1,
		&SecurityDescriptor,
		NULL))
	{
		err = GetLastError();
		goto Done;
	}
	if (SecurityDescriptor != NULL) {
		if (!SetFileSecurityA(lpUsedFileName, DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, SecurityDescriptor)) {
			err = GetLastError();
			goto Done;
		}
		if (fUseDefaultFileName) {
			DWORD len = strlen(szDefaultFileName);
			strcpy(szDefaultFileName + len - 3, "bak");
			SetFileSecurityA(lpUsedFileName, DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, SecurityDescriptor);
		}
	}
	err = ERROR_SUCCESS;
Done:
	if (SecurityDescriptor != NULL) {
		LocalFree(SecurityDescriptor);
	}
	return err;
}

DWORD sub_1053434(LPCSTR lpFileName) {
	WCHAR Buffer[MAX_PATH];
	HMODULE hLicDll = NULL;

	DWORD dwSysDirLen = GetSystemDirectory(Buffer, MAX_PATH);
	if (dwSysDirLen == 0 || dwSysDirLen + 15 >= MAX_PATH) {
		return GetLastError();
	}
	DWORD err = 0;
	lstrcat(Buffer, CWPAStringsDecryptor(word_10759D8, sizeof(word_10759D8) / sizeof(word_10759D8[0]), unk_1019768));
	hLicDll = LoadLibraryEx(Buffer, NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (hLicDll != NULL) {
		HRSRC hCanonicalLicStoreRsrc = FindResourceEx(hLicDll, RT_RCDATA, L"IDR_WPA_LICSTORE", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
		if (hCanonicalLicStoreRsrc != NULL) {
			HGLOBAL hCanonicalLicStoreGlobal = LoadResource(hLicDll, hCanonicalLicStoreRsrc);
			if (hCanonicalLicStoreGlobal != NULL) {
				LPVOID lpCanonicalLicStore = LockResource(hCanonicalLicStoreGlobal);
				DWORD szCanonicalLicStore = SizeofResource(hLicDll, hCanonicalLicStoreRsrc);
				if (lpCanonicalLicStore != NULL && szCanonicalLicStore != 0) {
					HANDLE hFile = CreateFileA(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
					if (hFile != INVALID_HANDLE_VALUE) {
						DWORD nWritten = 0;
						if (!WriteFile(hFile, lpCanonicalLicStore, szCanonicalLicStore, &nWritten, NULL)) {
							err = GetLastError();
						}
						CloseHandle(hFile);
					} else {
						err = GetLastError();
					}
				} else {
					err = GetLastError();
				}
			} else {
				err = GetLastError();
			}
		} else {
			err = GetLastError();
		}
		FreeLibrary(hLicDll);
	} else {
		err = GetLastError();
	}
	return err;
}

DWORD CWPALicenseManager::sub_1053728(LPCVOID lpStoreKeyPart1, DWORD cbStoreKeyPart1) {
	CHAR var_118[MAX_PATH + 1] = {0};
	LPVOID lpStoreKeyPart2 = NULL;
	DWORD cbStoreKeyPart2 = 0;
	DWORD var_10 = strlen(field_118);
	DWORD err;
	if (var_10 == 0) {
		err = FormatDefaultLSFileName(var_118, MAX_PATH + 1);
		if (err != ERROR_SUCCESS) {
			goto Cleanup;
		}
	} else {
		strcpy(var_118, field_118);
	}
	if (lpStoreKeyPart1 != NULL && cbStoreKeyPart1 != 0) {
		cbStoreKeyPart2 = cbStoreKeyPart1 + 4;
		lpStoreKeyPart2 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbStoreKeyPart2);
		if (lpStoreKeyPart2 == NULL) {
			err = ERROR_OUTOFMEMORY;
			goto Cleanup;
		}
		memcpy(lpStoreKeyPart2, lpStoreKeyPart1, cbStoreKeyPart1);
		*(DWORD*)((BYTE*)lpStoreKeyPart2 + cbStoreKeyPart1) = 0x787E43B5;
	}
	err = m_Store.Init(var_118, lpStoreKeyPart2, cbStoreKeyPart2, FALSE);
	if (err != ERROR_SUCCESS) {
		m_Store.Clear();
		if (err == ERROR_BAD_RECORD || err == ERROR_FILE_NOT_FOUND || err == ERROR_BAD_DECRYPT) {
			err = sub_1053434(var_118);
			if (err != ERROR_SUCCESS) {
				goto Cleanup;
			}
			err = SetLSFileAcl(var_118);
		}
		if (err != ERROR_SUCCESS) {
			goto Cleanup;
		}
		HANDLE hEventLog = RegisterEventSource(NULL, L"Windows Product Activation");
		if (hEventLog != NULL) {
			ReportEvent(hEventLog, EVENTLOG_ERROR_TYPE, 0, 0xC0000000 | 1010, NULL, 0, 0, NULL, NULL);
			DeregisterEventSource(hEventLog);
		}
		err = m_Store.Init(var_118, lpStoreKeyPart2, cbStoreKeyPart2, FALSE);
	}
Cleanup:
	if (lpStoreKeyPart2 != NULL) {
		HeapFree(GetProcessHeap(), 0, lpStoreKeyPart2);
	}
	if (err != ERROR_SUCCESS) {
		m_Store.Clear();
	}
	return err;
}

DWORD CWPALicenseManager::sub_1053A3C(LPVOID arg_0, DWORD arg_4) {
	LPVOID var_8 = NULL;
	DWORD var_C = 0;
	DWORD var_4 = 1;
	DWORD err;
	if (arg_4 != 8) {
		err = ERROR_340;
		goto Cleanup;
	}
	err = m_Store.AddRecord(2, arg_0, arg_4, TRUE);
	if (err == ERROR_SUCCESS) {
		var_4 = 1;
		err = m_Store.AddRecord(0x10, &var_4, sizeof(var_4), TRUE);
		if (err == ERROR_DUPLICATE_RECORD) {
			err = m_Store.ReplaceRecord(0x10, &var_4, sizeof(var_4));
		}
		if (err != ERROR_SUCCESS) {
			m_Store.DeleteRecord(2);
			goto Cleanup;
		}
	} else if (err == ERROR_DUPLICATE_RECORD) {
		err = m_Store.GetRecord(2, &var_8, &var_C);
		if (err != ERROR_SUCCESS) {
			goto Cleanup;
		}
		if (var_C == 8 && !memcmp(arg_0, var_8, 8)) {
			var_4 = 0;
			goto Cleanup;
		}
		var_4 = 1;
		err = m_Store.ReplaceRecord(2, arg_0, 8);
		if (err != ERROR_SUCCESS) {
			goto Cleanup;
		}
		err = m_Store.ReplaceRecord(0x10, &var_4, sizeof(var_4));
		if (err != ERROR_SUCCESS) {
			m_Store.ReplaceRecord(2, var_8, var_C);
		}
	}
Cleanup:
	if (var_8 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_8);
	}
	return err;
}

int sub_1053C0F();
DWORD CWPALicenseManager::sub_1053C0F(DWORD arg_0, DWORD arg_4) {
	int result = 0;
	if (arg_0 < 10) {
		result = arg_0 + arg_4 * 10;
	} else if (arg_0 > 9 && arg_0 < 100) {
		result = arg_0 + arg_4 * 100;
	} else if (arg_0 > 99 && arg_0 < 1000) {
		result = arg_0 + arg_4 * 1000;
	}
	return result;
}

DWORD CWPALicenseManager::sub_1053D0D(DWORD dwRecordId) {
	DWORD err = m_Store.DeleteRecord(dwRecordId);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1053DB7(DWORD arg_0) {
	DWORD err = m_Store.DeleteRecord(sub_1053C0F(1, arg_0));
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1053E99() {
	DWORD err = m_Store.DeleteRecord(2);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1053F48() {
	DWORD err = m_Store.DeleteRecord(4);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1053FF3() {
	DWORD err = m_Store.DeleteRecord(0x11);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1054098() {
	DWORD err = m_Store.DeleteRecord(9);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_105413C() {
	DWORD err = m_Store.DeleteRecord(7);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_10541E2() {
	DWORD err = m_Store.DeleteRecord(8);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1054285(DWORD dwRecordId, LPCVOID lpData, DWORD cbData, BOOL fEncrypt) {
	DWORD err = m_Store.AddRecord(dwRecordId, lpData, cbData, fEncrypt);
	if (err == ERROR_DUPLICATE_RECORD) {
		err = m_Store.ReplaceRecord(dwRecordId, lpData, cbData);
	}
	return err;
}

DWORD CWPALicenseManager::sub_1054386(DWORD dwRecordId, LPVOID* ppData, DWORD* pcbData) {
	DWORD err = m_Store.GetRecord(dwRecordId, ppData, pcbData);
#ifdef _X86_
	__asm nop
#endif
	return err;
}

DWORD CWPALicenseManager::sub_1054438(LPCWSTR arg_0, DWORD arg_4[4]) {
	DWORD err = ERROR_SUCCESS;
	WCHAR Dest[0x21] = {0};
	wcsncpy(Dest, arg_0, 0x20);
	WCHAR* p = wcstok(Dest, L"-");
	if (!p) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	arg_4[0] = _wtol(p);
	p = wcstok(NULL, L"-");
	if (!p) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	arg_4[1] = _wtol(p);
	p = wcstok(NULL, L"-");
	if (!p) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	arg_4[2] = _wtol(p);
	p = wcstok(NULL, L"-");
	if (!p) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	arg_4[3] = _wtol(p);
Done:
	return err;
}

int sub_1054612();
BOOL CWPALicenseManager::sub_1054612(LPCWSTR lpString, DWORD nStartPos, DWORD nEndPos) {
	for (DWORD i = nStartPos; i < nEndPos + 1; i++) {
		if (lpString[i] < L'0' || lpString[i] > L'9') {
			return FALSE;
		}
	}
	return TRUE;
}

DWORD CWPALicenseManager::sub_10546A9(DWORD arg_0) {
	DWORD err = m_Store.DeleteRecord(sub_1053C0F(20, arg_0));
	return err;
}

DWORD CWPALicenseManager::sub_1054789(DWORD arg_0) {
	DWORD err = m_Store.DeleteRecord(sub_1053C0F(21, arg_0));
#ifdef _X86_
	__asm nop
#endif
	return err;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_2() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_2:
                mov     edx, 2
                retn
}
}
#endif
#pragma warning(pop)

#include "license.h"

struct CWPAPhoneActivated {
    WORD field_0[0x20];
    HWID field_40;
    WCHAR field_48[1];
};

bool __forceinline WPADecryptWithMachineSeed(LPBYTE lpData, DWORD cbData) {
    BYTE key[16];
    if (FAILED(GetPerMachine128BitSeed(key))) {
        return false;
    }
    WPADecrypt(lpData, cbData, key);
    return true;
}

DWORD CWPALicenseManager::ValidateActivation(DWORD dwRecordId, CWPAClass4* arg_4) {
    WCHAR var_EC[0x21] = {0};
    LPVOID lpMem = NULL;
    DWORD var_30 = 0;
    LPWSTR var_20 = NULL;
    double var_70 = 115 * log10(2);
    DWORD var_5C = 2 * (int)ceil(var_70); // edi
    DWORD var_80[4] = {0, 0, 0, 0};
    DWORD var_2C = 0;
    DWORD var_50 = 0;
    DWORD var_54 = 0;
    DWORD var_48 = 0;
    DWORD var_3C = 0;
    DWORD var_64 = 0;
    DWORD var_60 = 0;
    DWORD var_58 = 0;
    LPVOID var_18 = NULL;
    DWORD var_40 = 0;
    LPVOID var_1C = NULL;
    DWORD var_4C = 0;
    CWPAClass4* var_24 = NULL;
    DWORD var_44 = 0;
    CWPACertificateManager var_A8;
    DWORD err;
    if (!arg_4) {
        err = ERROR_INVALID_PARAMETER;
        goto Cleanup;
    }
    err = m_Store.GetRecord(dwRecordId, &lpMem, &var_30);
    if (err) {
        goto Cleanup;
    }
    if (!WPADecryptWithMachineSeed((LPBYTE)lpMem, var_30)) {
        err = ERROR_MACHINE_SEED_FAIL;
        goto Cleanup;
    }
    DWORD tmp = var_5C + offsetof(CWPAPhoneActivated, field_48);
    if (var_30 == tmp) {
        BYTE var_94[0x14];
        DWORD var_10 = sizeof(var_94);
        var_20 = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 2 * ((int)ceil(var_70) + 1));
        if (!var_20) {
            err = ERROR_OUTOFMEMORY;
            goto Cleanup;
        }
        HWID var_38;
        CWPAPhoneActivated* pActivated = (CWPAPhoneActivated*)lpMem;
        memcpy(var_EC, pActivated->field_0, sizeof(pActivated->field_0));
        DWORD sz = sizeof(HWID);
        memcpy(&var_38, &pActivated->field_40, sz);
        memcpy(var_20, pActivated->field_48, var_5C);
        if (sub_1054438(var_EC, var_80)) {
            err = ERROR_339;
            goto Cleanup;
        }
        err = WPAValidatePhoneActivation(var_20, var_80, var_38, &var_50, &var_54, &var_48, &var_3C, &var_64, &var_60, &var_58, &var_2C, var_94, &var_10);
        if (err) {
            goto Cleanup;
        }
        arg_4->field_6C = var_2C;
        arg_4->field_0 = var_50;
        arg_4->field_4 = var_54;
        arg_4->field_8 = var_48;
        arg_4->field_C = var_3C;
        arg_4->sub_105487E(var_EC);
        ZeroMemory(&arg_4->field_56, sizeof(arg_4->field_56));
        memcpy(&arg_4->field_56, &var_38, sizeof(var_38));
        arg_4->field_60 = var_64;
        arg_4->field_68 = var_60;
        arg_4->field_64 = var_58;
        if (var_2C) {
            arg_4->sub_105492E(var_94, var_10);
        }
    } else {
        DWORD var_30_copy = var_30;
        LPVOID lpMem_copy = lpMem;
        err = m_Store.GetRecord(7, &var_18, &var_40);
        if (err) {
            goto Cleanup;
        }
        err = m_Store.GetRecord(8, &var_1C, &var_4C);
        if (err) {
            goto Cleanup;
        }
        err = var_A8.Init((const BYTE*)var_18, var_40, (const BYTE*)var_1C, var_4C);
        if (err) {
            goto Cleanup;
        }
        err = var_A8.ValidateInternetActivation(byte_1019960, sizeof(byte_1019960), (const BYTE*)lpMem_copy, var_30_copy, (LPVOID*)&var_24, &var_44);
        if (!err) {
            memcpy(arg_4, var_24, var_44);
        }
    }
Cleanup:
    if (lpMem) {
        HeapFree(GetProcessHeap(), 0, lpMem);
        lpMem = NULL;
    }
    if (var_20) {
        HeapFree(GetProcessHeap(), 0, var_20);
    }
    if (var_24) {
        HeapFree(GetProcessHeap(), 0, var_24);
        var_24 = NULL;
    }
    if (var_18) {
        HeapFree(GetProcessHeap(), 0, var_18);
        var_18 = NULL;
    }
    if (var_1C) {
        HeapFree(GetProcessHeap(), 0, var_1C);
        var_1C = NULL;
    }
    var_A8.Clear();
    return err;
}

BOOL CWPALicenseManager::sub_1055169(LPCWSTR lpString) {
	return wcslen(lpString) == 23
		&& lpString[5] == L'-'
		&& lpString[9] == L'-'
		&& lpString[17] == L'-'
		&& sub_1054612(lpString, 0, 4)
		&& sub_1054612(lpString, 6, 8)
		&& sub_1054612(lpString, 10, 16)
		&& sub_1054612(lpString, 18, 22);
}

DWORD CWPALicenseManager::sub_10552D8(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8) {
	DWORD err;
	DWORD var_4 = 1;
	LPVOID var_8 = 0;
	DWORD var_14 = 0;
	WCHAR var_5C[0x21] = {0};
	if (arg_8 > 0x40) {
		err = ERROR_339;
		goto Cleanup;
	}
	if (arg_8 > sizeof(var_5C)) {
		err = ERROR_x502;
		goto Cleanup;
	}
	memcpy(var_5C, arg_4, arg_8);
	if (!sub_1055169(var_5C)) {
		err = ERROR_339;
		goto Cleanup;
	}
	DWORD var_18 = sub_1053C0F(1, arg_0);
	DWORD var_10 = sub_1053C0F(15, arg_0);
	err = m_Store.AddRecord(var_18, arg_4, arg_8, TRUE);
	if (err == ERROR_SUCCESS) {
		var_4 = 1;
		err = m_Store.AddRecord(var_10, &var_4, sizeof(var_4), TRUE);
		if (err == ERROR_DUPLICATE_RECORD) {
			err = m_Store.ReplaceRecord(var_10, &var_4, sizeof(var_4));
		}
		if (err != ERROR_SUCCESS) {
			m_Store.DeleteRecord(var_18);
		}
	} else if (err == ERROR_DUPLICATE_RECORD) {
		err = m_Store.GetRecord(var_18, &var_8, &var_14);
		if (err != ERROR_SUCCESS) {
			goto Cleanup;
		}
		if (arg_8 == var_14 && !memcmp(arg_4, var_8, arg_8)) {
			var_4 = FALSE;
		} else {
			var_4 = TRUE;
			err = m_Store.ReplaceRecord(var_18, arg_4, arg_8);
			if (err != ERROR_SUCCESS) {
				goto Cleanup;
			}
			err = m_Store.ReplaceRecord(var_10, &var_4, sizeof(var_4));
			if (err != ERROR_SUCCESS) {
				m_Store.ReplaceRecord(var_18, var_8, var_14);
			}
		}
	}
Cleanup:
	if (var_8 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_8);
	}
	return err;
}
