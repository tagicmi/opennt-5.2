#include "precomp.h"
#pragma hdrstop
#include <stddef.h>
#include "newcrypt.h"

void licstore_do_nothing();
void licstore_do_nothing2();

#include "licstore.h"
#include "licstoreacl.h"

//#include "licstore_eh.inc"

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_3() {
__asm {
                mov     eax, 3
BEGIN_SCP_SEGMENT_3_3_0_10_00_00:
                mov     ebx, 3
                retn
}
}
#endif
#pragma warning(pop)

// on-disk format of wpa.dbl
struct CWPAFileRecordHeader {
    DWORD Id;
    DWORD FileOffset;
    DWORD Size;
    BYTE Encrypted;
    BYTE EncryptionOverheadSize;
    BYTE Padding[2];
};

#define WPA_MAX_FILE_RECORDS 0x40
struct CWPAFileHeader {
    DWORD NumRecords;
    CWPAFileRecordHeader Records[WPA_MAX_FILE_RECORDS];
    WORD Ignored;
    WORD Check; // check for correct decryption, must be zero
};

CWPALicenseStore::CWPALicenseStore() {
#ifdef _X86_
    void Begin_Vspweb_Scp_Segment_3_3();
    void End_Vspweb_Scp_Segment_3_3();
    __asm cmp eax, offset Begin_Vspweb_Scp_Segment_3_3
    __asm cmp eax, offset End_Vspweb_Scp_Segment_3_3
#endif
#ifdef _x86
    extern "C" void Begin_Vspweb_Scp_Segment_3_3();
    extern "C" void End_Vspweb_Scp_Segment_3_3();
#endif
    ZeroMemory(FileName, sizeof(FileName));
    field_4 = NULL;
    CryptoKeySeed = NULL;
    CryptoKeySeedSize = 0;
    licstore_do_nothing();
}

CWPALicenseStore::~CWPALicenseStore() {
    if (CryptoKeySeed) {
        HeapFree(GetProcessHeap(), 0, CryptoKeySeed);
        CryptoKeySeed = NULL;
    }
    licstore_do_nothing();
}

DWORD CWPALicenseStore::Clear() {
    if (CryptoKeySeed) {
        HeapFree(GetProcessHeap(), 0, CryptoKeySeed);
        CryptoKeySeed = NULL;
    }
    ZeroMemory(FileName, sizeof(FileName));
    CryptoKeySeed = NULL;
    CryptoKeySeedSize = 0;
    return 0;
}

HANDLE CWPALicenseStore::sub_1055684(DWORD dwDesiredAccess) {
    return CreateFileA(
        FileName,
        dwDesiredAccess,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
        NULL);
}

HANDLE CWPALicenseStore::sub_1055736() {
    return CreateFileA(
        FileName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        TRUNCATE_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
        NULL);
}

DWORD CWPALicenseStore::sub_10557E8(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LONG lDistanceToMove) {
    DWORD NumberOfBytesRead = 0;
    DWORD status = 0;
    if (SetFilePointer(hFile, lDistanceToMove, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        status = GetLastError();
    } else if (!ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, &NumberOfBytesRead, NULL)) {
        status = GetLastError();
    }
    return status;
}

DWORD CWPALicenseStore::sub_105590D(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LONG lDistanceToMove) {
    DWORD NumberOfBytesWritten = 0;
    DWORD status = 0;
    if (SetFilePointer(hFile, lDistanceToMove, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        status = GetLastError();
    } else if (!WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, &NumberOfBytesWritten, NULL)) {
        status = GetLastError();
    }
    return status;
}

ULONG CWPALicenseStore::sub_1055A36(const CWPAFileHeader* hdr, DWORD id)
{
    DWORD numRecords = hdr->NumRecords;
    if (!numRecords) {
        return -1;
    }
    ULONG i;
    for (i = 0; i < numRecords; i++) {
        if (hdr->Records[i].Id == id) {
            break;
        }
    }
    if (i == numRecords) {
        return (ULONG)-1;
    }
    return i;
}

