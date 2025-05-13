section .data
    promptA0 db "Enter A0 (0 or 1): ", 0
    promptA1 db "Enter A1 (0 or 1): ", 0
    promptC db "Enter C (0 or 1): ", 0
    invalidInput db "Invalid input! Please enter only 0 or 1.", 0
    resultMsg db "Output X: ", 0

section .bss
    A0 resb 1
    A1 resb 1
    C resb 1
    X resb 1

section .text
    global _start

_start:
    ; Print "Enter A0 (0 or 1): "
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, promptA0       ; address of the string
    mov edx, 20             ; length of the string
    int 0x80                ; make syscall

    ; Read A0
    mov eax, 3              ; syscall number for sys_read
    mov ebx, 0              ; file descriptor 0 (stdin)
    mov ecx, A0             ; address to store the input
    mov edx, 1              ; read 1 byte
    int 0x80                ; make syscall

    ; Print "Enter A1 (0 or 1): "
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, promptA1       ; address of the string
    mov edx, 20             ; length of the string
    int 0x80                ; make syscall

    ; Read A1
    mov eax, 3              ; syscall number for sys_read
    mov ebx, 0              ; file descriptor 0 (stdin)
    mov ecx, A1             ; address to store the input
    mov edx, 1              ; read 1 byte
    int 0x80                ; make syscall

    ; Print "Enter C (0 or 1): "
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, promptC        ; address of the string
    mov edx, 20             ; length of the string
    int 0x80                ; make syscall

    ; Read C
    mov eax, 3              ; syscall number for sys_read
    mov ebx, 0              ; file descriptor 0 (stdin)
    mov ecx, C              ; address to store the input
    mov edx, 1              ; read 1 byte
    int 0x80                ; make syscall

    ; Convert inputs (A0, A1, C) from ASCII to integer (subtract 48)
    mov al, byte [A0]
    sub al, '0'
    mov [A0], al

    mov al, byte [A1]
    sub al, '0'
    mov [A1], al

    mov al, byte [C]
    sub al, '0'
    mov [C], al

    ; Check for valid input (0 or 1)
    mov al, [A0]
    cmp al, 0
    je validA0
    cmp al, 1
    je validA0
    jmp invalid_input

validA0:
    mov al, [A1]
    cmp al, 0
    je validA1
    cmp al, 1
    je validA1
    jmp invalid_input

validA1:
    mov al, [C]
    cmp al, 0
    je validC
    cmp al, 1
    je validC
    jmp invalid_input

validC:
    ; Compute the multiplexer output: X = (A0 & ~C) | (A1 & C)
    mov al, [A0]
    not al                   ; ~C (inverting C)
    and al, [C]              ; A0 & ~C
    mov bl, al

    mov al, [A1]
    and al, [C]              ; A1 & C
    or bl, al                ; (A0 & ~C) | (A1 & C)
    mov [X], bl

    ; Print result "Output X: "
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, resultMsg      ; address of the result message
    mov edx, 11             ; length of the string
    int 0x80                ; make syscall

    ; Print the result of X
    mov al, [X]
    add al, '0'             ; Convert integer to ASCII
    mov [X], al
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, X              ; address of the result
    mov edx, 1              ; length of the string
    int 0x80                ; make syscall

    ; Exit the program
    mov eax, 1              ; syscall number for sys_exit
    xor ebx, ebx            ; exit code 0
    int 0x80                ; make syscall

invalid_input:
    ; Print "Invalid input! Please enter only 0 or 1."
    mov eax, 4              ; syscall number for sys_write
    mov ebx, 1              ; file descriptor 1 (stdout)
    mov ecx, invalidInput   ; address of the invalid input message
    mov edx, 41             ; length of the string
