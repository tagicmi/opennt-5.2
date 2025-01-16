#pragma once
#include "bl.h"
// the following probably should be in a separate include
extern void sub_104E349(LPCVOID lpData, DWORD cbData, BYTE md5[16]);
enum WPAFILETYPE {
	WPAFileType0,
	WPAFileType1,
	WPAFileType2,
	WPAFileType3,
};
extern "C" bool sub_104F0CA(WPAFILETYPE FileType, LPCWSTR lpszBaseDir, LPCWSTR arg_8, INT arg_C, PDWORD arg_10, BLPIDFILE_VERSIONINFO* arg_14);
