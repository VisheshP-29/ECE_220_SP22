; partners: ajaggi3, vprasad3
; Arnav Jaggi, Vishesh Prasad

; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST


; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;	Arnav Jaggi, Vishesh Prasad
; 	partners: ajaggi3, vprasad3
;	The following is the register table we used to print the histogram
;	R0 is used to hold output before it is printed
;	R1 holds a pointer to the histogram
;	R2 holds the ASCII value of '@'
;	R3 holds the memory at the start of the histogram
;	R4 serves as a temporary register and as a counter 
;	R5 serves as a counter 
; 	R6 serves as a counter

; We started out by printing putting x40 into R2, which is the ASCII value for '@'. After the character, we printed 'SPACE'. Next, we
; used a combination of nested loops. We looped through the histogram values, and using a nested loop, extracting and printing the four
; highest bits from the histogram memory four times. After printing the character, space, thenthe number of the characters found in hex, we
; went back and incremented R2 to print the next character, continuing with the loop by printing 'SPACE' and then going through the nested loop.
; Once 27 lines had been printed, we stop the program as by then, all of the histogram has been printed.

	AND R1, R1, #0		;clear R1
	AND R2, R2, #0		;clear R2
	AND R3, R3, #0		;clear R3
	AND R4, R4, #0		;clear R4
	AND R5, R5, #0		;clear R5
	AND R6, R6, #0		;clear R6
	LD R1, HIST_ADDR 	;point R1 to start of histogram

	
	LD R2, ASCIICHAR  	;load x40 into R2
	LD R6, NUM_BINS		;set R6 as counter
	

OUTPUT	AND R0, R0, #0 		;clear R0
	ADD R0, R2, R0		;add R2 and R0, store in R2
	OUT			;print
	ADD R2, R2, #1 		;increment R2	
	LD R0, SPACE		;load ascii value of (SPACE) into R0
	OUT			;print

	LDI R3, CHARACTER 	;load into R3, the memory at the location specified by R1
	AND R5, R5, #0		;clear R5
	ADD R5, R5, #4		;set outerloop counter (R5) to 4	
OLOOP	AND R4, R4, #0		;clear R4
	ADD R4, R4, #4		;set loop counter (R4) to 4
	AND R0, R0, #0		;clear R0
ILOOP	ADD R0, R0, R0		;left shift R0
	ADD R3, R3, #0		;add 0 to R3
	BRzp LSHIFT		;check if R3 starts with 0 or 1
	ADD R0, R0, #1		;if R3 starts with 1, add 1 to R0
LSHIFT	ADD R3, R3, R3		;leftshift R3 by 1
	ADD R4, R4, #-1		;decrement loop counter
	BRp ILOOP		;branch back to innerloop
	AND R4, R4, #0		;clear R4
	ADD R4, R0, #-10	;Subtract 10 from R0 and put it into the R4
	BRzp LETTER		;branch to LETTER if R4 is not negative
	AND R4, R4, #0		;clear R4
	LD R4, NUMBER		;load R4 with x30
	ADD R0, R0, R4		;add R4 and R0 and store it in R0
	OUT			;print value of R0
	BRnzp FINISH		;branch to FINISH
LETTER	LD R0, CAPITAL		;load R0 with x41
	ADD R0, R0, R4		;add R4 to R0, and store in R0
	OUT			;print value in R0
FINISH	ADD R5, R5, #-1		;decrement outerloop counter
	BRp OLOOP		;branch back to outerloop

	ADD R1, R1, #1		;increment R1
	ST R1, CHARACTER	;store the value of R1 into x3F00
	LD R0, NEWLINE		;load into R0 ascii value of newline
	OUT			;print newline
	ADD R6, R6, #-1		;decrement counter	
	
	BRp OUTPUT		;loop back





DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
ASCIICHAR 	.FILL x40	; hex value of ASCII '@'
SPACE 		.FILL x20	; hex value of ASCII 'SPACE'
NEWLINE 	.FILL x0A	; hex value of new line character
NUMBER		.FILL x30	; hex value of ASCII '0'
CHARACTER	.FILL x3F00	; histogram starting address
CAPITAL		.FILL x41	; hex value of ASCII 'A'

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
