.orig x3000

    LD R6, SATCK

    LD R0, A
    LD R1, B

    ADD R6, R6, -2 ; allocate two arguments
    STR R0, R6, 0  ; a is 1st arg
    STR R1, R6, 1  ; b is 2nd arg

    JSR CALLEE

    LDR R0, R6, 0  ; load return value
    ADD R6, R6, 3  ; pop off arguments + return value

    ST R0, ANSWER

    HALT

A        .fill 42
B        .fill 13
ANSWER   .blkw 1
STACK    .fill xF000


CALLEE

    ADD R6, R6, -3 ; allocate 3 spaces for important values
    STR R7, R6, 1  ; store return address
    STR R5, R6, 0  ; store old frame pointer
    ADD R5, R6, -1 ; create new frame pointer

    ; function

    LDR R0, R5, 4  ; load first argument
    LDR R1, R5, 5  ; load second argument

    ADD R2,R0,R1 ; add A and B

    STR R2, R5, 3 ;store return value
    ADD R6, R5, 3 ; top of stack is now pointing to the return value
    LDR R7, R5, 2 ; restore return address
    LDR R5, R5, 1 ;
    RET

.end
