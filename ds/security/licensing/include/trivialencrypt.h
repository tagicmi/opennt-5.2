#pragma once
void __forceinline WPAEncrypt(LPBYTE lpData, DWORD cbData, const BYTE dkey[16]) {
	for (DWORD x = 0; x + 8 <= cbData; x++) {
		LPBYTE ecx = lpData + x;
		DWORD v0 = *(DWORD*)ecx;
		DWORD v1 = *(DWORD*)(ecx + 4);
		DWORD sum = 0;
		DWORD delta = 0;
#ifdef _X86_
		__asm mov eax, 0x60B920F7
		__asm add eax, 0x3D7E58C2
		__asm mov delta, eax
#else
		DWORD n1 = 0x60B920F7, n2 = 0x3D7E58C2;
		delta = n1 + n2;
#endif
		for (DWORD i = 0; i < 0x20; i++) {
			v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ((DWORD*)dkey)[sum & 3]);
			sum += delta;
			v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ((DWORD*)dkey)[(sum >> 11) & 3]);
		}
		*(DWORD*)ecx = v0;
		*(DWORD*)(ecx + 4) = v1;
	}
}
DWORD __forceinline WPAGetXTEASum() {
	volatile DWORD result = 0;
	result += 0x77CF6050;
	result += 0x4F1FD6D0;
	return result;
}
DWORD __forceinline WPAGetXTEADelta2() {
	volatile DWORD result = 0;
	result += 0x60B920F7;
	result += 0x3D7E58C2;
	return result;
}
void __forceinline WPADecipher64(const DWORD* v, DWORD* w, const DWORD* k) {
	DWORD v0 = v[0],
		v1 = v[1],
		sum = WPAGetXTEASum(),
		delta = WPAGetXTEADelta2();
	for (DWORD i = 0; i < 32; i++) {
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
	}
	w[0] = v0;
	w[1] = v1;
}
void __forceinline WPADecrypt(PBYTE pBytes, DWORD cbBytes, const BYTE dkey[16]) {
	for (LONG var_C = cbBytes - 8; var_C >= 0; --var_C) {
		WPADecipher64((PDWORD)(pBytes + var_C), (PDWORD)(pBytes + var_C), (PDWORD)dkey);
	}
}

class CWPAStringsDecryptor {
private:
    const WORD* encrypted;
    size_t size;
    const BYTE* key;
    WCHAR decrypted[MAX_PATH];
public:
    operator LPCWSTR() const {
        return decrypted;
    }
    CWPAStringsDecryptor(const WORD* encrypted_, size_t size_, const BYTE* key_);
    ~CWPAStringsDecryptor();
};

extern const DWORD dword_1019368[256];
static DWORD __forceinline CalcCRC(const BYTE* lpData, LONG cbData)
{
	DWORD CRC = ~0;
	const BYTE* ptr = lpData;
	if (cbData > 0) {
		for (LONG i = 0; i < cbData; i++, ptr++) {
			CRC = (CRC << 8) ^ dword_1019368[(CRC >> 24) ^ *ptr];
		}
	}
	return ~CRC;
}

inline CWPAStringsDecryptor::CWPAStringsDecryptor(const WORD* encrypted_, size_t size_, const BYTE* key_)
{
	encrypted = encrypted_;
	key = key_;
	size = size_;
	ZeroMemory(decrypted, sizeof(decrypted));
	DWORD ExpectedCRC = *((DWORD*)(encrypted + size) - 1);
	DWORD CRC = CalcCRC((const BYTE*)encrypted_, size_ * sizeof(WCHAR) - sizeof(DWORD));
	if (CRC != ExpectedCRC || size_ >= MAX_PATH) {
		return;
	}
	memcpy(decrypted, encrypted_, size_ * sizeof(WCHAR));
	WPADecrypt((LPBYTE)decrypted, size * sizeof(WCHAR) - sizeof(DWORD), key);
	decrypted[size_] = 0;
}

inline CWPAStringsDecryptor::~CWPAStringsDecryptor() {
	WPAEncrypt((LPBYTE)decrypted, size * sizeof(WCHAR) - sizeof(DWORD), key);
}

// some keys for WPAEncrypt/WPADecrypt
extern const BYTE dword_1019778[16];
extern const BYTE unk_1019768[16];
extern HRESULT GetPerMachine128BitSeed(BYTE arg_0[16]);