HRESULT CWPALockable::sub_1055AFD() {
    if (ReleaseMutex(field_4)) {
        return S_OK;
    } else {
        DWORD err = GetLastError();
        return HRESULT_FROM_WIN32(err);
    }
}

DWORD CreateAndHoldOneMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCSTR lpName) {
    HANDLE hMutex = NULL;
    DWORD err;
    if (!lpName || !lpMutexAttributes) {
        err = ERROR_INVALID_PARAMETER;
    } else {
        hMutex = CreateMutexA(lpMutexAttributes, FALSE, lpName);
        err = GetLastError();
        if (hMutex) {
            if (err == ERROR_SUCCESS) {
                hMutex = NULL;
            }
            if (err == ERROR_ALREADY_EXISTS) {
                err = ERROR_SUCCESS;
            }
        }
    }
    if (hMutex) {
        CloseHandle(hMutex);
    }
    return err;
}

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_3() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_3:
                mov     edx, 3
                retn
}
}
#endif
#pragma warning(pop)

// 1: ?nukeit@?$AutoHeapPtr@U_SECURITY_DESCRIPTOR@@@@EAEXXZ
// aka AutoHeapPtr<SECURITY_DESCRIPTOR>::nukeit()
// 2: ??_G?$AutoPtrBase@U_SECURITY_DESCRIPTOR@@@@UAEPAXI@Z
// aka AutoPtrBase<SECURITY_DESCRIPTOR>::`scalar deleting destructor'
// 3: ?take@?$AutoPtrBase@U_SECURITY_DESCRIPTOR@@@@QAEAAV1@PAU_SECURITY_DESCRIPTOR@@@Z
// aka AutoPtrBase<SECURITY_DESCRIPTOR>::take
// 4: ?nukeit@AutoSIDPtr@@EAEXXZ
// 5: ??_G?$AutoPtrBase@U_SID@@@@UAEPAXI@Z
// aka AutoPtrBase<_SID>::`scalar deleting destructor'
//#include "licstore1.inl"

DWORD CWPALicenseStore::sub_1055F86(HANDLE hFile, CWPAFileHeader* lpData) {
    licstore_do_nothing();
    DWORD err;
    CWPAFileHeader* Buffer = (CWPAFileHeader*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CWPAFileHeader));
    if (!Buffer) {
        err = ERROR_OUTOFMEMORY;
    } else {
        err = sub_10557E8(hFile, Buffer, sizeof(CWPAFileHeader), 0);
        if (err == ERROR_SUCCESS) {
            err = sub_105C05A(CryptoKeySeed, CryptoKeySeedSize, Buffer, offsetof(CWPAFileHeader, Check), sizeof(CWPAFileHeader), 0);
            if (err != ERROR_SUCCESS) {
                err = ERROR_BAD_DECRYPT;
            } else {
                *lpData = *Buffer;
            }
        }
        HeapFree(GetProcessHeap(), 0, Buffer);
    }
    return err;
}

DWORD CWPALicenseStore::sub_1056144(HANDLE hFile, const CWPAFileHeader* lpData) {
    licstore_do_nothing();
    DWORD err;
    CWPAFileHeader* Buffer = (CWPAFileHeader*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CWPAFileHeader));
    if (!Buffer) {
        err = ERROR_OUTOFMEMORY;
    } else {
        *Buffer = *lpData;
        err = sub_105C05A(CryptoKeySeed, CryptoKeySeedSize, Buffer, offsetof(CWPAFileHeader, Check), sizeof(CWPAFileHeader), 1);
        if (err != ERROR_SUCCESS) {
            err = ERROR_BAD_ENCRYPT;
        } else {
            err = sub_105590D(hFile, Buffer, sizeof(CWPAFileHeader), 0);
        }
        HeapFree(GetProcessHeap(), 0, Buffer);
    }
    return err;
}

