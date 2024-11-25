section .data
val255 dq 255.0

section .text
bits 64
default rel
global asmImgCvtGrayIntToDouble

asmImgCvtGrayIntToDouble:

    mov r11, rcx ; save w*h, input counter
    movsd xmm2, [val255] ; divisor
    
    L1:
    ; check if no more inputs
        cmp r11, 0
        jz end

    ; move value to SIMD register
        movzx rax, byte [rdx] ; zero extend uint8_t input
        cvtsi2sd xmm1, rax
        
    ; divide
        divsd xmm1, xmm2
        
    ; store answer
        movsd [r8], xmm1
        
    ; shift pointers
        inc rdx ; +1 since intImage input is only 1 byte
        add r8, 8 ; move to next element in floatImage
        dec r11
        jmp L1
        
    end: nop
    
    ret
