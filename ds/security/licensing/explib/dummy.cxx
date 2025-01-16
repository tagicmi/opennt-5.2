#include "precomp.h"
#pragma hdrstop
#include "../include/dummy.h"

void WPADummy() {
#ifdef _X86_
	__asm nop
#endif
}