DWORD CWPALicenseStore::sub_10562CD() {
    licstore_do_nothing();
    CWPALockGuard var_1C(L"Global\\WPA_LICSTORE_MUTEX", this);
    if (!var_1C.sub_104360E()) {
        return ERROR_INVALID_PARAMETER;
    }
    DWORD var_10 = 0;
    HANDLE edi = sub_1055684(GENERIC_READ);
    DWORD err;
    if (edi == INVALID_HANDLE_VALUE) {
        err = GetLastError();
        goto Cleanup;
    }
    CWPAFileHeader FileHeader;
    err = sub_1055F86(edi, &FileHeader);
    if (err != ERROR_SUCCESS) {
        goto Cleanup;
    }
    DWORD FileSize = GetFileSize(edi, NULL);
    if (FileSize == INVALID_FILE_SIZE) {
        err = GetLastError();
        goto Cleanup;
    }
    DWORD i;
    for (i = 0; i < FileHeader.NumRecords; i++) {
        var_10 += FileHeader.Records[i].Size + FileHeader.Records[i].EncryptionOverheadSize;
        if (FileHeader.Records[i].FileOffset >= FileSize ||
            FileHeader.Records[i].FileOffset < sizeof(CWPAFileHeader))
        {
            err = ERROR_BAD_RECORD;
            goto Cleanup;
        }
    }
    if (var_10 != FileSize - sizeof(CWPAFileHeader)) {
        err = ERROR_BAD_RECORD;
    }
Cleanup:
    if (edi != INVALID_HANDLE_VALUE) {
        CloseHandle(edi);
    }
    return err;
}

//#include "licstore2.inl"
// 1: ??1?$AutoHeapPtr@U_SECURITY_DESCRIPTOR@@@@UAE@XZ
// aka AutoHeapPtr<SECURITY_DESCRIPTOR>::<destructor>
// 2: ??_G?$AutoHeapPtr@U_SECURITY_DESCRIPTOR@@@@UAEPAXI@Z
// aka AutoHeapPtr<SECURITY_DESCRIPTOR>::`scalar deleting destructor'
// 3: ??1AutoSIDPtr@@UAE@XZ
// aka AutoSIDPtr::~AutoSIDPtr
// 4: ??_EAutoSIDPtr@@UAEPAXI@Z
// aka AutoSIDPtr::`scalar deleting destructor'
// 5: `scalar deleting destructor' for CWPALicenseStore

DWORD CWPALicenseStore::Init(LPCSTR lpFileName, LPVOID lpCryptoKeySeedPart, DWORD cbCryptoKeySeedPart, BOOL fCreateClean) {
    licstore_do_nothing2();
    CWPALockGuard var_18(L"Global\\WPA_LICSTORE_MUTEX", this);
    if (!var_18.sub_104360E()) {
        return ERROR_INVALID_PARAMETER;
    }
    DWORD err;
    if (!lpFileName || !lstrlenA(lpFileName) || (ULONG)lstrlenA(lpFileName) >= MAX_PATH + 1) {
        err = ERROR_INVALID_PARAMETER;
        goto Cleanup;
    }
    lstrcpyA(FileName, lpFileName);
    if (lpCryptoKeySeedPart && cbCryptoKeySeedPart) {
        CryptoKeySeedSize = cbCryptoKeySeedPart + 4;
        CryptoKeySeed = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, CryptoKeySeedSize);
        if (!CryptoKeySeed) {
            err = ERROR_OUTOFMEMORY;
            goto Cleanup;
        }
        memcpy(CryptoKeySeed, lpCryptoKeySeedPart, cbCryptoKeySeedPart);
        *(DWORD*)((BYTE*)CryptoKeySeed + cbCryptoKeySeedPart) = 0x6BDC5BB8;
    }
    if (fCreateClean) {
        HANDLE hFile = CreateFileA(
            lpFileName,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
            NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            err = GetLastError();
            goto Cleanup;
        }
        CWPAFileHeader FileHeader;
        ZeroMemory(&FileHeader, sizeof(FileHeader));
        err = sub_1056144(hFile, &FileHeader);
        CloseHandle(hFile);
        if (err == ERROR_SUCCESS) {
            err = SetLSFileAcl(lpFileName);
        }
    } else {
        err = sub_10562CD();
    }
Cleanup:
    if (err != ERROR_SUCCESS) {
        if (CryptoKeySeed) {
            HeapFree(GetProcessHeap(), 0, CryptoKeySeed);
            CryptoKeySeed = NULL;
            CryptoKeySeedSize = 0;
        }
        ZeroMemory(&FileName, sizeof(FileName));
    }
    return err;
}

