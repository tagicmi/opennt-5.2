//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Decompiled by OpenXP's Development Team, 2023 - 2024
//
//  File:       basex.cxx
//
//--------------------------------------------------------------------------

#include "precomp.h"
#pragma hdrstop

#include <math.h>
#include "basex.h"

CWPABigNumBaseConverter::
CWPABigNumBaseConverter(
						LPCWSTR lpszAlphabet
						)
{
	m_lpszAlphabet = NULL;
	m_dwBase = 0;
	lpszAlphabetField_0 = 0;
	lpszAlphabetField_4 = 0;
	lpszAlphabetField_8 = 0;
	lpszAlphabetField_10 = 0;
	lpszAlphabetField_12 = 0;
	lpszAlphabetField_14 = 0;
	SetAlphabetAndBase(lpszAlphabet);
}

CWPABigNumBaseConverter::
~CWPABigNumBaseConverter()
{
	if (m_lpszAlphabet != NULL) {
		HeapFree(GetProcessHeap(), 0, m_lpszAlphabet);
		m_lpszAlphabet = NULL;
		m_dwBase = 0;
	}
}

DWORD 
CWPABigNumBaseConverter::
SetAlphabetAndBase(
				   LPCWSTR lpszAlphabet
				   )
{
	DWORD ReturnStatus = ERROR_SUCCESS;
	if (lpszAlphabet != NULL) {
		DWORD lpszAlphabet_wide = wcslen(lpszAlphabet);

		m_lpszAlphabet = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (lpszAlphabet_wide + 1) * sizeof(WCHAR));

		if (m_lpszAlphabet == 0) {
			ReturnStatus = ERROR_OUTOFMEMORY;
			return ReturnStatus;
		}
		//m_lpszAlphabet allocation didn't result in a memory leak
		wcscpy(m_lpszAlphabet, lpszAlphabet);
		m_dwBase = lpszAlphabet_wide;
	} else {
		if (m_lpszAlphabet != NULL) {
			//Reset m_dwBase on the condition that lpszAlphabet is NULL.
			HeapFree(GetProcessHeap(), 0, m_lpszAlphabet);
			m_lpszAlphabet = NULL;
			m_dwBase = 0;
		}
	}
	return ReturnStatus;
}

void 
CWPABigNumBaseConverter::
CalculateDigitCountAndByteSize(
							   DWORD nBits
							   )
{
	double tmp = nBits * log10(2) / log10(m_dwBase);
	lpszAlphabetField_0 = (DWORD)tmp;
	if (lpszAlphabetField_0 < tmp)
		lpszAlphabetField_0++;
	lpszAlphabetField_4 = nBits; //Never used...
	lpszAlphabetField_8 = nBits / 8 + (nBits % 8 ? 1 : 0);
}

DWORD 
CWPABigNumBaseConverter::
ConvertByteDataToWideString(
							CONST BYTE* lpBinaryData, 
							LPWSTR* ppszResult
							) 
{
	DWORD ReturnStatus = ERROR_SUCCESS;
	*ppszResult = NULL;
	LPBYTE lpMem = NULL;
	LONG AlphabetFieldBase = lpszAlphabetField_0;

	if (lpBinaryData == NULL) {
		ReturnStatus = ERROR_INVALID_PARAMETER;
		goto Cleanup;
	}
	LPWSTR AlphabetField = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (lpszAlphabetField_0 + 1) * sizeof(WCHAR));

	if (AlphabetField == NULL) {
		//Something went horribly wrong here.
		ReturnStatus = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	lpMem = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, lpszAlphabetField_8);

	if (lpMem == NULL) {
		ReturnStatus = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	memcpy(lpMem, lpBinaryData, lpszAlphabetField_8);
	AlphabetField[AlphabetFieldBase] = 0;
	for (; --AlphabetFieldBase >= 0; ) {
		DWORD edx = 0;
		LONG FieldItteration = lpszAlphabetField_8;
		for (; --FieldItteration >= 0; ) {
			DWORD ecx = edx * 0x100 + lpMem[FieldItteration];
			lpMem[FieldItteration] = (BYTE)(ecx / m_dwBase);
			edx = ecx % m_dwBase;
		}
		AlphabetField[AlphabetFieldBase] = m_lpszAlphabet[edx];
	}
	*ppszResult = AlphabetField;
Cleanup:
	if (lpMem != NULL) {
		HeapFree(GetProcessHeap(), 0, lpMem);
	}
	if (ReturnStatus != ERROR_SUCCESS && AlphabetField != NULL) {
		HeapFree(GetProcessHeap(), 0, AlphabetField);
	}
	return ReturnStatus;
}

void 
CWPABigNumBaseConverter::
CalculateCharacterRepresentationInfo(
									 DWORD nChars
									 )
{
	lpszAlphabetField_10 = nChars;
	double tmp = nChars * log10(m_dwBase) / log10(2);
	lpszAlphabetField_14 = (DWORD)tmp;
	if (lpszAlphabetField_14 < tmp)
		lpszAlphabetField_14++;
	lpszAlphabetField_12 = lpszAlphabetField_14 / 8 + (lpszAlphabetField_14 % 8 ? 1 : 0);
}

DWORD 
CWPABigNumBaseConverter::
ConvertWideStringToByteArray(
							 LPCWSTR lpTextData, 
							 PBYTE* ppResult
							 )
{
	*ppResult = NULL;
	DWORD ReturnStatus = ERROR_SUCCESS;
	DWORD lastNonZeroIndex = 0;
	PBYTE FieldHeap = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, lpszAlphabetField_12);

	if (FieldHeap == NULL) {
		ReturnStatus = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	for (; *lpTextData; lpTextData++) {
		LPCWSTR pChar = wcschr(m_lpszAlphabet, *lpTextData);
		if (pChar == NULL) {
			ReturnStatus = ERROR_INVALID_DATA;
			goto Cleanup;
		}
		DWORD_PTR digit = pChar - m_lpszAlphabet;
		DWORD i;
		for (i = 0; i <= lastNonZeroIndex; i++) {
			digit += FieldHeap[i] * m_dwBase;
			FieldHeap[i] = (BYTE)digit;
			digit >>= 8;
		}
		if (digit != 0) {
			FieldHeap[i] = (BYTE)digit;
			lastNonZeroIndex = i;
		}
	}
	*ppResult = FieldHeap;
Cleanup:
	if (ReturnStatus != ERROR_SUCCESS && FieldHeap != NULL) {
		HeapFree(GetProcessHeap(), 0, FieldHeap);
	}
	return ReturnStatus;
}
