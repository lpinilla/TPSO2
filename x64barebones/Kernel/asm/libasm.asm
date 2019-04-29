GLOBAL cpuVendor

EXTERN push_all
EXTERN pop_all
EXTERN switch_process

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

context_switch:
	push_all
	mov rax, rsp
	call switch_process
	mov rsp, rax
	pop_all