DWORD CWPALicenseStore::AddRecord(DWORD Id, LPCVOID lpData, DWORD cbData, BOOL fEncrypt) {
    licstore_do_nothing2();
    CWPALockGuard var_28(L"Global\\WPA_LICSTORE_MUTEX", this);
    if (!var_28.sub_104360E()) {
        return ERROR_INVALID_PARAMETER;
    }
    if (!cbData) {
        return ERROR_EMPTY_RECORD;
    }
    LPCVOID var_14 = NULL;
    HANDLE hFile = sub_1055684(GENERIC_READ | GENERIC_WRITE);
    DWORD err;
    if (hFile == INVALID_HANDLE_VALUE) {
        err = GetLastError();
        goto Cleanup;
    }
    CWPAFileHeader var_434, var_83C;
    err = sub_1055F86(hFile, &var_434);
    if (err) {
        goto Cleanup;
    }
    var_83C = var_434;
    if (var_434.NumRecords == WPA_MAX_FILE_RECORDS) {
        err = ERROR_TOO_MANY_RECORDS;
        goto Cleanup;
    }
    if (sub_1055A36(&var_434, Id) != (ULONG)-1) {
        err = ERROR_DUPLICATE_RECORD;
        goto Cleanup;
    }
    DWORD NextRecordNum;
    DWORD NextFileOffset;
    if (var_434.NumRecords == 0) {
        NextRecordNum = 0;
        NextFileOffset = sizeof(CWPAFileHeader);
    } else {
        NextRecordNum = var_434.NumRecords;
        NextFileOffset = var_434.Records[var_434.NumRecords - 1].FileOffset;
        NextFileOffset += var_434.Records[var_434.NumRecords - 1].Size;
        NextFileOffset += var_434.Records[var_434.NumRecords - 1].EncryptionOverheadSize;
    }
    DWORD var_10;
    if (fEncrypt) {
        if (cbData & 1) {
            var_10 = cbData + 1;
        } else {
            var_10 = cbData + 2;
        }
        var_14 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, var_10);
        if (var_14 == NULL) {
            err = ERROR_OUTOFMEMORY;
            goto Cleanup;
        }
        memcpy((LPVOID)var_14, lpData, cbData);
        if (sub_105C05A(CryptoKeySeed, CryptoKeySeedSize, (LPVOID)var_14, cbData, var_10, TRUE)) {
            err = ERROR_BAD_ENCRYPT;
            goto Cleanup;
        }
    } else {
        var_14 = lpData;
        var_10 = cbData;
    }
    ++var_434.NumRecords;
    var_434.Records[NextRecordNum].Encrypted = (BYTE)fEncrypt;
    var_434.Records[NextRecordNum].Id = Id;
    var_434.Records[NextRecordNum].Size = cbData;
    var_434.Records[NextRecordNum].FileOffset = NextFileOffset;
    var_434.Records[NextRecordNum].EncryptionOverheadSize = (BYTE)(var_10 - cbData);
    err = sub_1056144(hFile, &var_434);
    if (err) {
        goto Cleanup;
    }
    err = sub_105590D(hFile, var_14, var_10, NextFileOffset);
    if (err) {
        sub_1056144(hFile, &var_83C);
    }
Cleanup:
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
    }
    if (fEncrypt && var_14) {
        HeapFree(GetProcessHeap(), 0, (LPVOID)var_14);
    }
    return err;
}

