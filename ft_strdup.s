section .text
    global ft_strdup       ; char *strdup(const char *s)
    extern malloc
    extern ft_strlen
    extern ft_strcpy

ft_strdup:
    push    rbp            ; Set up stack frame
    mov     rbp, rsp
    push    rdi            ; Save source string pointer
    
    call    ft_strlen      ; Get length of string
    inc     rax            ; Add 1 for null terminator
    
    mov     rdi, rax       ; Set malloc argument to length + 1
    call    malloc WRT ..plt ; Allocate memory
    test    rax, rax       ; Check if malloc failed
    jz      .error         ; If zero, malloc failed
    
    mov     rdi, rax       ; Set destination for strcpy
    pop     rsi            ; Restore source string as second argument
    call    ft_strcpy      ; Copy string
    
    mov     rsp, rbp       ; Clean up stack frame
    pop     rbp
    ret                    ; Return pointer to new string
.error:
    mov     rsp, rbp       ; Clean up stack frame
    pop     rbp
    xor     rax, rax       ; Return NULL
    ret