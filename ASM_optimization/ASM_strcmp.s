;: 0-Linux-nasm-64.s  
;:================================================
;: ASM_strcmp.s                   (c)ALXnd,2025
;:================================================


;----------------------------------------- CODE ---------------------------------------------------------------------------------

section .text

global ASM_strcmp


;global _start
;
;_start:     
;            mov rdi, string1
;            mov rsi, string2
;            call ASM_strcmp
;
;            mov rax, 0x3C       ; exit64 (rdi)
;            xor rdi, rdi        ; exit_code ( always 0 :) )
;            syscall




;==========================================================
; ASM_strcmp (const char* string1, const char* string2)
;--------------------------
; INFO:
;   Compare 2 strings.
;--------------------------
; ENTRY:
;   rsi - arg 2
;   rdi - arg 1
;--------------------------
; ENTER: NONE
;--------------------------
; DESTR:
;   eax - возвращаемое значение
;==========================================================
ASM_strcmp:
            push rbx

            Cycle:

            mov al, [rdi]
            mov bl, [rsi]

            cmp al, 0
            je End_cycle
            
            cmp al, bl
            jne End_cycle

            inc rdi
            inc rsi
            jmp Cycle


            End_cycle:

            movsx eax, al
            movsx ebx, bl

            sub eax, ebx

            pop rbx
            
            ret


;section .data

;string1: db "AB", 0
;string2: db "AC", 0