#pragma once
#include "log.h"

class CIniLine : public CAutoString {
public:
	DWORD_PTR field_1C;
	LPCSTR field_20;
	DWORD field_24;
	CIniLine();
	~CIniLine();
	virtual void Reset();
};

class CParserCallback {
public:
	virtual BOOL HandleParsedData(void* lpData, int cbData) = 0;
	virtual BOOL HasError() const = 0;
};

class CParser {
public:
	virtual DWORD Parse(LPCSTR lpData, DWORD cbData) = 0;
	virtual void AttachParserCallbackObject(CParserCallback* pCallback) = 0;
};

class CIniParser : public CParser {
	CParserCallback* m_pCallback;
	CIniLine m_Line;
public:
	CIniParser(CParserCallback* pCallback);
	~CIniParser();
	virtual DWORD Parse(LPCSTR lpData, DWORD cbData);
	virtual void AttachParserCallbackObject(CParserCallback* pCallback);
};
