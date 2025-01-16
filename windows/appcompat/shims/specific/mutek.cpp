/*++

 Copyright (c) 2002 Microsoft Corporation

 Module Name:

    Mutek.cpp

 Abstract:

    App passes NumberOfBytesRead as inside the block of memory they're reading.

 Notes:

    This is an app specific shim.

 History:

    05/23/2002 linstev   Created

--*/

#include "precomp.h"
#include "strsafe.h"

IMPLEMENT_SHIM_BEGIN(Mutek)
#include "ShimHookMacro.h"

APIHOOK_ENUM_BEGIN
    APIHOOK_ENUM_ENTRY(ReadProcessMemory) 
APIHOOK_ENUM_END

/*++

 Buffer parameters so they don't get overwritten.

--*/

BOOL
APIHOOK(ReadProcessMemory)(
    HANDLE hProcess,              
    LPCVOID lpBaseAddress,        
    LPVOID lpBuffer,              
    DWORD nSize,                 
    LPDWORD lpNumberOfBytesRead   
    )
{
	#if defined(_X86_)
    __asm nop;
	#endif

    BOOL bRet = ORIGINAL_API(ReadProcessMemory)(hProcess, lpBaseAddress, lpBuffer, 
        nSize, lpNumberOfBytesRead);

	#if defined(_X86_)
    __asm nop;
	#endif

    return bRet;
}

/*++

 Register hooked functions

--*/

HOOK_BEGIN
    APIHOOK_ENTRY(KERNEL32.DLL, ReadProcessMemory)
HOOK_END

IMPLEMENT_SHIM_END

