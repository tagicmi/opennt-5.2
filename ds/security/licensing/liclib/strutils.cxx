#include "precomp.h"
#pragma hdrstop
#include "strutils.h"

BOOL IsHEX(const char* p) {
	if (p == NULL || *p == 0) {
		return FALSE;
	}
	for (; *p; p++) {
		if (!(*p >= '0' && *p <= '9') && !(*p >= 'a' && *p <= 'f') && !(*p >= 'A' && *p <= 'F')) {
			return FALSE;
		}
	}
	return TRUE;
}

DWORD HEXSTR2DWORD(const char* p, BOOL* pfSuccess) {
	*pfSuccess = IsHEX(p);
	if (!*pfSuccess) {
		return 0;
	}
	DWORD result = 0;
	if (!sscanf(p, "%x", &result)) {
		result = 0;
		*pfSuccess = FALSE;
	}
	return result;
}
