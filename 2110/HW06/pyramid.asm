;;===============================
;; Name: Jake Vollkommer
;;===============================
;; Write a program to print out a pyramid to the console.

.orig x3000

;; CODE GOES HERE! :D
            AND R1,R1,#0  ;counter = 0
            AND R2,R2,#0
            ADD R2,R2,#1  ;current = 0
            AND R3,R3,#0
            ADD R3,R3,#1  ;stars = 1
            LD R4,LEVELS
            ADD R5,R4,#-1 ;spaces = LEVELS - current
            NOT R4,R4
            ADD R4,R4,#1  ;2's complement of LEVELS

            ADD R6,R2,R4
BRp      ENDLOOP
LOOP_LEVELS
            NOT R6,R5
            ADD R6,R6,#1
            ADD R6,R1,R6
BRn      LOOP_SPACES
CONT_LEVELS AND R1,R1,#0
            ADD R5,R5,#-1 ;spaces--
LOOP_STARS  LD R0,STAR
OUT                       ;Print a *
            NOT R6,R3
            ADD R6,R6,#1  ;2's complement of stars
            ADD R1,R1,#1  ;counter++
            ADD R6,R1,R6
BRn      LOOP_STARS
            LD R0,NEWLINE
OUT                       ;Print a \n
            AND R1,R1,#0
            ADD R3,R3,#2
            ADD R2,R2,#1

            ADD R6,R2,R4
BRnz     LOOP_LEVELS
BRnzp    ENDLOOP

LOOP_SPACES ADD R1,R1,#1  ;counter++
            LD R0,SPACE
OUT                       ;Print a space
            NOT R6,R5
            ADD R6,R6,#1
            ADD R6,R1,R6
BRn      LOOP_SPACES
BRnzp    CONT_LEVELS
ENDLOOP

HALT

LEVELS  .fill 10
SPACE   .fill x20
STAR    .fill x2A
NEWLINE .fill xA
.end
