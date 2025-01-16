#pragma once
class CWPABigNumBaseConverter {
	DWORD lpszAlphabetField_0;
	DWORD lpszAlphabetField_4;
	DWORD lpszAlphabetField_8;

	DWORD lpszAlphabetField_10;
	DWORD lpszAlphabetField_12;
	DWORD lpszAlphabetField_14;

	LPWSTR m_lpszAlphabet;
	DWORD m_dwBase;

	DWORD SetAlphabetAndBase(LPCWSTR lpszAlphabet);

public:
	explicit CWPABigNumBaseConverter(LPCWSTR lpszAlphabet); // sub_105B97D
	~CWPABigNumBaseConverter(); // sub_105AF48
	void CalculateDigitCountAndByteSize(DWORD nBits);
	DWORD ConvertByteDataToWideString(CONST BYTE* lpBinaryData, LPWSTR* ppszResult);
	void CalculateCharacterRepresentationInfo(DWORD nChars);
	DWORD ConvertWideStringToByteArray(LPCWSTR lpTextData, PBYTE* ppResult);
};

class CWPABigNumBase24Converter : public CWPABigNumBaseConverter {
public:
	CWPABigNumBase24Converter() : CWPABigNumBaseConverter(L"BCDFGHJKMPQRTVWXY2346789") {} // sub_104A57F
};

class CWPABigNumDecimalConverter : public CWPABigNumBaseConverter {
public:
	CWPABigNumDecimalConverter() : CWPABigNumBaseConverter(L"0123456789") {}
};
