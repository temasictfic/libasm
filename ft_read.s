section .text
    global ft_read         ; ssize_t read(int fd, void *buf, size_t count)
    extern __errno_location
    
ft_read:
    mov     rax, 0         ; syscall number for read
    syscall                ; Execute syscall
    cmp     rax, 0         ; Check for error
    jl      .error         ; If negative, handle error
    ret                    ; Return number of bytes read
.error:
    neg     rax            ; Get positive error code
    push    rax            ; Save error code
    call    __errno_location WRT ..plt  ; Get errno address
    pop     qword [rax]    ; Set errno
    mov     rax, -1        ; Return -1 to indicate error
    ret