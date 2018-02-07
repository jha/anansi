[bits 64]
global anansi_context_capture
global anansi_context_restore

section .text

; http://www.sandpile.org/x86/gpr.htm
struc context
; Traditional GPRs */
.rax:   RESQ 1
.rcx:   RESQ 1
.rdx:   RESQ 1
.rbx:   RESQ 1
.rsp:   RESQ 1
.rbp:   RESQ 1
.rsi:   RESQ 1
; rdi has been omitted because according to unix ABI, arguments
; will be passed on registers. The context struc will clobber the
; previous value of rdi, so there is no point saving it

; Additional GPRs
.r8:    RESQ 1
.r9:    RESQ 1
.r10:   RESQ 1
.r11:   RESQ 1
.r12:   RESQ 1
.r13:   RESQ 1
.r14:   RESQ 1
.r15:   RESQ 1

; Instruction pointer
.rip:   RESQ 1

; TODO: Add SIMD registers too
endstruc

; context struc as arg0 (passed in rdi)
; If porting to another OS, this may need to be patched
anansi_context_capture:
    ; Store traditional GPRs
    mov     qword [rdi + context.rax], rax
    mov     qword [rdi + context.rcx], rcx
    mov     qword [rdi + context.rdx], rdx
    mov     qword [rdi + context.rbx], rbx
    mov     qword [rdi + context.rsp], rsp
    mov     qword [rdi + context.rbp], rbp
    mov     qword [rdi + context.rsi], rsi

    ; Store additional GPRs
    mov     qword [rdi + context.r8], r8
    mov     qword [rdi + context.r9], r9
    mov     qword [rdi + context.r10], r10
    mov     qword [rdi + context.r11], r11
    mov     qword [rdi + context.r12], r12
    mov     qword [rdi + context.r13], r13
    mov     qword [rdi + context.r14], r14
    mov     qword [rdi + context.r15], r15

    ; Capture the instruction pointer in the context of the caller
    ; Since we have no function epilogue, the return address should be
    ; at the top of the stack
    push    rax
    mov     rax, qword [rsp + 8]
    mov     qword [rdi + context.rip], rax
    pop     rax

    ret

; context struc as arg0 (passed in rdi)
; If porting to another OS, this may need to be patched
anansi_context_restore:
    ; Load traditional GPRs
    mov     rax, qword [rdi + context.rax]
    mov     rcx, qword [rdi + context.rcx]
    mov     rdx, qword [rdi + context.rdx]
    mov     rbx, qword [rdi + context.rbx]
    mov     rsp, qword [rdi + context.rsp]
    mov     rbp, qword [rdi + context.rbp]
    mov     rsi, qword [rdi + context.rsi]

    ; Load additional GPRs
    mov     r8, qword [rdi + context.r8]
    mov     r9, qword [rdi + context.r9]
    mov     r10, qword [rdi + context.r10]
    mov     r11, qword [rdi + context.r11]
    mov     r12, qword [rdi + context.r12]
    mov     r13, qword [rdi + context.r13]
    mov     r14, qword [rdi + context.r14]
    mov     r15, qword [rdi + context.r15]

    ret
