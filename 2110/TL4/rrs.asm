;;===============================
;; CS 2110 Spring 2017
;; Timed Lab 4 - Functions
;; Name: Jake Vollkommer
;;===============================

; DO NOT REMOVE THIS LINE, UDIV is used inside PRINT
;@plugin filename=lc3_udiv vector=x80

.orig x3000
	LD R6, STACK

	LD R0, CURR_HEAD	; load address of linked-list head
	ADD R6, R6, -1
	STR R0, R6, 0		; push it on the stack

	JSR REVERSE_SUM		; call the reverseSum function
	LDR R0, R6, 0		; load return value
	ADD R6, R6, 2		; pop arg+rv off the stack

	ST R0, SUM 			; store answer in SUM
	HALT


CURR_HEAD	.fill HEAD1		; you can change this to any HEADx to test

SUM		.blkw 1

STACK	.fill xF000


REVERSE_SUM

	ADD R6, R6, -4 ; Allocate return value/address, old FP
	STR R5, R6, 1  ; Store frame pointer on stack as old FP
	STR R7, R6, 2  ; Store return value on stack
	ADD R5, R6, 0 ; Set R5 to point to one above old fp loc

	LDR R4, R5, 4  ; Load nodePtr -> R4
BRz BASE
	LDR R1, R4, 1  ; nextPtr = mem[nodePtr + 1]

	ADD R6, R6, -1 ; Make room for 1 parameter
	STR R1, R6, 0  ; nextPtr is arg
	JSR REVERSE_SUM
	LDR R2, R6, 0  ; sum = reversePrint(nextPtr)

	LDR R4, R5, 4  ; restore old nodePtr
	LDR R3, R4, 0  ; mem[nodePtr]
	ADD R2, R2, R3 ; sum += mem[nodePtr]
	STR R2, R5, 0  ; store sum on stack

	ADD R6, R6, -1 ; Make room for 1 parameter
	STR R2, R6, 0  ; sum is arg
	LD R3, PRINT_ADDR
	JSRR R3
	LDR R2, R5, 0  ; restore sum
BR RETURN

BASE AND R2, R2, 0
RETURN
	STR R2, R5, 3  ; Store return value on the stack
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET


PRINT_ADDR .fill PRINT
.end


; The linked-list nodes

.orig x4000
HEAD1		; should print: 3 3 12 14 17 22
.fill 5		; the first number is the value
.fill x4004	; the second number is the address of the next node
.end

.orig x4004
.fill 3
.fill x4008
.end

.orig x4008
.fill 2
.fill x400C
.end

.orig x400C
.fill 9
.fill x4010
.end

.orig x4010
.fill 0
.fill x4014
.end

.orig x4014
.fill 3
.fill x0
.end


.orig x4040
HEAD2		; should print 1 16 58 67 77
.fill 10
.fill x4050
.end

.orig x4044
.fill 42
.fill x404C
.end

.orig x4048
.fill 1
.fill x0
.end

.orig x404C
.fill 15
.fill x4048
.end

.orig x4050
.fill 9
.fill x4044
.end


.orig x4080
HEAD3		; should print 5000
.fill 5000
.fill x0
.end


.orig x5000
PRINT
.fill x1dbf
.fill x7f80
.fill x6181
.fill x1dbf
.fill x7180
.fill x4806
.fill x1da2
.fill x2003
.fill xf021
.fill x6f80
.fill xc1c0
.fill x0020
.fill x1dbd
.fill x7f81
.fill x7b80
.fill x1bbf
.fill x6144
.fill x0a04
.fill x2214
.fill x1001
.fill xf021
.fill x0e0d
.fill x2211
.fill xf080
.fill x1dbf
.fill x7340
.fill x1020
.fill x0403
.fill x1dbf
.fill x7180
.fill x4fed
.fill x6140
.fill x2206
.fill x1001
.fill xf021
.fill x1d63
.fill x6f42
.fill x6b41
.fill xc1c0
.fill x0030
.fill x000a
.end
