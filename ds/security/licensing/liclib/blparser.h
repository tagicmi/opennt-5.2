class CBLParserCallback : public CParserCallback {
	LPSTR field_4;
	LPSTR field_8;
	LPSTR field_C;
	LPSTR field_10;
	LPVOID field_14;
public:
	BOOL m_bFound;
	DWORD field_1C;
	CBLParserCallback();
	~CBLParserCallback();
	virtual BOOL HandleParsedData(void* pLine, int nLines);
	virtual BOOL HasError() const { return 0; }
	HRESULT sub_1050BEB(LPCSTR pData);
private:
	BOOL RangeMatch(LPCSTR arg_0, LPCSTR arg_4, LPCSTR arg_8);
	BOOL TwoFieldMatch(LPCSTR arg_0, LPCSTR arg_4);
};

class CBLVerParserCallback : public CParserCallback {
	char m_Version[MAX_PATH];
public:
	CBLVerParserCallback() {
		m_Version[0] = 0;
	}
	~CBLVerParserCallback() {}
	virtual BOOL HandleParsedData(void* pLine, int nLines);
	virtual BOOL HasError() const { return 0; }
	virtual char* sub_1050A8F() { return m_Version; }
};
