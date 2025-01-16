#include "precomp.h"
#pragma hdrstop
#include <ntregapi.h>
#include <wincrypt.h>
#include "../include/trivialencrypt.h"
//#include "../include/autoptr.h"
#include "../include/errors.h"
#include "../include/keyexists.h"
#include "../lib/basex.h"
#include "../liclib/crypthelper.h"
#include "times.h"
#include "regtime.h"

void regtime_do_nothing();

extern __declspec(selectany) const BYTE dword_10192F8[9] = {0xC7, 0xB9, 0xF4, 0x43, 0x01, 0x86, 0xB7, 0x12, 0x4F};

// L"SigningHashData"
WCHAR VALUENAME_ENC[] = {0xB441, 0xE41C, 0x2F7E, 0x549C, 0x2867, 0x7EF3, 0xD5FB, 0x2C7D,
                0xF072, 0xEA0C, 0x800E, 0xB4AD, 0x9217, 0xF6D1, 0x8E51, 0x72F0,
                0x15E7, 0xE5B5};
// L"System\\WPA\\"
WCHAR word_1075444[] = {0x56C1, 0x1C5C, 0xF752, 0x18F4, 0x5969, 0xB4E0, 0x4E96, 0x9168,
                0x898C, 0xA573, 0x1466, 0x3C55, 0xFFD, 0x9680};
