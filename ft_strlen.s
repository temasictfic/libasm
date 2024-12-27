section .text
    global ft_strlen        ; size_t strlen(const char *s)

ft_strlen:
    xor     rax, rax        ; Initialize counter to 0
.loop:
    cmp     byte [rdi + rax], 0  ; Compare current byte with null terminator
    je      .done           ; If equal (found null), jump to done
    inc     rax            ; Increment counter
    jmp     .loop          ; Continue loop
.done:
    ret                    ; Return counter in rax