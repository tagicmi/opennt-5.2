#include "precomp.h"
#pragma hdrstop
#include "bios.h"
#include "strutils.h"
#include "iniparser.h"
#include "inisection.h"
#include "bl.h"

#include "blparser.h"

CBLParserCallback::CBLParserCallback() {
	field_14 = 0;
	field_4 = 0;
	field_8 = 0;
	field_C = 0;
	field_10 = 0;
	m_bFound = FALSE;
	field_1C = 0;
}

CBLParserCallback::~CBLParserCallback() {
	if (field_14 != NULL) {
		LocalFree(field_14);
	}
}

HRESULT CBLParserCallback::sub_1050BEB(LPCSTR pData) {
	DWORD err;
	LPSTR edx = NULL;
	if (pData == NULL) {
		err = E_INVALIDARG;
		goto Done;
	}
	edx = (LPSTR)LocalAlloc(0, strlen(pData) + 1);
	if (edx == NULL) {
		err = E_OUTOFMEMORY;
		goto Done;
	}
	strcpy(edx, pData);
	field_4 = edx;
	field_8 = strchr(edx, '-');
	if (field_8 == NULL) {
		err = E_INVALIDARG;
		goto Done;
	}
	*field_8 = 0;
	++field_8;
	field_C = strchr(field_8, '-');
	if (field_8 == NULL) { // probably a bug, field_C intended
		err = E_INVALIDARG;
		goto Done;
	}
	*field_C = 0;
	++field_C;
	field_10 = strchr(field_C, '-');
	if (field_10 == NULL) {
		err = E_INVALIDARG;
		goto Done;
	}
	*field_10 = 0;
	++field_10;
	if (field_14 != NULL) {
		LocalFree(field_14);
		field_14 = NULL;
	}
	field_14 = edx;
	edx = NULL;
	if (strlen(field_4) != 5 || strlen(field_8) != 3 || strlen(field_C) != 7 || strlen(field_10) != 5) {
		err = E_INVALIDARG;
		goto Done;
	}
	field_C[strlen(field_C) - 1] = 0;
	field_10[strlen(field_10) - 3] = 0;
	err = S_OK;
Done:
	if (edx != NULL) {
		LocalFree(edx);
	}
	return err;
}

BOOL CBLParserCallback::RangeMatch(LPCSTR arg_0, LPCSTR arg_4, LPCSTR arg_8) {
	BOOL var_4 = FALSE;
	if (strlen(arg_0) != 6 || strlen(arg_4) != 6 || strlen(arg_8) != 6) {
		return FALSE;
	}
	DWORD esi = HEXSTR2DWORD(arg_0, &var_4);
	var_4 = FALSE;
	DWORD edi = HEXSTR2DWORD(arg_4, &var_4);
	var_4 = FALSE;
	DWORD eax = HEXSTR2DWORD(arg_8, &var_4);
	BOOL result;
	if (esi >= edi && esi <= eax) {
		result = TRUE;
	} else {
		result = FALSE;
	}
	return result;
}

BOOL CBLParserCallback::TwoFieldMatch(LPCSTR arg_0, LPCSTR arg_4) {
	if (0 == strcmp("*", arg_4)) {
		return TRUE;
	}
	if (0 == strcmp(arg_0, arg_4)) {
		return TRUE;
	}
	char* question = strchr(arg_4, '?');
	if (question == NULL || 0 != strncmp(arg_0, arg_4, arg_4 + strlen(arg_4) - question)) {
		return FALSE;
	}
	return TRUE;
}

BOOL CBLParserCallback::HandleParsedData(void* pLine, int nLines) {
	if (pLine == NULL) {
		return FALSE;
	}
	if (nLines == 0) {
		return TRUE;
	}
	CIniLine* pIniLine = (CIniLine*)pLine;
	pIniLine->MoveToFirstString();
	PCSTR var_4 = 0;
	PCSTR var_8 = 0;
	PCSTR var_10 = 0;
	PCSTR var_C = 0;
	PCSTR var_14 = 0;
	DWORD esi = 0;
	const char* pField = pIniLine->MoveToNextString();
	DWORD arg_4 = 0;
	while (pField != NULL && arg_4 < 6) {
		BOOL var_18 = FALSE;
		switch (arg_4) {
		case 5:
			if (0 == strcmp("*", pField)) {
				esi = 0xFFFFFFFF;
			} else {
				esi = HEXSTR2DWORD(pField, &var_18);
			}
			break;
		case 4:
			var_14 = pField;
			break;
		case 3:
			var_C = pField;
			break;
		case 2:
			var_10 = pField;
			break;
		case 1:
			var_8 = pField;
			break;
		case 0:
			var_4 = pField;
			break;
		default:
			return TRUE;
		}
		pField = pIniLine->MoveToNextString();
		++arg_4;
	}
	if (TwoFieldMatch(field_4, var_4)
		&& TwoFieldMatch(field_8, var_8)
		&& RangeMatch(field_C, var_10, var_C)
		&& TwoFieldMatch(field_10, var_14))
	{
		m_bFound = TRUE;
		field_1C = esi;
		return FALSE;
	}
	return TRUE;
}