// L"System\\CurrentControlSet\\Control\\Session Manager\\WPA\\"
WCHAR szWPAOldBaseKeyName_ENC[] = {0x56C1,0x1C5C,0xF752,0x34F4,0x646E,0x1FC6,0xBFE4,0x14D5,0x7697,0xBD34,0x045E,0xA5FB,0xF1F1,0x635C,0x3257,0xCECA,0x535A,0x8850,0xC18D,0x7F28,0x952B,0xCC19,0x8CD4,0x8BFF,0xE7CF,0xAADF,0x9642,0xFD7E,0x4FAD,0xEF2D,0x7AFE,0x99A1,0x10E5,0xC268,0xEEA9,0xBB9C,0xCE62,0x7FFE,0xFE96,0x2BE9,0xBBF3,0x53B6,0x6AF3,0x25D3,0x84B0,0x6E5A,0xB417,0x8854,0x993C,0x5737,0xD9D3,0xC031,0xB462,0x3B33,0xD70D,0x856D};
// L"SigningHash"
WCHAR word_10754D0[] = {0xB441,0xE41C,0x2F7E,0x549C,0x2867,0x7EF3,0xD5FB,0xC57D,0x0F7A,0xC280,0xDB4E,0x9D9C,0xC3C8,0x783E};
// L"ReSigningHash"
WCHAR word_10754EC[] = {0x534D,0x7A57,0x8CD0,0x4F7A,0xEAA3,0x83DA,0x3FDC,0x297F,0xF32A,0x498C,0x1681,0x0ED9,0xFC59,0xB18B,0x6FE6,0x6978};
// L"EntryHash"
WCHAR word_107550C[] = {0x9D19,0x0487,0xAC35,0x769C,0x9EFA,0x81D1,0xBA22,0x699C,0x6193,0xFE0A,0x1F05,0xB6D2};
// L"ExitHash"
WCHAR word_1075524[] = {0x4572,0x5C74,0x70D4,0x6AF2,0x7CD5,0x1E06,0x1B1D,0x5D6A,0x0841,0xB6EE,0xE0AA};
// L"ImportHash"
WCHAR word_107553C[] = {0x2836,0xB320,0xAF09,0x5FBC,0x23A0,0x1AE0,0xE7EA,0x11FC,0xF6EE,0x9289,0xCE10,0x2D7F,0xC19A};
// L"ExportHash"
WCHAR word_1075558[] = {0x1755,0x9DA7,0xC220,0x9F77,0x5C54,0x956F,0xC406,0x5C54,0x74F6,0x1585,0xF5A5,0xA88B,0xD9D4};
// L"StartHash"
WCHAR word_1075574[] = {0x9636,0xC0D5,0x0054,0x2997,0x7765,0x66DD,0x7273,0x0C4A,0x5F98,0xF006,0x0EB3,0xE1CA};
// L"EndHash"
WCHAR word_107558C[] = {0xC468,0x1951,0x0AC2,0x3B7D,0xA045,0x6973,0x9315,0x450A,0x679B,0xA0BF};
// L"HashID"
WCHAR szGP1[] = {0x5E48,0x73C0,0x1C8A,0x25A3,0x2D13,0x56AE,0xD7FC,0xD27E,0x9442};
// L"ReHashID"
WCHAR szGP2[] = {0x9314,0x14F8,0xC950,0xAF93,0x8AC7,0xDD8F,0x1FB7,0x5735,0x648F,0xD233,0x9FB8};
// L"HashAlgID"
WCHAR szGP3[] = {0x0E48,0x33EB,0xA591,0xBFB8,0xE2F4,0x616A,0x5269,0xAACF,0xB1E0,0x4B46,0xB398,0x926E};
// L"ExHashAlgID"
WCHAR szGP4[] = {0xA82F,0x931B,0x85E0,0x3C6C,0xDE20,0x1AAC,0xBCD3,0x8B03,0x6AED,0x2F52,0x9C40,0x3157,0x36F1,0x1E89};
// L"KeyHashMatrix"
WCHAR szGP5[] = {0xFE6D,0x5A9F,0x2206,0x7F77,0xCB66,0xE1B5,0xAD87,0xB48A,0x8D87,0xF863,0xDB34,0x0625,0x0EBD,0x98F8,0xC791,0x5543};
// L"KeyHashCol"
WCHAR szGP6[] = {0xFE6D,0x5A9F,0x2206,0x3C77,0xD272,0xBB4E,0x8E05,0xF2E4,0x05EA,0x8481,0xD87B,0x1087,0xB7EA};
// L"RowMatrix"
WCHAR szGP7[] = {0x6016,0x160B,0x2EEB,0x746A,0x6EC9,0x3716,0xFE3A,0x11D9,0x785E,0x0E05,0x10B7,0x2FE6};
// L"DiagMatrix"
WCHAR szGP8[] = {0xF312,0x72E3,0x0330,0xDF7B,0xFF99,0x3F20,0x01ED,0xB11C,0xF17D,0x5C2D,0x43C7,0x4FA0,0xFDB0};
// L"EnableHash"
WCHAR szGP9[] = {0x9646,0x9F32,0xBEB3,0xDE83,0x29A8,0xEFC7,0xDE20,0x99EB,0xE483,0x1CF0,0x4AAD,0xA38C,0x7493};
// L"DisableHash"
WCHAR szGP10[] = {0x427F,0x5093,0x96BA,0x6D4C,0x3C95,0x8E17,0x86B6,0xB16C,0x3814,0x2E5D,0x28CE,0xFC1D,0xF29F,0x7028};
// L"ValidateCrc"
WCHAR szGP11[] = {0xB241,0x70D5,0x831A,0x36D3,0xFC1A,0xE586,0xF9DC,0xE946,0x223D,0x6C2D,0x6C5F,0x2A79,0xEF65,0x6691};
// L"CancelCrc"
WCHAR szGP12[] = {0x9C24,0xE839,0x17C4,0xAC78,0xA854,0x24CD,0x171C,0x7520,0xC030,0x07E2,0xCCC5,0x7D68};
// L"CipherHash"
WCHAR szGP13[] = {0x6E76,0x85C9,0x7305,0x8191,0xFD6B,0xFF08,0xAE1A,0xA77B,0x5513,0xA75D,0x34C5,0x0A65,0x4273};
// L"DecipherHash"
WCHAR szGP14[] = {0xA548,0x97A3,0x827D,0xEAC5,0x9E7E,0x9588,0x6692,0xC3B2,0x11D0,0xEBAC,0x7E24,0xB21B,0x75BD,0xEC78,0x0E87};
// L"CryptAlg"
WCHAR szGP15[] = {0x0E48,0x3F53,0x454B,0x89E3,0x44AF,0xAD02,0x6606,0x9FAB,0x6B0D,0xC769,0x3054};
// L"DecryptAlg"
WCHAR szGP16[] = {0xB70C,0xF489,0xB5FF,0x74D7,0x655F,0x3DAD,0xF88F,0x69ED,0x2E8C,0xF704,0x5788,0x9A90,0x2E42};
// L"RenewCrc"
WCHAR szGP17[] = {0x49F7,0x7346,0x26CF,0xED92,0x8753,0xE9B0,0x0E46,0x5B80,0x9569,0x8691,0x5256};
// L"ExpireCrc"
WCHAR szGP18[] = {0xA459,0xEA8B,0x6CE3,0x4106,0x10E5,0x8664,0x5852,0xCB00,0xDBD2,0x9F67,0xDE4A,0x4AE0};
// L"AllocBuf"
WCHAR szGP19[] = {0x0B7F,0x5BBC,0xE41F,0xC081,0xB7F4,0xADEC,0x9152,0xCB39,0x775C,0x1C03,0xC7E1};
// L"FreeBuf"
WCHAR szGP20[] = {0x84D5,0x7CDC,0xF496,0x2751,0x05EF,0x2764,0x08DB,0xFA20,0x07F4,0x6F2D};
// L"CipherMatrix"
WCHAR szGP21[] = {0x6E76,0x85C9,0xF305,0x2A9C,0x83AE,0x813A,0x6039,0xE257,0x2971,0x9FA6,0x4226,0x5798,0xBE74,0x2552,0xC879};
// L"CipherCol"
WCHAR szGP22[] = {0x6E76,0x85C9,0xD205,0xB407,0x82AF,0x9902,0x3EE1,0xEF9F,0x77C8,0x3E2F,0xA502,0x95B9};
// L"SignMatrix"
WCHAR szGP23[] = {0xC141,0x2970,0x1AF4,0x0B3E,0x0669,0x7409,0xBEF0,0xB964,0x9749,0xE7CF,0x570F,0xB3AD,0xFF1D};
// L"ResignMatrix"
WCHAR szGP24[] = {0xCDC0,0xA4B7,0x9D08,0xBC52,0x0033,0xBAEF,0x6628,0xF0BB,0xF9AD,0xCDF1,0x31A0,0xD53C,0x62D6,0xC96D,0x634D};
struct sWPAKEKeys {
	CONST WCHAR* Data1;
	DWORD Size1;
	CONST WCHAR* Data2;
	DWORD Size2;
};
sWPAKEKeys off_1075820[] = {
	{word_10754D0, sizeof(word_10754D0) / sizeof(word_10754D0[0]), word_10754EC, sizeof(word_10754EC) / sizeof(word_10754EC[0])},
	{word_107550C, sizeof(word_107550C) / sizeof(word_107550C[0]), word_1075524, sizeof(word_1075524) / sizeof(word_1075524[0])},
	{word_107553C, sizeof(word_107553C) / sizeof(word_107553C[0]), word_1075558, sizeof(word_1075558) / sizeof(word_1075558[0])},
	{word_1075574, sizeof(word_1075574) / sizeof(word_1075574[0]), word_107558C, sizeof(word_107558C) / sizeof(word_107558C[0])},
};
sWPAKEKeys aszAdditionalGracePeriodTags[] = {
	{szGP1, sizeof(szGP1) / sizeof(szGP1[0]), szGP2, sizeof(szGP2) / sizeof(szGP2[0])},
	{szGP3, sizeof(szGP3) / sizeof(szGP3[0]), szGP4, sizeof(szGP4) / sizeof(szGP4[0])},
	{szGP5, sizeof(szGP5) / sizeof(szGP5[0]), szGP6, sizeof(szGP6) / sizeof(szGP6[0])},
	{szGP7, sizeof(szGP7) / sizeof(szGP7[0]), szGP8, sizeof(szGP8) / sizeof(szGP8[0])},
	{szGP9, sizeof(szGP9) / sizeof(szGP9[0]), szGP10, sizeof(szGP10) / sizeof(szGP10[0])},
	{szGP11, sizeof(szGP11) / sizeof(szGP11[0]), szGP12, sizeof(szGP12) / sizeof(szGP12[0])},
	{szGP13, sizeof(szGP13) / sizeof(szGP13[0]), szGP14, sizeof(szGP14) / sizeof(szGP14[0])},
	{szGP15, sizeof(szGP15) / sizeof(szGP15[0]), szGP16, sizeof(szGP16) / sizeof(szGP16[0])},
	{szGP17, sizeof(szGP17) / sizeof(szGP17[0]), szGP18, sizeof(szGP18) / sizeof(szGP18[0])},
	{szGP19, sizeof(szGP19) / sizeof(szGP19[0]), szGP20, sizeof(szGP20) / sizeof(szGP20[0])},
	{szGP21, sizeof(szGP21) / sizeof(szGP21[0]), szGP22, sizeof(szGP22) / sizeof(szGP22[0])},
	{szGP23, sizeof(szGP23) / sizeof(szGP23[0]), szGP24, sizeof(szGP24) / sizeof(szGP24[0])},
};
const void* ScpProtectedData_8_1_0_10_00_00[] = {
	word_1075444,
	szWPAOldBaseKeyName_ENC,
	word_10754D0,
	word_10754EC,
	word_107550C,
	word_1075524,
	word_107553C,
	word_1075558,
	word_1075574,
	word_107558C,
	off_1075820,
	szGP1,
	szGP2,
	szGP3,
	szGP4,
	szGP5,
	szGP6,
	szGP7,
	szGP8,
	szGP9,
	szGP10,
	szGP11,
	szGP12,
	szGP13,
	szGP14,
	szGP15,
	szGP16,
	szGP17,
	szGP18,
	szGP19,
	szGP20,
	szGP21,
	szGP22,
	szGP23,
	szGP24,
	aszAdditionalGracePeriodTags,
        dword_10192F8,
};

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
extern "C" void __declspec() Begin_Vspweb_Scp_Segment_8_2();
/*
void __declspec(naked) Begin_Vspweb_Scp_Segment_8_2() {
__asm {
                mov     eax, 8
BEGIN_SCP_SEGMENT_8_2_0_10_00_00:
                mov     ebx, 2
                retn
}
}
*/
#pragma warning(pop)