DWORD CWPALicenseStore::GetRecord(DWORD Id, LPVOID* ppData, DWORD* pcbData) {
	licstore_do_nothing2();
	CWPALockGuard var_24(L"Global\\WPA_LICSTORE_MUTEX", this);
	if (!var_24.sub_104360E()) {
		return ERROR_INVALID_PARAMETER;
	}
	LPVOID Buffer = 0;
	HANDLE hFile = sub_1055684(GENERIC_READ);
	DWORD err;
	if (hFile == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		goto Cleanup;
	}
	CWPAFileHeader FileHeader;
	err = sub_1055F86(hFile, &FileHeader);
	if (err) {
		goto Cleanup;
	}
	ULONG Index = sub_1055A36(&FileHeader, Id);
	if (Index == (ULONG)-1) {
		err = ERROR_NO_RECORD;
		goto Cleanup;
	}
	DWORD cbData = FileHeader.Records[Index].Size;
	DWORD cbFull = cbData + FileHeader.Records[Index].EncryptionOverheadSize;
	Buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbFull);
	if (Buffer == NULL) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	err = sub_10557E8(hFile, Buffer, cbFull, FileHeader.Records[Index].FileOffset);
	if (err) {
		goto Cleanup;
	}
	if (FileHeader.Records[Index].Encrypted) {
		err = sub_105C05A(CryptoKeySeed, CryptoKeySeedSize, Buffer, cbData, cbFull, FALSE);
		if (err) {
			err = ERROR_BAD_DECRYPT;
			goto Cleanup;
		}
		*ppData = Buffer;
		*pcbData = cbData;
	} else {
		*ppData = Buffer;
		*pcbData = cbFull;
	}
Cleanup:
	if (err && Buffer) {
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
	}
	return err;
}

DWORD CWPALicenseStore::DeleteRecord(DWORD Id) {
	licstore_do_nothing2();
	CWPALockGuard var_30(L"Global\\WPA_LICSTORE_MUTEX", this);
	if (!var_30.sub_104360E()) {
		return ERROR_INVALID_PARAMETER;
	}
	DWORD RecordSize = 0;
	LPVOID Buffer = NULL;
	HANDLE hFile = sub_1055684(GENERIC_READ);
	DWORD err;
	if (hFile == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		goto Cleanup;
	}
	CWPAFileHeader FileHeader;
	err = sub_1055F86(hFile, &FileHeader);
	if (err) {
		goto Cleanup;
	}
	ULONG Index = sub_1055A36(&FileHeader, Id);
	if (Index == (ULONG)-1) {
		err = ERROR_NO_RECORD;
		goto Cleanup;
	}
	BYTE EncryptionOverheadSize = FileHeader.Records[Index].EncryptionOverheadSize;
	DWORD FileOffset = FileHeader.Records[Index].FileOffset;
	RecordSize = FileHeader.Records[Index].Size;
	DWORD FileSize = GetFileSize(hFile, NULL);
	if (FileSize == INVALID_FILE_SIZE) {
		err = GetLastError();
		goto Cleanup;
	}
	DWORD DataSize = FileSize - sizeof(CWPAFileHeader);
	Buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, DataSize);
	if (!Buffer) {
		err = ERROR_OUTOFMEMORY;
		goto Cleanup;
	}
	err = sub_10557E8(hFile, Buffer, DataSize, sizeof(CWPAFileHeader));
	if (err) {
		goto Cleanup;
	}
	for (ULONG i = Index + 1; i < FileHeader.NumRecords; i++) {
		memcpy(&FileHeader.Records[i - 1], &FileHeader.Records[i], sizeof(CWPAFileRecordHeader));
		FileHeader.Records[i - 1].FileOffset -= RecordSize + EncryptionOverheadSize;
	}
	--FileHeader.NumRecords;
	FileHeader.Records[FileHeader.NumRecords].Encrypted = 0;
	FileHeader.Records[FileHeader.NumRecords].Id = 0;
	FileHeader.Records[FileHeader.NumRecords].Size = 0;
	FileHeader.Records[FileHeader.NumRecords].FileOffset = 0;
	FileHeader.Records[FileHeader.NumRecords].EncryptionOverheadSize = 0;
	CloseHandle(hFile);
	hFile = sub_1055736();
	if (hFile == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		goto Cleanup;
	}
	err = sub_1056144(hFile, &FileHeader);
	if (err) {
		goto Cleanup;
	}
	DWORD dwNotMovedSize = FileOffset - sizeof(CWPAFileHeader);
	err = sub_105590D(hFile, Buffer, dwNotMovedSize, sizeof(CWPAFileHeader));
	if (err) {
		goto Cleanup;
	}
	err = sub_105590D(
		hFile,
		(LPBYTE)Buffer + dwNotMovedSize + RecordSize + EncryptionOverheadSize,
		DataSize - (dwNotMovedSize + RecordSize + EncryptionOverheadSize),
		FileOffset);
