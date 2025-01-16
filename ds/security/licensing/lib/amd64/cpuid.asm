.code

WPAHasCPUID:
    push rbp
    mov rbp, rsp ; init
    mov BYTE PTR [rbp-1], 0 ; cpuidFlag = 0
    pushfq
	pop rax
	mov rbx, rax
	xor rax, 200000h
	push rax
	popfq
	pushfq
	pop rax
	push rbx
	popfq
	xor rax, rbx
	mov BYTE PTR [rbp-1], al
    movzx eax, BYTE PTR [rbp-1] ; cpuidFlag = 0
    test eax, eax ; if
    je L2 ; != 0
    mov eax, 1 ; true (to return)
    jmp L3 ; true (to return)
L2:
    movzx eax, BYTE PTR [rbp-1] ; cpuidFlag
L3:
    pop rbp
	ret

GetCPUID:
	xor     eax, eax
	xor     ebx, ebx
	xor     ecx, ecx
	xor     edx, edx
	cpuid
	mov edi, ebx
	mov	esi, edx
	mov	edx, ecx

GetCPUIDModel:
	mov     eax, 1
	xor     ebx, ebx
	xor     ecx, ecx
	xor     edx, edx
	cpuid
	mov     edi, eax
	mov     esi, edx

GetCPUIDStepping:
	mov     eax, 3
	xor     ebx, ebx
	xor     ecx, ecx
	xor     edx, edx
	cpuid
	mov     edi, ecx
	mov     esi, edx
end