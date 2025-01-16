#pragma once
#include "licstore.h"

class CWPAClass4;
class CWPALicenseManager
{
	CWPALicenseStore m_Store;
	CHAR field_118[MAX_PATH + 1];
	DWORD field_220;

public:
	CWPALicenseManager(); // sub_1052F75
	~CWPALicenseManager(); // sub_1053053
	DWORD sub_1053728(LPCVOID lpStoreKeyPart1, DWORD cbStoreKeyPart1);
	DWORD sub_1053A3C(LPVOID arg_0, DWORD arg_4);
	DWORD sub_1053D0D(DWORD dwRecordId);
	DWORD sub_1053DB7(DWORD arg_0);
	DWORD sub_1053E99();
	DWORD sub_1053F48();
	DWORD sub_1053FF3();
	DWORD sub_1054098();
	DWORD sub_105413C();
	DWORD sub_10541E2();
	DWORD sub_1054285(DWORD dwRecordId, LPCVOID lpData, DWORD cbData, BOOL fEncrypt);
	DWORD sub_1054386(DWORD dwRecordId, LPVOID* ppData, DWORD* pcbData);
	DWORD sub_10546A9(DWORD arg_0);
	DWORD sub_1054789(DWORD arg_0);
	DWORD ValidateActivation(DWORD dwRecordId, CWPAClass4* arg_4);
	DWORD sub_10552D8(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8);
private:
    DWORD sub_1053C0F(DWORD arg_0, DWORD arg_4);
    DWORD sub_1054438(LPCWSTR arg_0, DWORD* arg_4);
    BOOL sub_1054612(LPCWSTR lpString, DWORD nStartPos, DWORD nEndPos);
    BOOL sub_1055169(LPCWSTR lpString);
};
