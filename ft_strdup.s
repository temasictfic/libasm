section .text
    global ft_strdup       ; char *strdup(const char *s)
    extern malloc          ; void *malloc(size_t size)
    extern ft_strlen       ; size_t strlen(const char *s)
    extern ft_strcpy       ; char *strcpy(char *dest, const char *src)

ft_strdup:
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
    

    ret                    ; Return pointer to new string
.error:
    xor     rax, rax       ; Return NULL
    ret