BOOL WPAKeyExists(HKEY hKey, LPCWSTR lpSubKey) {
	HKEY hSubKey;
	if (RegOpenKeyEx(hKey, lpSubKey, 0, KEY_QUERY_VALUE, &hSubKey) != ERROR_SUCCESS) {
		return FALSE;
	}
	RegCloseKey(hSubKey);
	return TRUE;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
extern "C" void __declspec() End_Vspweb_Scp_Segment_8_2();
/*
void __declspec(naked) End_Vspweb_Scp_Segment_8_2() {
__asm {
                mov     ecx, 8
END_SCP_SEGMENT_8_2:
                mov     edx, 2
                retn
}
}
*/
#pragma warning(pop)

//#include "regtime1.inl"
//instantiate ??_E?$AutoPtrBase@G@@UAEPAXI@Z
//aka public: virtual void * __thiscall AutoPtrBase<unsigned short>::`scalar deleting destructor'

HRESULT sub_104A757(HKEY* phKey) {
	regtime_do_nothing();
#ifdef _X86_
	__asm {
                push    eax
                lea     eax, ScpProtectedData_8_1_0_10_00_00 ; void const * * ScpProtectedData_8_1_0_10_00_00
                pop     eax
                cmp     eax, offset Begin_Vspweb_Scp_Segment_8_2 ; Begin_Vspweb_Scp_Segment_8_2(void)
                cmp     eax, offset End_Vspweb_Scp_Segment_8_2 ; End_Vspweb_Scp_Segment_8_2(void)
	}
#endif
	DWORD dwDisposition;
	DWORD err = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		CWPAStringsDecryptor(word_1075444, sizeof(word_1075444)/sizeof(word_1075444[0]), unk_1019768),
		0,
		NULL,
		0,
		WPAKeyExists(HKEY_LOCAL_MACHINE, CWPAStringsDecryptor(word_1075444, sizeof(word_1075444)/sizeof(word_1075444[0]), unk_1019768))
			? KEY_READ : KEY_ALL_ACCESS,
		NULL,
		phKey,
		&dwDisposition);
	return HRESULT_FROM_WIN32(err);
}

