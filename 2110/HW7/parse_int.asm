;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Jake Vollkommer
;;===============================

.orig x3000
    LD R6, STACK

    ; You can test your functions individually here
    ; Alternatively, if you are confident in your own code,
    ; you can run the tester directly without anything here


    ; This part has been done for you
    ; When ParseInt is ready, you can uncomment the below lines

    JSR PARSE_INT   ; call PARSE_INT with no arguments
    LDR R0, R6, 0   ; load return value
    ADD R6, R6, 1   ; pop return value of stack
    ST R0, ANSWER   ; store answer

    HALT


ANSWER              .blkw 1
STACK               .fill xF000


; ======================== PARSE_INT ========================
PARSE_INT

	ADD R6, R6, -5 ; Allocate return value/address, old FP, locals
	STR R7, R6, 3  ; Store frame pointer on the stack as old FP
	STR R5, R6, 2  ; Store return value on stack
	ADD R5, R6, 1  ; Set R5 to point to one above the old FP location

	AND R1, R1, 0  ; result = 0
	AND R2, R2, 0  ; isHex = 0

	STR R1, R5, 0  ; store result on stack
	STR R2, R5, -1 ; store isHex on stack

GETC
OUT

	LD R3, X
	NOT R3, R3
	ADD R3, R3, 1  ; -'x'
	ADD R3, R0, R3 ; R0 - 'x'
BRnp LOOP
	ADD R2, R2, 1  ; isHex = 1
	STR R2, R5, -1
GETC
OUT

LOOP
	LDR R1, R5, 0  ; store result in R1
	LDR R2, R5, -1 ; store isHex in R2

	ADD R6, R6, -2 ; allocate two arguments and one var
	STR R1, R6, 0  ; result is 1st arg
	STR R0, R6, 1  ; R0 is 2nd arg

	ADD R2, R2, 0
BRnp HEX
	LD R4, PARSE_DECIMAL_ADDR
	JSRR R4
	LDR R3, R6, 0 ; parsed = ParseDecimal(result, R0)
BR CHECK_DONE

HEX
	LD R4, PARSE_HEX_ADDR
	JSRR R4
	LDR R3, R6, 0 ; parsed = ParseHex(result, R0)
	LDR R1, R6, 1 ; restore old result
	LDR R2, R6, 3 ; restore old isHex

CHECK_DONE
	ADD R4, R3, 1 ; if parsed == -1
BRz PI_RETURN
	AND R1, R1, 0
	ADD R1, R1, R3 ; result = parsed
	STR R1, R5, 0
GETC
OUT

BR LOOP

PI_RETURN
	STR R1, R5, 3 ; Store return value on stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

X   .fill 120


PARSE_DECIMAL_ADDR  .fill x5000     ; the address of the ParseDecimal function
PARSE_HEX_ADDR      .fill x6000     ; the address of the ParseHex function
.end


; =========================== MULT ==========================
.orig x4000
MULT

	ADD R6, R6, -3 ; Allocate return value/address, old FP
	STR R7, R6, 1  ; Store frame pointer on the stack as old FP
	STR R5, R6, 0  ; Store return value on stack
	ADD R5, R6, -1 ; Set R5 to point to one above the old FP location

	AND R4, R4, 0  ; result = 0

	LDR R1, R5, 4  ; Load first arg
	LDR R2, R5, 5  ; Load second arg
BRnz DONE

MULT_LOOP
	ADD R4, R4, R1 ; result += a
	ADD R2, R2, -1 ; b--
BRp MULT_LOOP

DONE
	STR R4, R5, 3 ; Store return value on stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

.end


; ====================== PARSE_DECIMAL ======================
.orig x5000

PARSE_DECIMAL
	ADD R6, R6, -3 ; Allocate return value/address, old FP
	STR R7, R6, 1  ; Store frame pointer on the stack as old FP
	STR R5, R6, 0  ; Store return value on stack
	ADD R5, R6, -1 ; Set R5 to point to one above the old FP location

	LDR R1, R5, 4  ; Load first arg (acc)
	LDR R2, R5, 5  ; Load second arg (c)

	LD R3, ASCII
	NOT R3, R3
	ADD R3, R3, 1  ; -48 or '0'
	ADD R3, R2, R3 ; c - '0'
	BRn IF

	ADD R3, R3, -9 ; c - '9'
	BRnz SKIP
IF
	AND R3, R3, 0
	ADD R3, R3, -1
BR PD_TEARDOWN

SKIP
	AND R3, R3, 0
	ADD R3, R3, 10

	ADD R6,R6, -2  ; allocate two arguments
	STR R1, R6, 0  ; acc is 1st arg
	STR R3, R6, 1  ; 10 is 2nd arg

	LD R4, PD_MULT_ADDR
	JSRR R4

	LDR R3, R6, 0  ; m = Mult(acc, 10)
	LDR R2, R5, 5 ; Store old c back into R2
	ADD R3, R3, R2 ; m = m + c
	LD R4, ASCII
	NOT R4, R4
	ADD R4, R4, 1  ; -'0'
	ADD R3, R3, R4 ; m = m + c - '0'

PD_TEARDOWN
	STR R3, R5, 3  ; Store return value on stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

PD_MULT_ADDR    .fill x4000         ; the address of the Mult function
ASCII .fill 48
.end


; ======================== PARSE_HEX ========================
.orig x6000

PARSE_HEX

	ADD R6, R6, -3 ; Allocate return value/address, old FP
	STR R7, R6, 1  ; Store frame pointer on the stack as old FP
	STR R5, R6, 0  ; Store return value on stack
	ADD R5, R6, -1 ; Set R5 to point to one above the old FP location

	LDR R1, R5, 4  ; Load first arg (acc)
	LD R3, BASE

	ADD R6,R6, -2  ; allocate two arguments
	STR R1, R6, 0  ; acc is 1st arg
	STR R3, R6, 1  ; 16 is 2nd arg
	LD R4, PH_MULT_ADDR
	JSRR R4
	LDR R4, R6, 0  ; m = Mult(acc, 16)

	LDR R2, R5, 5  ; Load second arg (c)

	LD R3, ZERO
	NOT R3, R3
	ADD R3, R3, 1  ; -'0'
	ADD R3, R2, R3 ; c - '0'
BRn SKIPFIRST
	ADD R3, R3, -9 ; c - '9'
BRp SKIPFIRST
	ADD R3, R3, 9  ; c - '0'
	ADD R4, R4, R3 ; m + c - '0'
BR PH_TEARDOWN

SKIPFIRST
	LD R3, A
	NOT R3, R3
	ADD R3, R3, 1
	ADD R3, R2, R3 ; c - 'A'

BRn INVALID
	ADD R3, R3, -5 ; c - 'F'
BRp INVALID
	ADD R3, R3, 5  ; c - 'A'
	ADD R4, R4, R3 ; m + c - 'A'
	ADD R4, R4, 10 ; m + c - 'A' + 10
BR PH_TEARDOWN

INVALID
	AND R4, R4, 0
	ADD R4, R4, -1
PH_TEARDOWN
	STR R4, R5, 3  ; Store return value on the stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

A    .fill 65
BASE .fill 16
ZERO .fill 48

PH_MULT_ADDR    .fill x4000         ; the address of the Mult function
.end
