;;======================================================================
;; CS2110                         Lab #12                      Fall 2016
;;======================================================================
;; Filename: sumtorial.asm
;; Author: Jake Vollkommer
;; Date: 2/20/2017
;; Assignment: Lab 11
;; Description: An assembly program to calculate sumtorial
;;======================================================================

;;Pseudocode:
;;-----------

; Sumtorial(n)
; {
;     int i;
;     int sum = 0;
;     for(i = 0; i < n; i++)
;     {
;        sum += n
;        n = n-1;
;     }
;     return sum;
; }

.orig x3000

;;Your Code Here
	AND R0,R0,#0 ;sum = 0
	AND R1,R1,#0 ;i = 0
	LD R2,NUM    ;n = NUM
	;ADD R2,R2,#1 ;;??
	NOT R3,R2
	ADD R3,R3,#1 ;2's complement of n
	ADD R4,R1,R3
BRzp   OUTPUT
LOOP
	ADD R0,R0,R2  ;sum += n
	ADD R2,R2,#-1 ;n--
	;ADD R1,R1,#1  ;i++
	NOT R3,R2
	ADD R3,R3,#1 ;2's complement of n
	ADD R4,R1,R3
BRn    LOOP

OUTPUT ST R0,NUM
HALT

NUM     .FILL     #5
ASCII   .fill x30
.end