//#include "regtime2.inl"
//instantiate ??1?$AutoHeapPtr@G@@UAE@XZ aka public: virtual __thiscall AutoHeapPtr<unsigned short>::~AutoHeapPtr<unsigned short>(void)
//instantiate ??0?$AutoHeapPtr@G@@QAE@PAG@Z aka public: __thiscall AutoHeapPtr<unsigned short>::AutoHeapPtr<unsigned short>(unsigned short *)
//instantiate ??_E?$AutoHeapPtr@G@@UAEPAXI@Z aka public: virtual void * __thiscall AutoHeapPtr<unsigned short>::`scalar deleting destructor'(unsigned int)

extern "C" BOOL CheckNewSKUVLHack(PCWSTR lpSubKey, PCWSTR lpValueName, DWORD dwExpectedValue) {
	AutoHKEY var_24;
	HRESULT hr = sub_104A757(&var_24);
	if (FAILED(hr)) {
		return FALSE;
	}
	AutoHKEY var_18;
	if (RegOpenKeyEx(var_24, lpSubKey, 0, KEY_QUERY_VALUE, &var_18) != ERROR_SUCCESS) {
		return FALSE;
	}
	DWORD Type = 0;
	DWORD Data = 0;
	DWORD cbData = sizeof(Data);
	RegQueryValueEx(var_18, lpValueName, NULL, &Type, (LPBYTE)&Data, &cbData);
	if (Data == dwExpectedValue) {
		return TRUE;
	}
	return FALSE;
}

