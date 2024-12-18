section .text
    global ft_strcpy        ; char *strcpy(char *dest, const char *src)

ft_strcpy:
    push    rbp            ; Save base pointer
    mov     rbp, rsp       ; Set up stack frame
    mov     rax, rdi       ; Save destination pointer (will be our return value)
.loop:
    mov     cl, byte [rsi] ; Get byte from source
    mov     byte [rdi], cl ; Copy byte to destination
    test    cl, cl         ; Check if we just copied null terminator
    jz      .done          ; If yes, we're done
    inc     rsi            ; Move to next source byte
    inc     rdi            ; Move to next destination byte
    jmp     .loop          ; Continue copying
.done:
    mov     rsp, rbp       ; Restore stack
    pop     rbp
    ret                    ; Return original destination pointer (in rax)