#include "precomp.h"
#pragma hdrstop
#include <crypto/rc4.h>
#include <crypto/md5.h>
#include "../shortsig/sigpriv.h"
#include "newcrypt.h"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_8() {
__asm {
                mov     eax, 3
BEGIN_SCP_SEGMENT_3_8_0_10_00_00:
                mov     ebx, 8
                retn
}
}
#endif
#pragma warning(pop)

DWORD sub_105BA4B(LPBYTE arg_0, DWORD arg_4, DWORD ignored, CONST BYTE* arg_C, DWORD arg_10) {
	DWORD err = ERROR_SUCCESS;
	LPBYTE lpMem = NULL;
	LPBYTE var_4 = NULL;
	LPBYTE var_8 = NULL;
	LPDWORD var_C = NULL;
	DWORD size1 = arg_4 / 2;
	lpMem = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (lpMem == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_4 = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (var_4 == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_8 = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (var_8 == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_C = (LPDWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (size1 + 3) / 4 * 4);
	if (var_C == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	DWORD i, j;
	for (i = 0; i < size1; i++) {
		lpMem[i] = arg_0[i];
	}
	for (i = size1; i < 2*size1; i++) {
		var_4[i-size1] = arg_0[i];
	}
	for (j = 0; j < 4; j++) {
		err = ShortSigHash(var_4, size1, (CONST DWORD*)arg_C, arg_10 / 4, var_C, size1 * 8);
		for (i = 0; i < size1; i++) {
			var_8[i] = var_4[i];
		}
		for (i = 0; i < size1; i++) {
			var_4[i] = lpMem[i] ^ ((LPBYTE)var_C)[i];
		}
		for (i = 0; i < size1; i++) {
			lpMem[i] = var_8[i];
		}
	}
	for (i = 0; i < size1; i++) {
		arg_0[i] = lpMem[i];
	}
	for (i = 0; i < size1; i++) {
		arg_0[i+size1] = var_4[i];
	}
Cleanup:
	if (lpMem != NULL) {
		HeapFree(GetProcessHeap(), 0, lpMem);
	}
	if (var_4 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_4);
	}
	if (var_8 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_8);
	}
	if (var_C != NULL) {
		HeapFree(GetProcessHeap(), 0, var_C);
	}
	return err;
}

DWORD sub_105BD36(LPBYTE arg_0, DWORD arg_4, DWORD arg_8, CONST BYTE* arg_C, DWORD arg_10) {
	DWORD err = ERROR_SUCCESS;
	LPBYTE lpMem = NULL;
	LPBYTE var_4 = NULL;
	LPBYTE var_8 = NULL;
	LPDWORD var_C = NULL;
	DWORD size1 = arg_4 / 2;
	lpMem = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (lpMem == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_4 = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (var_4 == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_8 = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size1);
	if (var_8 == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	var_C = (LPDWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (size1 + 3) / 4 * 4);
	if (var_C == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	DWORD i, j;
	for (i = 0; i < size1; i++) {
		lpMem[i] = arg_0[i];
	}
	for (i = size1; i < 2*size1; i++) {
		var_4[i-size1] = arg_0[i];
	}
	for (j = 0; j < 4; j++) {
		// IN: next(first) = second, next(second) = first ^ hash
		// OUT: first = next(second) ^ hash, second = next(first)
		ShortSigHash(lpMem, size1, (CONST DWORD*)arg_C, arg_10 / 4, var_C, size1 * 8);
		for (i = 0; i < size1; i++) {
			var_8[i] = lpMem[i];
		}
		for (i = 0; i < size1; i++) {
			lpMem[i] = var_4[i] ^ ((LPBYTE)var_C)[i];
		}
		for (i = 0; i < size1; i++) {
			var_4[i] = var_8[i];
		}
	}
	for (i = 0; i < size1; i++) {
		arg_0[i] = lpMem[i];
	}
	for (i = 0; i < size1; i++) {
		arg_0[i+size1] = var_4[i];
	}
	for (i = arg_8; i < arg_4; i++) {
		if (arg_0[i] != 0) {
			err = ERROR_INVALID_PARAMETER;
			goto Cleanup;
		}
	}
Cleanup:
	if (lpMem != NULL) {
		HeapFree(GetProcessHeap(), 0, lpMem);
	}
	if (var_4 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_4);
	}
	if (var_8 != NULL) {
		HeapFree(GetProcessHeap(), 0, var_8);
	}
	if (var_C != NULL) {
		HeapFree(GetProcessHeap(), 0, var_C);
	}
	return err;
}

DWORD sub_105C05A(LPCVOID lpKeySeed, DWORD dwKeySeed, LPVOID lpBuffer, DWORD CheckOffset, DWORD Size, BOOL arg_14) {
	DWORD err = ERROR_SUCCESS;
	if (lpKeySeed == NULL || dwKeySeed == 0) {
		return ERROR_INVALID_PARAMETER;
	}
	MD5_CTX md5ctx;
	MD5Init(&md5ctx);
	MD5Update(&md5ctx, (CONST BYTE*)lpKeySeed, dwKeySeed);
	MD5Final(&md5ctx);
	BYTE var_10[16];
	ZeroMemory(var_10, sizeof(var_10));
	memcpy(var_10, md5ctx.digest, 5);
	RC4_KEYSTRUCT rc4ctx;
	rc4_key(&rc4ctx, sizeof(var_10), var_10);
	rc4(&rc4ctx, Size, (BYTE*)lpBuffer);
	if (!arg_14) {
		for (DWORD i = CheckOffset; i < Size; i++) {
			if (((LPBYTE)lpBuffer)[i] != 0) {
				err = ERROR_INVALID_PARAMETER;
				break;
			}
		}
	}
	return err;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_8() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_8:
                mov     edx, 8
                retn
}
}
#endif
#pragma warning(pop)
