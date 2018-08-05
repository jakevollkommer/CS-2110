;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Jake Vollkommer
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    LD R6, STACK

	LD R0, N       ; Load n as an argument
	ADD R6, R6, -1 ; Allocate space on the stack
	STR R0, R6, 0

    JSR COLLATZ     ; call Collatz

	LDR R0, R6, 0
	ADD R6, R6, 2
	ST R0, ANSWER

    HALT


N       .fill 3
ANSWER  .fill 0
STACK   .fill xF000


COLLATZ
	ADD R6, R6, -3
	STR R5, R6, 0
	STR R7, R6, 1
	ADD R5, R6, -1

	LDR R0, R5, 4 ; Load argument into R0

	AND R2, R2, 0
	ADD R3, R2, -1
	ADD R3, R0, R3 ; n - 1
BRz DONE

	AND R1, R1, 0
	ADD R1, R1, 2  ; R1 = 2
UDIV
	ADD R1, R1, 0
BRz EVEN
	ADD R6, R6, -1 ; Allocate space for parameters
	AND R3, R3, 0
	LDR R0, R5, 4  ; Restore old n
	ADD R3, R3, R0 ; m = n
	ADD R3, R3, R0 ; m = n * 2
	ADD R3, R3, R0 ; m = n * 3
	ADD R3, R3, 1  ; m = n * 3 + 1
	STR R3, R6, 0  ; add m as a parameter
	JSR COLLATZ
	LDR R2, R6, 0  ; c = Collatz(m)
	ADD R2, R2, 1  ; R2 -> c + 1
BR DONE

EVEN
	ADD R6, R6, -1 ; Allocate space for parameter
	STR R0, R6, 0  ; add R0 as a parameter
	JSR COLLATZ
	LDR R2, R6, 0  ; c = Collatz(R0)
	ADD R2, R2, 1  ; R2 -> c + 1

DONE
	STR R2, R5, 3  ; Store return value
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

.end
