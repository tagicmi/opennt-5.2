//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Decompiled by OpenXP's Development Team, 2023 - 2024
//
//  File:       basex.cxx
//
//--------------------------------------------------------------------------

#include "precomp.h"
#pragma hdrstop

#include <math.h>

#include "basex.h"
#include "lichwid.h"
#include "newcrypt.h"
#include "../shortsig00/shortsig2000.h"
#include "cidiid.h"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label

#ifdef _x64
extern "C" void __declspec Begin_Vspweb_Scp_Segment_3_4();
#endif

#if defined(_X86_)
void 
__declspec(naked) 
Begin_Vspweb_Scp_Segment_3_4() 
{
	__asm {
    	            mov     eax, 3
	BEGIN_SCP_SEGMENT_3_4_0_10_00_00:
    	            mov     ebx, 4
    	            retn
	}
}
#endif

#pragma warning(pop)

void cidiid_unused() { CWPABigNumDecimalConverter x; }

DWORD CacheCIDInfo(CONST DWORD arg_0[4], ULONGLONG arg_4, LPBYTE arg_C, DWORD arg_10, bool arg_14) {
	BYTE CID[16] = {NULL};
	ULONGLONG* dst = (ULONGLONG*)(CID + 8);
	*dst = arg_0[3] | ((ULONGLONG)arg_0[2] << 17);
	*dst |= (ULONGLONG)arg_0[0] << 41;
	*dst |= (ULONGLONG)arg_0[1] << 58;
	*(ULONGLONG*)CID = arg_4;
	DWORD err;
	if (arg_14) {
		err = sub_105BA4B(arg_C, arg_10, arg_10, CID, sizeof(CID));
	} else {
		err = sub_105BD36(arg_C, arg_10, arg_10, CID, sizeof(CID));
	}
	return err;
}

DWORD sub_105D0A7(CWPAHyperellipticParams* Params) {
	DWORD err = ERROR_SUCCESS;
	Params->dwCurveGenus = 2;
	Params->dwModulusSize = 2;
	Params->field_8 = 4;
	if (!PID_allocate_key_fields_dwords(Params)) {
		err = ERROR_OUTOFMEMORY;
		goto Done;
	}
	Params->dwPublicMultiplier = 0x10001;
	// prime modulus = 0x16A6B036D7F2A79
	Params->pModulus[0] = 0x6D7F2A79;
	Params->pModulus[1] = 0x16A6B03;
	// curve coefficients in y^2 = x^5 + a4*x^4 + a3*x^3 + a2*x^2 + a1*x + a0
	// a0 = 0
	Params->pCurveCoefficients[0] = 0;
	Params->pCurveCoefficients[1] = 0;
	// a1 = 0x21840136C85381
	Params->pCurveCoefficients[2] = 0x36C85381;
	Params->pCurveCoefficients[3] = 0x218401;
	// a2 = 0x44197B83892AD0
	Params->pCurveCoefficients[4] = 0x83892AD0;
	Params->pCurveCoefficients[5] = 0x44197B;
	// a3 = 0x1400606322B3B04
	Params->pCurveCoefficients[6] = 0x322B3B04;
	Params->pCurveCoefficients[7] = 0x1400606;
	// a4 = a3
	Params->pCurveCoefficients[8] = 0x322B3B04;
	Params->pCurveCoefficients[9] = 0x1400606;
	// leading coefficient 1
	Params->pCurveCoefficients[10] = 1;
	Params->pCurveCoefficients[11] = 0;
Done:
	return err;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
extern "C" void __declspec() End_Vspweb_Scp_Segment_3_4();
#endif
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_4() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_4:
                mov     edx, 4
                retn
}
}
#endif
#pragma warning(pop)

DWORD sub_105D231(LPBYTE lpData, DWORD cbData) {
	CWPAShortSigKey* Key = NULL;
	CWPAHyperellipticParams Params;
	DWORD err = sub_105D0A7(&Params);
	if (err != ERROR_SUCCESS) {
		goto Cleanup;
	}
	if (!PID_setup_key(&Params, &Key)) {
		err = ERROR_INVALID_PARAMETER;
		goto Cleanup;
	}
	PID_free_key_fields_dwords(&Params);
	// deserialize (lpData,cbData) as divisor, multiply by PublicMultiplier, serialize back to lpData
	if (!PID_verify(lpData, cbData, Key, lpData)) {
		err = ERROR_BAD_SHORTSIG_1;
		goto Cleanup;
	}
Cleanup:
	if (Key != NULL) {
		PID_unsetup_key(Key);
	}
	return err;
}

DWORD WPAValidatePhoneActivation(LPCWSTR arg_0, DWORD arg_4[4], HWID arg_8, DWORD* arg_10, DWORD* arg_14, DWORD* arg_18, DWORD* arg_1C, DWORD* arg_20, DWORD* arg_24, DWORD* arg_28, DWORD* arg_2C, BYTE* arg_30, DWORD* arg_34) {
	LPBYTE var_10 = NULL;
	CWPABigNumDecimalConverter var_48;
	ULONGLONG var_18 = 0;
	BYTE var_28[16];
	ZeroMemory(var_28, sizeof(var_28));
	DWORD err;
	if (arg_0 == NULL || arg_4 == NULL || arg_8.AsQword == 0 || arg_10 == NULL || arg_14 == NULL || arg_18 == NULL || arg_2C == NULL || arg_1C == NULL || arg_20 == NULL || arg_24 == NULL || arg_28 == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	var_48.CalculateCharacterRepresentationInfo((DWORD)ceil(115 * log10(2.0)));
	err = var_48.ConvertWideStringToByteArray(arg_0, &var_10);
	if (err != ERROR_SUCCESS) {
		goto Done;
	}
	DWORD next = GetTickCount() + 2000;
	do {
		Sleep(500);
	} while (GetTickCount() < next);
	memcpy(var_28, var_10, 15);
	err = sub_105D231(var_28, 14);
	if (err != ERROR_SUCCESS) {
		goto Done;
	}
	err = CacheCIDInfo(arg_4, arg_8.AsQword, var_28, 14, false);
	if (err != ERROR_SUCCESS) {
		goto Done;
	}
	if (var_28[7] > 0x80) {
		err = ERROR_BAD_SHORTSIG_2;
		goto Done;
	}
	for (DWORD i = 8; i < 14; i++) {
		if (var_28[i] != 0) {
			err = ERROR_BAD_SHORTSIG_2;
			goto Done;
		}
	}
	memcpy(&var_18, var_28, 7);
	ULONGLONG tmp = (var_18 >> 48) & 0xFF;
	*arg_2C = (DWORD)tmp;
	if (*arg_2C == 0) {
		goto Done;
	}
	tmp = var_18 & 0xFF;
	DWORD tmp2 = (DWORD)tmp;
	if (tmp2 == 0) {
		goto Done;
	}
	if (*arg_34 == 0 || tmp2 > *arg_34) {
		goto Done;
	}
	*arg_34 = tmp2;
	tmp = (var_18 >> 8) & 0xFFFFFFFFFFi64;
	memcpy(arg_30, &tmp, tmp2);
Done:
	next = GetTickCount() + 2000;
	do {
		Sleep(500);
	} while (GetTickCount() < next);
	if (var_10 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_10);
		var_10 = NULL;
	}
	return err;
}
