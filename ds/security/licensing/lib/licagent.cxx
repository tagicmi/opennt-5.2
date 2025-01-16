#include "precomp.h"
#pragma hdrstop

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
	extern "C" void __declspec() Begin_Vspweb_Scp_Segment_3_6();
#endif
#ifdef _X86_
void __declspec(naked) Begin_Vspweb_Scp_Segment_3_6() {
__asm {
                mov     eax, 3
BEGIN_SCP_SEGMENT_3_6_0_10_00_00:
                mov     ebx, 6
                retn
}
}
#endif
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable:4102) // unreferenced label
#ifdef _x64
	extern "C" void __declspec() End_Vspweb_Scp_Segment_3_6();
#endif
#ifdef _X86_
void __declspec(naked) End_Vspweb_Scp_Segment_3_6() {
__asm {
                mov     ecx, 3
END_SCP_SEGMENT_3_6:
                mov     edx, 6
                retn
}
}
#endif
#pragma warning(pop)
