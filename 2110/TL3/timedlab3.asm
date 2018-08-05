;;===============================
;; Timed Lab 3 (Spring 2017)
;;
;; Name: Jake Vollkommer
;;===============================
;; Write a program that counts the occurence of each number,
;; 0 to 9 inclusive, in an array.

.orig x3000

	LD R0, TABLE   ; Pointer to TABLE[0]
	AND R1, R1, 0
	ADD R1, R1, 10 ; i = 10
	AND R2, R2, 0
CLEARTABLE
	ADD R3, R0, 0
	STR R2, R3, 0  ; TABLE[i] = 0;
	ADD R0, R0, 1  ; Point to next index of TABLE
	ADD R1, R1, -1 ; i--
BRp CLEARTABLE
	LD R0, TABLE   ; point to TABLE[0]
	LD R4, ARRAY   ; point to ARRAY[0]
	AND R1, R1, 0  ; i = 0
	LD R2, LENGTH
	NOT R2, R2
	ADD R2, R2, 1  ; 2's complement of LENGTH
	ADD R3, R1, R2 ; i - LENGTH
	BRzp DONE
LOOP
	LDR R5, R4, 0  ; index = ARRAY[i]
	ADD R5, R0, R5 ; point to TABLE[index]
	LDR R6, R5, 0  ; value of TABLE[index]
	ADD R6, R6, 1  ; TABLE[index] += 1
	STR R6, R5, 0  ; Store new value at TABLE[index]
	ADD R4, R4, 1  ; point to next index of ARRAY

	ADD R1, R1, 1  ; i++
	ADD R3, R1, R2 ; i - LENGTH
BRn LOOP
DONE
	HALT

ARRAY .fill x6000
LENGTH .fill 20
TABLE .fill x7000
.end

;; This array contains the elements you will count
.orig x6000
.fill 1
.fill 2
.fill 3
.fill 4
.fill 5
.fill 6
.fill 7
.fill 8
.fill 9
.fill 0
.fill 1
.fill 2
.fill 4
.fill 4
.fill 5
.fill 6
.fill 7
.fill 8
.fill 9
.fill 0
.end

;; This array stores the counts of the ten possible elements
.orig x7000
.blkw 10
.end
