;;===============================
;; Name: Jake Vollkommer
;;===============================
;; Write a program to search for a certain value in an array.

.orig x3000

;; CODE GOES HERE! :D
        LD R0,RESULT
        AND R1,R1,#0  ;counter = 0
        LD R7,LENGTH
        NOT R7,R7
        ADD R7,R7,#1  ;2's complement of LENGTH
        LD R2,NUMBER
        LD R3,ARRAY   ;Pointer at the start of the array

LOOP    LDR R4,R3,#0  ;Get the element in the array
;; element is contained if NUMBER ^ current = 0
;; xor = ~(~(a&~(a & b)) & ~(b & ~(a & b)))
        AND R5,R2,R4  ;a & b
        NOT R5,R5     ;c = ~(a&b)
        AND R6,R2,R5  ;a & c
        NOT R6,R6     ;d = ~(a&c)
        AND R5,R4,R5  ;b & c
        NOT R5,R5     ;e = ~(b&c)
        AND R6,R6,R5  ;d & e
        NOT R6,R6     ;~(d&e)
BRz   TRUE            ;NUMBER is contained in the array
        ADD R3,R3,#1  ;Point to the next element in the array
        ADD R1,R1,#1  ;counter++
        ADD R6,R1,R7  ;counter - LENGTH
BRn   LOOP
BRnzp FALSE           ;End of array, not contained

TRUE    AND R0,R0,#0
        ADD R0,R0,#1
        ST R0,RESULT
HALT

FALSE   AND R0,R0,#0
        ST R0,RESULT
HALT

ARRAY   .fill x6000
LENGTH  .fill 20
NUMBER  .fill 15
RESULT  .fill 0
ASCII   .fill x30
.end

.orig x6000
.fill 1
.fill 2
.fill 733
.fill 44
.fill 9
.fill 7
.fill 12
.fill 80
.fill 3
.fill 64
.fill 21
.fill 10
.fill 90
.fill 7
.fill 15
.fill 12
.fill 377
.fill 65
.fill 7
.fill 42
.end
