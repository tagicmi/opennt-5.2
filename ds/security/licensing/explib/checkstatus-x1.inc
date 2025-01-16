#include "storeinlsa.h"
#include "../include/trivialencrypt.h"

HRESULT GetPerMachine128BitSeed(BYTE arg_0[16]) {
	BYTE var_1C[16] = {0xCC, 0xC3, 0x8B, 0xFF, 0xCC, 0xC3, 0x8B, 0xFF, 0x8B, 0x44, 0x24, 4, 0xCC, 0xC2, 4, 0};
	// L"G${ED8F4747-E13D-47bc-856B-5CEFE1A81A7F}"
	WCHAR var_78[] = {0x987C,0x29C1,0xC868,0x2B0D,0x44C5,0x0424,0x5E4F,0xA547,0xCCE9,0xE2DA,0xECE5,0x518A,0xA23D,0x9479,0x63D2,0x5684,0x8FD5,0x699E,0x1FA8,0x9F6F,0xBC20,0x6A4B,0x0701,0x9E3F,0x1F3C,0xE17D,0x17B9,0x3D88,0xB18B,0x6DED,0x907A,0xC088,0xCC1D,0x561D,0xD618,0x67C9,0x1D94,0xE490,0x0C8D,0xB5C5,0xE92C,0xB21A,0x67CF};
	WCHAR String1[0x2A];
	lstrcpyn(String1, CWPAStringsDecryptor(var_78, sizeof(var_78) / sizeof(var_78[0]), var_1C), sizeof(String1) / sizeof(String1[0]) - 1);
	CLSAStoreForWPA var_A4(NULL, POLICY_GET_PRIVATE_INFORMATION, String1);
	DWORD var_20 = 16;
	RPC_STATUS status = var_A4.LoadData(arg_0, &var_20);
	if (SUCCEEDED(status)) {
		return status;
	}
	CLSAStoreForWPA var_C0(NULL, POLICY_CREATE_SECRET, String1);
	UUID Uuid;
	status = UuidCreate(&Uuid);
	if (FAILED(status)) {
		return status;
	}
	status = var_C0.StoreData((LPBYTE)&Uuid, sizeof(Uuid));
	memcpy(arg_0, &Uuid, var_20);
	return status;
}
