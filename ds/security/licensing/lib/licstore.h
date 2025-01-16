#pragma once

#define ERROR_TOO_MANY_RECORDS 81
#define ERROR_DUPLICATE_RECORD 82
#define ERROR_NO_RECORD 83
#define ERROR_BAD_RECORD 84
#define ERROR_BAD_DECRYPT 85
#define ERROR_BAD_ENCRYPT 86
#define ERROR_EMPTY_RECORD 594

#define ERROR_MACHINE_SEED_FAIL 337
#define ERROR_339 339
#define ERROR_340 340

#define ERROR_x502 0x502

// vmt@10190F4
class CWPALockable
{
public:
	HANDLE field_4;
	CWPALockable() : field_4(NULL) {
	}
	virtual HRESULT sub_1057D9E(LPCWSTR MutexName);
	virtual HRESULT sub_1055AFD(void);
	virtual ~CWPALockable() {
		if (field_4 != NULL) {
			CloseHandle(field_4);
			field_4 = NULL;
		}
	}
};

class CWPALockGuardBase {
public:
	bool field_0;
	LPCWSTR field_4;
	CWPALockable* field_8;
	CWPALockGuardBase(LPCWSTR szMutexName, CWPALockable* target)
		: field_0(false)
		, field_4(szMutexName)
		, field_8(target)
	{
	}
	bool sub_104360E() {
		if (field_0) {
			DebugBreak();
			return true;
		}
		if (FAILED(field_8->sub_1057D9E(field_4))) {
			return false;
		}
		field_0 = true;
		return true;
	}
	~CWPALockGuardBase() {
		if (field_0) {
			field_8->sub_1055AFD();
		}
		field_0 = false;
	}
};

class CWPALockGuard : public CWPALockGuardBase {
public:
	CWPALockGuard(LPCWSTR szMutexName, CWPALockable* target)
		: CWPALockGuardBase(szMutexName, target)
	{}
	~CWPALockGuard() {}
};

struct CWPAFileHeader;

// vmt@1019E00
class CWPALicenseStore : public CWPALockable
{
public:
    char FileName[MAX_PATH + 1];
    PVOID CryptoKeySeed;
    DWORD CryptoKeySeedSize;

    CWPALicenseStore(); // sub_1055DEA
    ~CWPALicenseStore(); // sub_1055EA4
    DWORD Clear();

    DWORD Init(LPCSTR lpFileName, LPVOID lpCryptoKeySeedPart, DWORD cbCryptoKeySeedPart, BOOL fCreateClean);
    DWORD AddRecord(DWORD Id, LPCVOID lpData, DWORD cbData, BOOL fEncrypt);
    DWORD GetRecord(DWORD Id, LPVOID* ppData, DWORD* pcbData);
    DWORD DeleteRecord(DWORD Id);
    DWORD ReplaceRecord(DWORD Id, LPCVOID lpData, DWORD cbData);

private:
    HANDLE sub_1055684(DWORD dwDesiredAccess);
    HANDLE sub_1055736();
    DWORD sub_10557E8(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LONG lDistanceToMove);
    DWORD sub_105590D(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LONG lDistanceToMove);
    ULONG sub_1055A36(const CWPAFileHeader* hdr, DWORD id);
    DWORD sub_1055F86(HANDLE hFile, CWPAFileHeader* lpData);
    DWORD sub_1056144(HANDLE hFile, const CWPAFileHeader* lpData);
    DWORD sub_10562CD();
};

DWORD CreateAndHoldWPAGlobalMutex();
