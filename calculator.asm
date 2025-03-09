section .data
    prompt db "Select operation (1: Add, 2: Subtract, 3: Multiply, 4: Divide, 5: Modulus): ", 0
    num1_prompt db "Enter first number: ", 0
    num2_prompt db "Enter second number: ", 0
    result_prompt db "Result: ", 0
    div_error_msg db "Error: Division by zero", 10, 0
    format_specifier_input db "%d", 0
    format_specifier_output db "%d", 10, 0

section .bss
    choice resd 1
    num1 resd 1
    num2 resd 1
    result resd 1

section .text
    global main
    extern printf, scanf

main:
    ; Set up stack frame
    push rbp
    mov rbp, rsp

    ; Display prompt
    mov rdi, prompt
    xor rax, rax
    call printf

    ; Get choice
    mov rdi, format_specifier_input
    mov rsi, choice
    xor rax, rax
    call scanf

    ; Get first number
    mov rdi, num1_prompt
    xor rax, rax
    call printf
    
    mov rdi, format_specifier_input
    mov rsi, num1
    xor rax, rax
    call scanf

    ; Get second number
    mov rdi, num2_prompt
    xor rax, rax
    call printf
    
    mov rdi, format_specifier_input
    mov rsi, num2
    xor rax, rax
    call scanf

    ; Perform operation
    mov eax, [choice]
    cmp eax, 1
    je add_op
    cmp eax, 2
    je sub_op
    cmp eax, 3
    je mul_op
    cmp eax, 4
    je div_op
    cmp eax, 5
    je mod_op
    jmp exit

add_op:
    mov eax, [num1]
    add eax, [num2]
    mov [result], eax
    jmp print_result

sub_op:
    mov eax, [num1]
    sub eax, [num2]
    mov [result], eax
    jmp print_result

mul_op:
    mov eax, [num1]
    imul eax, dword [num2]
    mov [result], eax
    jmp print_result

div_op:
    mov eax, [num2]
    test eax, eax
    jz div_zero_error
    
    mov eax, [num1]
    cdq
    idiv dword [num2]
    mov [result], eax
    jmp print_result

mod_op:
    mov eax, [num2]
    test eax, eax
    jz div_zero_error
    
    mov eax, [num1]
    cdq
    idiv dword [num2]
    mov [result], edx
    jmp print_result

div_zero_error:
    mov rdi, div_error_msg
    xor rax, rax
    call printf
    jmp exit

print_result:
    mov rdi, result_prompt
    xor rax, rax
    call printf
    
    mov rdi, format_specifier_output
    mov rsi, [result]
    xor rax, rax
    call printf

exit:
    mov rsp, rbp
    pop rbp
    xor rax, rax
    ret