struct CWPAKeyNameGeneratorInput {
	WORD field_0;
	WORD field_2;
	DWORD field_4;
};

BOOL sub_104AC41(LPWSTR lpszResult, DWORD dwResultSize, LPCWSTR lpszPrefix) {
	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*)&VersionInfo);
	CWPAKeyNameGeneratorInput BinarySuffix;
	ZeroMemory(&BinarySuffix, sizeof(BinarySuffix));
	BinarySuffix.field_2 = 0xE7A;
	BinarySuffix.field_4 = 7;
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
	BOOL Result = FALSE;
	lpszResult[dwResultSize - 1] = 0;
	if (_snwprintf(lpszResult, dwResultSize - 1, L"%s-%s", lpszPrefix, (WCHAR*)lpszSuffix) >= 0) {
		Result = TRUE;
	}
	return Result;
}

bool sub_104B09C(HKEY hKey, LPWSTR lpszValueName, DWORD dwValueNameSize, DWORD arg_C, PDWORD arg_10) {
	DWORD var_10 = 0;
	if (arg_C == 0) {
		var_10 = sizeof(off_1075820) / sizeof(off_1075820[0]);
	} else if (arg_C == 1) {
		var_10 = sizeof(aszAdditionalGracePeriodTags) / sizeof(aszAdditionalGracePeriodTags[0]);
	}
	for (DWORD var_14 = 0; var_14 < var_10; var_14++) {
		WCHAR var_21C[0x104];
		if (arg_C == 0) {
			sub_104AC41(
				lpszValueName,
				dwValueNameSize,
				CWPAStringsDecryptor(off_1075820[var_14].Data1, off_1075820[var_14].Size1, unk_1019768)
			);
		} else {
			sub_104AC41(lpszValueName,
				dwValueNameSize,
				CWPAStringsDecryptor(aszAdditionalGracePeriodTags[var_14].Data1, aszAdditionalGracePeriodTags[var_14].Size1, unk_1019768)
			);
		}
		if (!WPAKeyExists(hKey, lpszValueName)) {
			if (arg_10 != NULL) {
				*arg_10 = 1;
			}
			return true;
		}
		if (arg_C == 0) {
			sub_104AC41(
				var_21C,
				sizeof(var_21C) / sizeof(var_21C[0]),
				CWPAStringsDecryptor(off_1075820[var_14].Data2, off_1075820[var_14].Size2, unk_1019768)
			);
		} else {
			sub_104AC41(var_21C,
				sizeof(var_21C) / sizeof(var_21C[0]),
				CWPAStringsDecryptor(aszAdditionalGracePeriodTags[var_14].Data2, aszAdditionalGracePeriodTags[var_14].Size2, unk_1019768)
			);
		}
		if (!WPAKeyExists(hKey, var_21C)) {
			if (arg_10 != NULL) {
				*arg_10 = 0;
			}
			return true;
		}
	}
	return false;
}

