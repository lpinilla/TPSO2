GLOBAL _spin_lock
GLOBAL _spin_unlock

section .text

_spin_lock:
    mov rax, 1

    xchg rax, [rdi]

    test rax, rax

    jnz _spin_lock

    ret

_spin_unlock:
    mov rax, 0

    xchg rax, [rdi]

    ret