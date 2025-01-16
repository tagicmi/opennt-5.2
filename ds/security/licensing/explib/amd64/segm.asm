.code

option prologue:none
option epilogue:none

Begin_Vspweb_Scp_Segment_1_2 proc
	mov rax, 1
BEGIN_SCP_SEGMENT_8_2_0_10_00_00:
	mov rbx, 2
	retn
Begin_Vspweb_Scp_Segment_1_2 endp

Begin_Vspweb_Scp_Segment_8_2 proc
	mov rax, 8
BEGIN_SCP_SEGMENT_8_2_0_10_00_00:
	mov rbx, 2
	retn
Begin_Vspweb_Scp_Segment_8_2 endp

End_Vspweb_Scp_Segment_1_2 proc
	mov rax, 1
END_SCP_SEGMENT_1_2:
	mov rbx, 2
	retn
End_Vspweb_Scp_Segment_1_2 endp

End_Vspweb_Scp_Segment_8_2 proc
	mov rcx, 8
END_SCP_SEGMENT_8_2:
	mov rdx, 2
	retn
End_Vspweb_Scp_Segment_8_2 endp

end
