.orig x3000

    LD R6, STACK

    ; Call digisum(n)
    LD R0, N
    ADD R6, R6, -1
    STR R0, R6, 0
    JSR DIGISUM

    ; Pop return value and arg off stack
    LDR R0,R6, 0
    ADD R6, R6, 2

    ; Save the answer
    ST R0, ANSWER

    HALT

STACK  .fill xF000
N      .fill 45
ANSWER .blkw 1
STACK  .fill xF000

    ; Preconditions
    ; R0 = X
    ; R1 = Y
    ; Postconditions:
    ; R0 = X / Y
    ; R1 = X % Y

DIGISUM

    ADD R6, R6, -3 ; Allocate return value/Address, old FP
    STR R5, R6, 0  ; Store frame pointer on the stack as old FP
    STR R7, R6, 1  ; Store return value on stack
    ADD R5, R6, -1 ; Set R5 to point to one above the old FP location

    ADD R6, R6, -2 ; Make room for local variables
    LDR R0, R5, -4 ; Load R0 with N
    AND R1, R1, 0
    ADD R1, R1, 10 ; Set R1 to 10
    UDIV           ; R0 = X/Y, R1 = X%Y
    STR R0, R5, 0
    STR R1, R5, -1 ; Store div and mod on stack as local vars
    LDR R2, R5, 4  ; Load N into R2
BRnp SKIPRET       ; if N == 0
    STR R2, R5, 3
    BR TEARDOWN
SKIPRET            ; if N != 0
    ADD R6, R6, -1 ; Make room for 1 parameter
    STR R0, R6, 0  ; Store div into param spot
    JSR DIGISUM    ; JSR
    LDR R3, R6, 0  ; Load return val from digisum->R3
    ADD R6, R6, 2  ; Pop down R6
    LDR R1, R5, -1 ; Reload mod into R1
    ADD R0, R1, R3 ; Add mod + digisum(div)
    STR R0, R5, 3  ; Store return value on stack

TEARDOWN
    ADD  R6, R5, 3 ;
    LDR R7, R5, 2  ;
    LDR R5, R5, 1  ;
RET
