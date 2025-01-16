#include "precomp.h"
#pragma hdrstop
#include "iniparser.h"

#include "trim.h"

CIniLine::CIniLine() {
	field_1C = 0;
	field_20 = 0;
	field_24 = 0;
}

CIniLine::~CIniLine() {
}

void CIniLine::Reset() {
	field_1C = 0;
	field_20 = 0;
	field_24 = 0;
	CAutoString::Reset();
}

CIniParser::CIniParser(CParserCallback* pCallback) {
	AttachParserCallbackObject(pCallback);
	m_Line.ChangeIncreaseSize(0x200);
}

CIniParser::~CIniParser()
{
}

void CIniParser::AttachParserCallbackObject(CParserCallback* pCallback) {
	m_pCallback = pCallback;
}

BOOL AddField(CAutoString& List, BOOL fIgnoreEmpty, LPCSTR lpValueBegin, LPCSTR lpValueEnd) {
	BOOL result = FALSE;
	TrimHeadBlank(lpValueBegin, lpValueEnd);
	if (lpValueBegin <= lpValueEnd) {
		TrimTrailBlank(lpValueEnd, lpValueBegin);
		DWORD_PTR wtadd = lpValueEnd - lpValueBegin + 1;
		List.AddString(lpValueBegin, (DWORD)(wtadd));
		result = TRUE;
	} else if (!fIgnoreEmpty) {
		List.AddString("\0");
		result = TRUE;
	}
	return result;
}

DWORD CIniParser::Parse(LPCSTR lpData, DWORD cbData) {
	DWORD err = ERROR_SUCCESS;
	if (lpData == NULL) {
		err = ERROR_INVALID_PARAMETER;
		goto Done;
	}
	LPCSTR pCur = lpData;
	LPCSTR var_C = lpData;
	LPCSTR var_4 = lpData;
	BOOL fContinue = TRUE;
	DWORD nFields = 0;
	m_Line.Reset();
	LPCSTR lpEnd = lpData + cbData;
	while (pCur < lpEnd) {
		if (!fContinue) {
			goto Done2;
		}
		switch (*pCur) {
		case '=':
			if (nFields == 0) {
				m_Line.field_1C = TRUE;
				if (AddField(m_Line, FALSE, var_4, pCur - 1)) {
					nFields = 1;
				}
				++pCur;
				var_4 = pCur;
			} else {
				++pCur;
			}
			break;
		case ';':
			if (AddField(m_Line, nFields == 0, var_4, pCur - 1)) {
				++nFields;
			}
			while (*pCur != '\r' && *pCur != '\n' && pCur < lpEnd) {
				++pCur;
			}
			var_4 = pCur;
			break;
		case ',':
			if (AddField(m_Line, FALSE, var_4, pCur - 1)) {
				++nFields;
			}
			++pCur;
			var_4 = pCur;
			break;
		case '\n':
		case '\r':
			if (AddField(m_Line, nFields == 0, var_4, pCur - 1)) {
				++nFields;
			}
			m_Line.field_20 = var_C;
			m_Line.field_24 = (DWORD)(pCur - var_C);
			if (m_pCallback != NULL && nFields > 0) {
				fContinue = m_pCallback->HandleParsedData(&m_Line, 1);
			}
			TrimLF(pCur, lpEnd);
			m_Line.Reset();
			nFields = 0;
			var_C = pCur;
			var_4 = pCur;
			break;
		default:
			++pCur;
			break;
		}
		if (pCur == lpEnd) {
			if (AddField(m_Line, nFields == 0, var_4, pCur - 1)) {
				m_Line.field_20 = var_C;
				m_Line.field_24 = (DWORD)(pCur - var_C);
			}
			if (m_pCallback != NULL && nFields > 0) {
				fContinue = m_pCallback->HandleParsedData(&m_Line, 1);
			}
		}
	}
Done2:;
Done:
	return err;
}
