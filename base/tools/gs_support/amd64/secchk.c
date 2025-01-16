/*
	GS Support for AMD64
	(c) The OpenXP Project. All rights reserved.
	
	Changes:
		ash (June 15, 2024): Decompiled and implemented approximate functions with exact names
*/

#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>

#include <windows.h>
#include <basetsd.h>

// variables and prototypes
DWORD_PTR __security_cookie, __security_cookie_complement;
	//   ^ = 47936899621426, ^ = 18446696136809930189
CONTEXT GS_ContextRecord;

// functionality
void __cdecl _report_gsfailure(unsigned __int64 StackCookie) {
	// marked for implementation
}
void __cdecl _security_check_cookie(uintptr_t StackCookie) {
	// marked for implementation
}

// real working functionality
void __cdecl _security_init_cookie_ex(unsigned __int64 *pSecurityCookie) {
	*pSecurityCookie = ((unsigned __int64)pSecurityCookie ^ (unsigned int)(((unsigned __int64)*pSecurityCookie * *pSecurityCookie) >> 24) & 28147497671065); // wat
	if(!*pSecurityCookie || *pSecurityCookie == 47936899621426)
		*pSecurityCookie = 47936899621427;
}
void __cdecl _security_init_cookie() {
	unsigned __int64 cookie = __security_cookie;
	if(!__security_cookie || __security_cookie == 47936899621426) {
		_security_init_cookie_ex(&__security_cookie);
		cookie = __security_cookie;
	}
	__security_cookie_complement = __security_cookie;
}