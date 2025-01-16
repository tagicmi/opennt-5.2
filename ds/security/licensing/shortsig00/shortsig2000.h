#pragma once
typedef struct
{
	DWORD dwCurveGenus;
	DWORD dwModulusSize; // in dwords
	DWORD field_8;
	DWORD dwPublicMultiplier;
	DWORD field_10;
	LPDWORD field_14;
	LPDWORD pModulus;
	LPDWORD pCurveCoefficients;
	LPDWORD field_20;
	LPDWORD field_24[2];
} CWPAHyperellipticParams;

typedef struct tagWPAShortSigKey CWPAShortSigKey;

#ifdef __cplusplus
extern "C" {
#endif

BOOL PID_allocate_key_fields_dwords(CWPAHyperellipticParams* pParams);
BOOL PID_setup_key(CWPAHyperellipticParams* pParams, CWPAShortSigKey** ppKey);
BOOL PID_free_key_fields_dwords(CWPAHyperellipticParams* pParams);
BOOL PID_verify(CONST BYTE* lpData, DWORD cbData, const CWPAShortSigKey* pKey, LPBYTE lpOut);
BOOL PID_unsetup_key(CWPAShortSigKey* pKey);

#ifdef __cplusplus
}
#endif
