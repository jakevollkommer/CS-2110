;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Jake Vollkommer
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    LD R6, STACK

	ADD R6, R6, -2 ; Allocate space in the stack
	LD R0, A
	LD R1, B
	STR R0, R6, 0
	STR R1, R6, 1

    JSR GCD

	LDR R0, R6, 0 ; Load return value
	ADD R6, R6, 3 ; pop value off stack
	ST R0, ANSWER

    HALT

A       .fill 20
B       .fill 16
ANSWER  .blkw 1
STACK   .fill xF000

GCD

	ADD R6, R6, -5 ; Allocate return value/address, old FP
	STR R5, R6, 2  ; Store frame pointer on stack as old FP
	STR R7, R6, 3  ; Store return value on stack
	ADD R5, R6, 1 ; Set R5 to point to one above old fp loc

	LDR R0, R5, 4  ; Load first arg (a)
	LDR R1, R5, 5  ; Load second arg (b)
	LDR R2, R5, 5  ; Load b into R2

UDIV

	ADD R1, R1, 0
BRz TEARDOWN

	ADD R6, R6, -2 ; Make room for 2 parameters
	STR R2, R6, 0  ; Store b as first param
	STR R1, R6, 1  ; Store R1 as first param
	JSR GCD
	LDR R2, R6, 0  ; Load return value into R2

TEARDOWN
	STR R2, R5, 3  ; Store return value on the stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

.end
