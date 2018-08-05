;;===============================
;; Name: Jake Vollkommer
;;===============================
;; Write a program that sorts an array in ascending order.

.orig x3000

;; CODE GOES HERE! :D
             LD R1,ARRAY    ;Pointer to beginning of array
             LD R2,LENGTH
             AND R3,R3,#0   ;k = 0
CHECK_DONE   NOT R7,R2
             ADD R7,R7,#1   ;2's complement of LENGTH
             ADD R4,R3,R7   ;k - LENGTH
BRzp      DONE
LOOP         AND R4,R4,#0
             ADD R4,R4,#1   ;isSorted = 1
             AND R5,R5,#0   ;i = 0
CHECK_IN     NOT R7,R3
             ADD R7,R7,#1   ;2's complement of k
             ADD R7,R2,R7   ;LENGTH - k
             NOT R7,R7
             ADD R7,R7,#1   ;2's complement of (LENGTH - k)
             ADD R6,R5,#1   ;i + 1
             ADD R7,R6,R7
BRzp      CHECK_SORTED

IN_LOOP      ADD R5,R5,#1   ;i++ after swap
             LDR R6,R1,#0   ;ARRAY[i - 1]

             ADD R1,R1,#1   ;Point to next element
             LDR R7,R1,#0   ;temp =  ARRAY[i]
             NOT R0,R6
             ADD R0,R0,#1   ;2's complement of ARRAY[i - 1]
             ADD R0,R7,R0   ;ARRAY[i] - ARRAY[i - 1]
BRn       SWAP
BRnzp     CHECK_IN

CHECK_SORTED ADD R3,R3,#1   ;k++
             LD R1,ARRAY    ;Point back to the first element
             AND R0,R4,#-1
BRp DONE
BRnzp     CHECK_DONE

SWAP         STR R6,R1,#0   ;ARRAY[i] = ARRAY[i-1]
             STR R7,R1,#-1  ;ARRAY[i - 1] = temp
             AND R4,R4,#0   ;isSorted = 0
BRnzp     CHECK_IN

DONE
HALT

ARRAY   .fill x6000
LENGTH  .fill 7
.end

;; This array should be sorted when finished
.orig x6000
.fill 7
.fill 6
.fill 5
.fill 4
.fill 3
.fill 2
.fill 1
.end