HRESULT SearchAndCheckPID(BYTE* lpIniData, DWORD cbIniData, PCWSTR lpszProductId, BOOL fOem, DWORD* arg_10) {
	CBLParserCallback var_50;
	CIniParser var_80(&var_50);
	CIniSection var_30;
	LPSTR hMem = NULL;
	volatile DWORD var_18 = 0;
	HRESULT hr;
	if (lpIniData == NULL || cbIniData == 0 || lpszProductId == NULL || arg_10 == NULL) {
		hr = E_INVALIDARG;
		goto Cleanup;
	}
	*arg_10 = 0;
	DWORD uBytes = 0;
	for (;;) {
		uBytes = WideCharToMultiByte(GetACP(), 0, lpszProductId, -1, hMem, uBytes, NULL, NULL);
		if (uBytes == 0) {
			hr = HRESULT_FROM_WIN32(GetLastError());
			goto Cleanup;
		}
		if (hMem != NULL) {
			break;
		}
		hMem = (LPSTR)LocalAlloc(0, uBytes);
		if (hMem == NULL) {
			hr = E_OUTOFMEMORY;
			goto Cleanup;
		}
	}
	hr = var_50.sub_1050BEB(hMem);
	if (hr != S_OK) {
		goto Cleanup;
	}
	DWORD err = var_30.Attach((LPCSTR)lpIniData, cbIniData, fOem ? "OEM-5.1" : "MS-5.1");
	if (err != ERROR_SUCCESS) {
		hr = HRESULT_FROM_WIN32(err);
		goto Cleanup;
	}
	err = var_30.Parse(var_80);
	if (err != ERROR_SUCCESS) {
		hr = HRESULT_FROM_WIN32(err);
		goto Cleanup;
	}
	DWORD eax = (NULL != &var_18) ? var_50.field_1C : *&var_18;
	if (var_50.m_bFound) {
		*arg_10 = eax;
	}
Cleanup:
	if (hMem != NULL) {
		LocalFree(hMem);
	}
	return hr;
}

BOOL CBLVerParserCallback::HandleParsedData(void* pLine, int nLines) {
	if (pLine == NULL) {
		return FALSE;
	}
	if (nLines == 0) {
		return TRUE;
	}
	const char* pFieldName = ((CIniLine*)pLine)->MoveToFirstString();
	if (0 != strcmp(pFieldName, "Version")) {
		return TRUE;
	}
	const char* pFieldValue = ((CIniLine*)pLine)->MoveToNextString();
	lstrcpynA(m_Version, pFieldValue, MAX_PATH);
	return FALSE;
}

HRESULT sub_1051879(LPCWSTR lpszBaseDir, LPCWSTR arg_4, INT arg_8, PDWORD arg_C) {
	if (arg_C == 0) {
		return E_INVALIDARG;
	}
	if (!sub_104F0CA(WPAFileType3, lpszBaseDir, arg_4, arg_8, arg_C, NULL)) {
		*arg_C = 0xFFFFFFFF;
		return GetLastError() == ERROR_FILE_NOT_FOUND ? HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) : E_FAIL;
	}
	return S_OK;
}

HRESULT GetBLVersion(BYTE* arg_0, DWORD arg_4, struct BLPIDFILE_VERSIONINFO * arg_8) {
	CBLVerParserCallback var_15C;
	CIniParser var_54(&var_15C);
	CIniSection var_24;

	DWORD hr = var_24.Attach((const char*)arg_0, arg_4, "Version");
	if (hr) goto exit;
	hr = var_24.Parse(var_54);
	if (hr) goto exit;
	const char* ver = var_15C.sub_1050A8F();
	if (NULL != ver && *ver) {
		float x = (float)atof(ver);
		arg_8->field_0 = (int)x;
		arg_8->field_2 = (int)((x - arg_8->field_0) * 1000.f);
	}
exit:
	hr = HRESULT_FROM_WIN32(hr);
	return hr;
}