extern "C" HRESULT sub_104B34F(DWORD arg_0, CWPATimes* arg_4) {
	HRESULT hrz = S_OK;
	{
	CWPACryptHelper var_2C;
	HRESULT hr = var_2C.sub_104FD06(dword_10192F8, sizeof(dword_10192F8), 0);
	if (FAILED(hr)) {
		return hr;
	}
	AutoHKEY var_C;
	hr = sub_104A757(&var_C);
	if (FAILED(hr)) {
		return hr;
	}
	WCHAR szSubKey[MAX_PATH];
	DWORD tmp;
	if (!sub_104B09C(var_C, szSubKey, MAX_PATH, arg_0, &tmp)) {
		return E_WPA_ERROR_0506;
	}
	AutoHKEY var_18;
	DWORD err = RegOpenKeyEx(var_C, szSubKey, 0, KEY_READ, &var_18);
	if (err != ERROR_SUCCESS) {
		HRESULT hr = HRESULT_FROM_WIN32(err);
		return hr;
	}
	hr = var_2C.sub_105021B(
		var_18,
		CWPAStringsDecryptor(VALUENAME_ENC, sizeof(VALUENAME_ENC)/sizeof(VALUENAME_ENC[0]), unk_1019768),
		(LPBYTE)arg_4,
		sizeof(CWPATimes));
	if (FAILED(hr)) {
		return hr;
	}
	{
	bool ok = false;
	ULONG tmp1, tmp2;
	if (arg_4->dwSize == sizeof(*arg_4)) {
		OSVERSIONINFOEX VersionInfo;
		DWORD dwMask;
		VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
		GetVersionEx((OSVERSIONINFO*)&VersionInfo);
		if (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE || VersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			dwMask = 0x10000;
		} else {
			dwMask = 0;
		}
		DWORD dwProductId = 0x80000E7A | dwMask;
		if (arg_4->dwProductId == dwProductId) {
			ok = true;
		}
	}
	if (ok) {
			tmp1 = 0xE7A;
			NTSTATUS ntstatus = NtLockProductActivationKeys(&tmp1, &tmp2);
			HRESULT hr2 = HRESULT_FROM_NT(ntstatus);
			if (FAILED(hr2)) {
				ok = false;
			}
		}
	if (ok) {
		hrz = (tmp1 < 0xE69 ? E_WPA_KERNEL_TOO_OLD : S_OK);
	} else {
		hrz = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	}
	}
	return hrz ? hrz : hrz;
}

extern "C" HRESULT sub_104B689(DWORD arg_0, CWPATimes* arg_4) {
	HRESULT result;
	CWPACryptHelper var_30;
	HRESULT hr = var_30.sub_104FD06(dword_10192F8, sizeof(dword_10192F8), 0);
	if (FAILED(hr)) {
		result = hr;
	} else {
	AutoHKEY var_C;
	hr = sub_104A757(&var_C);
	if (FAILED(hr)) {
		result = hr;
	} else {
	WCHAR szSubKey[MAX_PATH];
	DWORD tmp;
	if (!sub_104B09C(var_C, szSubKey, MAX_PATH, arg_0, &tmp)) {
		result = E_WPA_ERROR_0506;
	} else {
	AutoHKEY var_18;
	if (tmp) {
	DWORD dwDisposition;
	DWORD err = RegCreateKeyEx(var_C, szSubKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &var_18, &dwDisposition);
	if (err != ERROR_SUCCESS) {
		result = HRESULT_FROM_WIN32(err);
	} else {
	hr = var_30.sub_105068E(
		var_18,
		CWPAStringsDecryptor(VALUENAME_ENC, sizeof(VALUENAME_ENC)/sizeof(VALUENAME_ENC[0]), unk_1019768),
		(LPBYTE)arg_4,
		sizeof(CWPATimes));
	if (FAILED(hr)) {
		result = hr;
	} else
	{
	ULONG tmp1, tmp2;
	tmp1 = 0xE7A;
	result = NtLockProductActivationKeys(&tmp1, &tmp2);
	result = HRESULT_FROM_NT(result);
	if (SUCCEEDED(result)) {
	if (tmp1 < 0xE69) {
		result = E_WPA_KERNEL_TOO_OLD;
	}
	if (tmp2 != GetSystemMetrics(SM_CLEANBOOT)) {
		result = E_WPA_GETSAFEMODE_HACKED;
	}
	if (SUCCEEDED(result) && SUCCEEDED(var_30.sub_105068E(
		var_18,
		CWPAStringsDecryptor(VALUENAME_ENC, sizeof(VALUENAME_ENC)/sizeof(VALUENAME_ENC[0]), unk_1019768),
		(LPBYTE)arg_4,
		sizeof(CWPATimes))))
	{
		result = E_FAIL;
	}
	}
	}
	}} else {
		result = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
	}}}}
	return result;
}

void regtime_do_nothing() {}
