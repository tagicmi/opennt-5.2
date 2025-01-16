.486
.model flat, C

option prologue:none
option epilogue:none

.code

Begin_Vspweb_Scp_Segment_1_2 proc
	mov eax, 1
BEGIN_SCP_SEGMENT_8_2_0_10_00_00:
	mov ebx, 2
	retn
Begin_Vspweb_Scp_Segment_1_2 endp

Begin_Vspweb_Scp_Segment_8_2 proc
	mov eax, 8
BEGIN_SCP_SEGMENT_8_2_0_10_00_00:
	mov ebx, 2
	retn
Begin_Vspweb_Scp_Segment_8_2 endp

End_Vspweb_Scp_Segment_1_2 proc
	mov eax, 1
END_SCP_SEGMENT_1_2:
	mov ebx, 2
	retn
End_Vspweb_Scp_Segment_1_2 endp

End_Vspweb_Scp_Segment_8_2 proc
	mov ecx, 8
END_SCP_SEGMENT_8_2:
	mov edx, 2
	retn
End_Vspweb_Scp_Segment_8_2 endp

end
