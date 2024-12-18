section .text
    global ft_strcmp       ; int strcmp(const char *s1, const char *s2)

ft_strcmp:
    xor     rax, rax       ; Clear return register
    xor     rcx, rcx       ; Clear temp register
.loop:
    mov     al, byte [rdi] ; Load byte from first string
    mov     cl, byte [rsi] ; Load byte from second string
    sub     rax, rcx       ; Calculate difference
    jnz     .done          ; If difference not zero, we're done
    cmp     cl, 0          ; Check if we hit null terminator
    je      .done          ; If yes, strings are equal (rax is 0)
    inc     rdi            ; Move to next byte in first string
    inc     rsi            ; Move to next byte in second string
    jmp     .loop
.done:
    ret                    ; Return difference in rax