#include <windows.h>
#include <crypto/sha.h>
#include "sigpriv.h"

WPA_SHORTSIG_STATUS ShortSigHash(CONST BYTE* Mbyte, DWORD nbytes, CONST DWORD* Mdword, DWORD ndwords, LPDWORD hashval, DWORD nbitout) {
	DWORD esi = (nbitout + 31) / 32;
	BYTE buf[20];
	DWORD i;
	DWORD j;
	A_SHA_CTX vcontext;
	ZeroMemory(&vcontext, sizeof(vcontext));
	A_SHAInit(&vcontext);
	A_SHAUpdate(&vcontext, (BYTE*)Mbyte, nbytes);
	j = 0;
	for (i = 0; i != ndwords; i++) {
		DWORD x = Mdword[i];
		buf[j] = (BYTE)x;
		buf[j+1] = (BYTE)(x >> 8);
		buf[j+2] = (BYTE)(x >> 16);
		buf[j+3] = (BYTE)(x >> 24);
		j += 4;
		if (j > sizeof(buf) - 4 || i == ndwords - 1) {
			A_SHAUpdate(&vcontext, buf, j);
			j = 0;
		}
	}
	A_SHAFinal(&vcontext, buf);
	if (esi * 4 <= sizeof(buf)) {
		for (i = 0; i != esi; i++) {
			hashval[i] = buf[i*4] + (buf[i*4+1] << 8) + (buf[i*4+2] << 16) + (buf[i*4+3] << 24);
		}
		hashval[esi-1] >>= (esi * 32 - nbitout);
		return SHORTSIG_SUCCESS;
	} else {
		return SHORTSIG_BAD_LENGTH;
	}
}