Cleanup:
	if (Buffer) {
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
	}
	return err;
}

bool sub_10574CF(SID** pAdminSID, SID** pPowerUserSID, SID** pLocalSystemSID) {
	bool Success = false;
	AutoSIDPtr AdminSID, PowerUserSID, LocalSystemSID;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, (PSID*)&AdminSID)
		&& AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_POWER_USERS, 0, 0, 0, 0, 0, 0, (PSID*)&PowerUserSID)
		&& AllocateAndInitializeSid(&NtAuthority, 1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, (PSID*)&LocalSystemSID))
	{
		*pAdminSID = AdminSID._disownptr();
		*pPowerUserSID = PowerUserSID._disownptr();
		*pLocalSystemSID = LocalSystemSID._disownptr();
		Success = true;
	}
	return Success;
}

SECURITY_DESCRIPTOR* sub_10577AD() {
	AutoSIDPtr LocalSystemSID, AdminSID, PowerUserSID;
	//PSID Result = NULL;
	if (!sub_10574CF(&AdminSID, &PowerUserSID, &LocalSystemSID)) {
		return NULL;
	}
	AutoHeapPtr<SECURITY_DESCRIPTOR> SecurityDescriptor;
	DWORD nAclLength = sizeof(ACL) + 3 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD))
		+ GetLengthSid(AdminSID) + GetLengthSid(PowerUserSID) + GetLengthSid(LocalSystemSID);
	SecurityDescriptor = (SECURITY_DESCRIPTOR*)HeapAlloc(GetProcessHeap(), 0, nAclLength + sizeof(SECURITY_DESCRIPTOR));
	if (!SecurityDescriptor) {
		return NULL;
	}
	ACL* Acl = (ACL*)(SecurityDescriptor + 1);
	if (!InitializeAcl(Acl, nAclLength, ACL_REVISION)) {
		return NULL;
	}
	if (!AddAccessAllowedAce(Acl, ACL_REVISION, GENERIC_ALL, LocalSystemSID)) {
		return NULL;
	}
	if (!AddAccessAllowedAce(Acl, ACL_REVISION, GENERIC_ALL, PowerUserSID)) {
		return NULL;
	}
	if (!AddAccessAllowedAce(Acl, ACL_REVISION, GENERIC_ALL, AdminSID)) {
		return NULL;
	}
	if (!InitializeSecurityDescriptor(SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION)) {
		return NULL;
	}
	if (!SetSecurityDescriptorDacl(SecurityDescriptor, TRUE, Acl, FALSE)) {
		return NULL;
	}
	return SecurityDescriptor._disownptr();
}

HANDLE sub_1057BFD(BOOL bInitialOwner, LPCWSTR lpName) {
	HANDLE hMutex = OpenMutexW(SYNCHRONIZE, FALSE, lpName);
	if (!hMutex) {
		AutoHeapPtr<SECURITY_DESCRIPTOR> SecurityDescriptor(sub_10577AD());
		if (SecurityDescriptor) {
			SECURITY_ATTRIBUTES Attrs;
			Attrs.nLength = sizeof(Attrs);
			Attrs.lpSecurityDescriptor = SecurityDescriptor;
			Attrs.bInheritHandle = FALSE;
			hMutex = CreateMutexW(&Attrs, bInitialOwner, lpName);
		}
	}
	return hMutex;
}

HRESULT CWPALockable::sub_1057D9E(LPCWSTR lpName) {
	if (!field_4) {
		field_4 = sub_1057BFD(FALSE, lpName);
	}
	if (!field_4) {
		return HRESULT_FROM_WIN32(ERROR_NO_SYSTEM_RESOURCES);
	}
	DWORD status = WaitForSingleObject(field_4, 600000);
	if (status != WAIT_OBJECT_0) {
		if (status != WAIT_ABANDONED) {
			if (status != WAIT_TIMEOUT) {
				if (status != WAIT_FAILED) {
					return HRESULT_FROM_WIN32(ERROR_INVALID_FUNCTION);
				} else {
					DWORD err = GetLastError();
					return HRESULT_FROM_WIN32(err);
				}
			} else {
				return HRESULT_FROM_WIN32(ERROR_SEM_TIMEOUT);
			}
		} else {
			status = WaitForSingleObject(field_4, 600000);
			if (status == WAIT_OBJECT_0) {
				return ERROR_SUCCESS;
			} else {
				return E_UNEXPECTED;
			}
		}
	} else {
		return WAIT_OBJECT_0;
	}
}

