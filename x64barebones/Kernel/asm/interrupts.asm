GLOBAL _cli
GLOBAL _sti
GLOBAL pic_master_mask
GLOBAL pic_slave_mask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00_handler
GLOBAL _irq01_handler
GLOBAL _exception0_handler
GLOBAL _exception6_handler
GLOBAL _exception13_handler
GLOBAL _syscall_handler

EXTERN irq_dispatcher
EXTERN exception_dispatcher
EXTERN syscall_dispacher

%macro push_all 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro pop_all 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irq_handler_master 1
	push_all

	mov rdi, %1 				; pasaje de parametro
	call irq_dispatcher

								; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	pop_all
	iretq
%endmacro

%macro exception_handler 1
	push_all

	mov rdi, %1 				; pasaje de parametro
	call exception_dispatcher
	pop_all
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

pic_master_mask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

pic_slave_mask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  			; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn



_irq00_handler:					;8254 Timer (Timer Tick)
	irq_handler_master 0

_irq01_handler:					;Teclado
	irq_handler_master 1

								;Zero Division Exception
_exception0_handler:
	exception_handler 0

_exception6_handler:
	exception_handler 6

_exception13_handler:
	exception_handler 13

_syscall_handler:
	call syscall_dispacher
	iretq
