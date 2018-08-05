;;===============================
;; Name: Jake Vollkommer
;;===============================
;; Write a program that divides two non-negative numbers A and B.

.orig x3000

;; CODE GOES HERE! :D
        AND R0,R0,#0
        ;ADD R0,R0,#-1   ;QUOTIENT = 0
        AND R1,R1,#0     ;REMAINDER = 0
        LD R2, A
        LD R3, B
        AND R7,R3,#-1
BRz   FAIL               ;Branch to FAIL if B = 0
        AND R1,R1,#0
        ADD R1,R1,R2     ;REMAINDER = A
        NOT R3,R3
        ADD R3,R3,#1     ;2's complement of B
        ADD R5,R2,R3     ;A - B
BRn   OUTPUT
LOOP    ADD R0,R0,#1     ;QUOTIENT++
        AND R1,R1,#0
        ADD R1,R1,R2     ;REMAINDER = A
        ADD R2,R2,R3     ;A = A - B
BRzp  LOOP               ;Branch to LOOP if A > B
FAIL    ADD R0,R0,#-1    ;QUOTIENT = -1
OUTPUT  ST R0,QUOTIENT
        ST R1,REMAINDER
HALT

A   .fill 10
B   .fill 21
QUOTIENT    .fill 0
REMAINDER    .fill 0
.end