DWORD CreateAndHoldWPAGlobalMutex() {
	DWORD err;
	AutoHeapPtr<SECURITY_DESCRIPTOR> SecurityDescriptor(sub_10577AD());
	if (!SecurityDescriptor) {
		err = GetLastError();
		goto Cleanup;
	}
	SECURITY_ATTRIBUTES Attrs;
	Attrs.nLength = sizeof(Attrs);
	Attrs.lpSecurityDescriptor = SecurityDescriptor;
	Attrs.bInheritHandle = FALSE;
	err = CreateAndHoldOneMutex(&Attrs, "Global\\WPA_PR_MUTEX");
	if (err) {
		goto Cleanup;
	}
	err = CreateAndHoldOneMutex(&Attrs, "Global\\WPA_RT_MUTEX");
	if (err) {
		goto Cleanup;
	}
	err = CreateAndHoldOneMutex(&Attrs, "Global\\WPA_LT_MUTEX");
	if (err) {
		goto Cleanup;
	}
	err = CreateAndHoldOneMutex(&Attrs, "Global\\WPA_HWID_MUTEX");
	if (err) {
		goto Cleanup;
	}
	err = CreateAndHoldOneMutex(&Attrs, "Global\\WPA_LICSTORE_MUTEX");
Cleanup:
	return err;
}

DWORD CWPALicenseStore::ReplaceRecord(DWORD Id, LPCVOID lpData, DWORD cbData) {
	CWPALockGuard var_24(L"Global\\WPA_LICSTORE_MUTEX", this);
	if (!var_24.sub_104360E()) {
		return ERROR_INVALID_PARAMETER;
	}
	DWORD fEncrypt = 0;
	LPVOID Buffer = NULL;
	HANDLE hFile = sub_1055684(GENERIC_READ | GENERIC_WRITE);
	DWORD err;
	if (hFile == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		goto Cleanup;
	}
	CWPAFileHeader FileHeader;
	err = sub_1055F86(hFile, &FileHeader);
	if (err) {
		goto Cleanup;
	}
	ULONG Index = sub_1055A36(&FileHeader, Id);
	if (Index == (UINT)-1) {
		err = ERROR_NO_RECORD;
		goto Cleanup;
	}
	DWORD ecx = FileHeader.Records[Index].Size;
	DWORD var_28 = FileHeader.Records[Index].FileOffset;
	fEncrypt = FileHeader.Records[Index].Encrypted;
	if (ecx == cbData) {
		DWORD cbFull;
		if (fEncrypt) {
			if (cbData & 1) {
				cbFull = cbData + 1;
			} else {
				cbFull = cbData + 2;
			}
			Buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbFull);
			if (!Buffer) {
				err = ERROR_OUTOFMEMORY;
				goto Cleanup;
			}
			memcpy(Buffer, lpData, cbData);
			err = sub_105C05A(CryptoKeySeed, CryptoKeySeedSize, Buffer, cbData, cbFull, TRUE);
			if (err) {
				goto Cleanup;
			}
		} else {
			Buffer = (LPVOID)lpData;
			cbFull = cbData;
		}
		err = sub_105590D(hFile, Buffer, cbFull, var_28);
	} else {
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
		err = DeleteRecord(Id);
		if (err) {
			goto Cleanup;
		}
		err = AddRecord(Id, lpData, cbData, fEncrypt);
	}
Cleanup:
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
	}
	if (fEncrypt && Buffer) {
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
	return err;
}

void licstore_do_nothing2() { licstore_do_nothing(); }
void licstore_do_nothing() {}
