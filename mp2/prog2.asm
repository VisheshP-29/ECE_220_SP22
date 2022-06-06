; The approach that we took for this machine problem was to follow the flowchart provided in order to write
; easy-to-follow and flowable code. Our first step was to take in the input from the user and echoed to the monitor.
; Then, we checked if the input was a valid character or not. If we encounter an invalid input, we print 'Invalid Expression'
; into the monitor. We then check if the input is a number, and pushing it to the stack if it is a number. If it is not a number
; we checked what type of operator, the input is and jump to the appropriate operator subroutine. If we encounterd an equals sign
; we would pop from the stack, two times. The first was to get the most recent value from the stack, and the second pop is to check
; for underflow, since if we do not encounter underflow, that means that the equals was an invalid expression. If the equals evaluator
; runs correctly, we then print send the result of all the calculations to be printed by our hex printer and stored in R5.
; partners: vprasad3, ajaggi3


.ORIG x3000
	
;your code goes here
	
		AND R0, R0, #0		;clear R0
		AND R1, R1, #0		;clear R1
		AND R2, R2, #0		;clear R2
		AND R3, R3, #0		;clear R3
		AND R4, R4, #0		;clear R4
		AND R5, R5, #0		;clear R5
		AND R6, R6, #0		;clear R6

GETIN	GETC				;get input from user
		OUT					;echo character back to user

		LD R1, EQUALS		;load R1 with ASCII value for '='
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 (2's complement)
		ADD R1, R0, R1		;subtract R1 from R0 to see if the input is =
		BRz EQAEVAL			;if value is 0, branch to the output calculation section

		LD R1, SPACE		;load R1 with the ASCII value for 'space'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0 to see if input is a 'space'
		BRz	GETIN			;if the input is 'space', do nothing, and get the next input
		
		LD R1, EXPSIGN		;load R1 with the ASCII value for '^'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0 to see if input is '^'
		BRz OPERATOR		;if value is 0, branch to operation calculation

		LD R1, MULSIGN		;load R1 with the ASCII value for '*'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0 to see if input is '*'	
		BRn INVALID			;if the value is negative, it's below the '*', and therefore invalid in our code, so branch to Invalid

		LD R1, NINESIGN		;load R1 with the ASCII value for 9
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0 to see if input is greater than 9
		BRp INVALID			;if value is positive, it's above 9, and therefore invalid (we already checked for '^' earlier)
		
		LD R1, RAND1		;load R1 with the ASCII value for ','
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;Subtract R1 from R0
		BRz INVALID			;if value is 0, branch to Invalid

		LD R1, RAND2		;load R1 with the ASCII value for '.'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0
		BRz INVALID			;if value is 0, branch to Invalid

		LD R1, ZEROSIGN		;load R1 with the ASCII value for 0
		NOT R1, R1		    ;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R0, R1		;subtract R1 from R0
		BRn OPERATOR		;if value is negative branch to operation calculation, positive means that the input is a number

;Push Number to Stack		
PSH2	LD R1, ZEROSIGN		;load R1 with the ASCII value for '0'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R0, R0, R1		;subtract R1 and R0
		JSR PUSH			;push answer
		ADD R5, R5, #0		;check for overflow	
		BRp INVALID			;if overflows, go to INVALID
		BRnzp GETIN			;get next input

;Operation Calculations
OPERATOR
		AND R6, R6, #0		;clear R6
		ADD R6, R0, R6		;store value in R0 in R6
		AND R3, R3, #0		;clear R3
		AND R4, R4, #0		;clear R4
		JSR POP				;pop new value
		ADD R5, R5, #0		;add 0 to R5
		BRp INVALID			;check for underflow
		ADD R4, R0, R4		;store value in R0 in R4
		JSR POP				;pop next value
		ADD R5, R5, #0		;add 0 to R5
		BRp INVALID			;check for underflow
		ADD R3, R0, R3		;store value in R0 in R3

ADDEVAL	LD R1, ADDSIGN		;load R1 with the ASCII value for '+'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R6, R1		;add R6 to R1, store in R1
		BRnp SUBEVAL		;if the value is not 0, go to SUBEVAL
		JSR PLUS			;else, execute PLUS subroutine
		BRnzp CONT			;PUSH answer

SUBEVAL	LD R1, SUBSIGN		;load R1 with the ASCII value for '-'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R6, R1		;subtract R6 from R1
		BRnp MULEVAL		;if value is not 0, go to MULEVAL
		JSR MIN				;else, execute MIN subroutine
		BRnzp CONT			;PUSH answer

MULEVAL	LD R1, MULSIGN		;load R1 with the ASCII value for '*'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R6, R1		;subtract R6 from R1
		BRnp DIVEVAL		;if value is not 0, go to DIVEVAL
		JSR MUL				;else, execute MUL subroutine
		BRnzp CONT			;PUSH answer

DIVEVAL	LD R1, DIVSIGN		;load R1 with ASCII value of '/'
		NOT R1, R1			;negate R1
		ADD R1, R1, #1		;add 1 to R1
		ADD R1, R6, R1		;subtract R6 from R1
		BRnp EXPEVAL		;if value is not 0, go to EXPEVAL
		JSR DIV				;else, execute DIV subroutine
		BRnzp CONT			;PUSH answer

EXPEVAL	JSR EXP				;execute EXP subroutine


CONT	JSR PUSH			;push to stack
		ADD R5, R5, #0		;check for overflow
		BRp INVALID			;if overflow, go to Invalid
		BRnzp GETIN			;get next input value

; Equals Evalutation
EQAEVAL	AND R3, R3, #0		;clear R3
		AND R4, R4, #0		;clear R4
		JSR POP				;pop value from stack
		ADD R5, R5, #0		;check for underflow
		BRp INVALID			;if underflow, go to INVALID
		ADD R3, R0, R3		;add R0 to R3
		ADD R4, R0, R4		;add R0 to R4
		JSR POP				;pop value from stack
		ADD R5, R5, #0		;check for underflow
		BRz INVALID			;if underflow, go to INVALID
		AND R5, R5, #0		;clear R5
		ADD R5, R4, R5		;store value in R4 in R5
		JSR PRINT_HEX		;execute PRINT_HEX subroutine
		BRnzp STOP			;branch to STOP


INVALID	LEA R0, BADOUT		;load R0 with string 'Invalid Expression' from memory location specified by BADOUT
		PUTS				;print string located at memory location stored at R0


STOP	HALT				;stop execution of program



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
		
		ST R7, PRINT_SAVE		;store value of R7 at memory location PRINT_SAVE
		AND R0, R0, #0			;clear R0
		AND R2, R2, #0			;clear R2
		AND R4, R4, #0			;clear R4
		AND R6, R6, #0			;clear R6

		ADD R6, R6, #4			;add 4 to R6
POLOOP	AND R4, R4, #0			;clear R4
		ADD R4, R4, #4			;add 4 to R4
		AND R0, R0, #0			;clear R0
PILOOP	ADD R0, R0, R0			;add R0 to itself
		ADD R3, R3, #0			;check R3
		BRzp SHIFT				;if zero or positive, branch to leftshift
		ADD R0, R0, #1			;add 1 to R0
SHIFT	ADD R3, R3, R3			;leftshift R3
		ADD R4, R4, #-1			;subtract 1 from R4
		BRp PILOOP				;as long as R4 is positive, loop back to PILOOP
		AND R4, R4, #0			;clear R4
		ADD R4, R0, #-10		;store in R4, R0 - #10
		BRzp LET				;if value is zero or positive, go to LET
		AND R4, R4, #0			;clear R4
		LD R4, NUM				;load R4 with ASCII value of '0'
		ADD R0, R0, R4			;add R4 to R0
		OUT						;write one character in R0 to screen
		BRnzp FIN				;go to FIN loop
LET		LD R0, CAP				;load R0 with ASCII value of 'A'
		ADD R0, R0, R4			;add R4 to R0
		OUT						;write chracter to screen
FIN		ADD R6, R6, #-1			;decrement R6 by 1
		BRp POLOOP				;if positive, go to POLOOP 
		LD R7, PRINT_SAVE		;load R7 with value saved in PRINT_SAVE
		RET						;return to original code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Plus Subroutine
PLUS	
;your code goes here

		AND R0, R0, #0			;clear R0
		ADD R0, R3, R4 			;add R4 and R3, store in R0
		RET						;return to original code
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Minus Subroutine
MIN	
;your code goes here

		AND R0, R0, #0			;clear R0
		NOT R4, R4				;negate R4
		ADD R4, R4, #1			;add 1 to R4
		ADD	R0, R3, R4			;subtract R3 and R4, store in R0
		RET						;return to original code
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Multiply Subroutine
MUL	
;your code goes here

		AND R0, R0, #0			;clear R0
		ADD R4, R4, #0			;check R4
		BRz ENDMUL				;if 0, go to ENDMUL
		BRp MULPOS				;if positive, go to MULPOS
MULNEG	ADD R0, R0, R3			;add R3 to R0
		ADD R4, R4, #1			;add 1 to R4
		BRn MULNEG				;if R4 is negative, loop back to MULNEG
		NOT R0, R0				;negate R0
		ADD R0, R0, #1			;add 1 to R0
		BRnzp ENDMUL			;finish subroutine
MULPOS	ADD R0, R0, R3			;add R3 to R0
		ADD R4, R4, #-1			;decrement R4
		BRp MULPOS				;if R4 is positive, loop back to MULPOS
ENDMUL	RET						;return to original code
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Division Subroutine
DIV	
;your code goes here

		AND R0, R0, #0			;clear R0
		NOT R4, R4				;negate R4
		ADD R4, R4, #1			;add 1 to R4
DIVLOOP	ADD R0, R0, #1			;add 1 to R0
		ADD R3, R3, R4			;add R3 and R4, store in R3
		BRzp DIVLOOP			;if zero or positive, loop back to DIVLOOP
		ADD R0, R0, #-1			;decrement R0
		RET						;return to original code
				
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Exponent Subroutine
EXP
;your code goes here
		
		AND R0, R0, #0			;clear R0
		AND R6, R6, #0			;clear R6
	 	AND R5, R5, #0			;clear R5
		ADD R5, R3, R5			;add R3 to R5
		ADD R4, R4, #0			;check R4 
		BRz ZEROEXP				;if R4 is 0, go to ZEROEXP
		ADD R4, R4, #-1			;decrement R4
OLOOP	AND R6, R6, #0			;clear R6
		ADD R6, R5, R6			;add R5 to R6
ILOOP	ADD R0, R0, R3			;add R3 to R0
		ADD R6, R6, #-1			;decrement R6
		BRp ILOOP				;if positive, branch back to ILOOP
		ADD R3, R0, #0			;add R0 to R3
		AND R0, R0, #0			;clear R0
		ADD R4, R4, #-1			;decrement R4
		BRp OLOOP				;if positive, branch back to OLOOP
		ADD R0, R3, #0			;add R3 to R0
		BRnzp GOBACK			;skip to GOBACK
ZEROEXP	ADD R0, R0, #1			;if exponent is 0, set R0 to 1
GOBACK	RET						;return back to original code


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
		ST R3, PUSH_SaveR3	;save R3
		ST R4, PUSH_SaveR4	;save R4
		AND R5, R5, #0		;clear R5
		LD R3, STACK_END	;load R3 with STACK_END
		LD R4, STACk_TOP	;load R4 with STACk_TOP
		ADD R3, R3, #-1		;decrement R3
		NOT R3, R3			;negate R3
		ADD R3, R3, #1		;increment R3
		ADD R3, R3, R4		;add R4 to R3
		BRz OVERFLOW		;stack is full
		STR R0, R4, #0		;no overflow, store value in the stack
		ADD R4, R4, #-1		;move top of the stack
		ST R4, STACK_TOP	;store top of stack pointer
		BRnzp DONE_PUSH		;push values
OVERFLOW
		ADD R5, R5, #1		;if overflow, set R5 to 1
DONE_PUSH
		LD R3, PUSH_SaveR3	;load R3 with saved value
		LD R4, PUSH_SaveR4	;load R4 with saved value
		RET					;return to original code


PUSH_SaveR3	.BLKW #1	;save blank space for R3
PUSH_SaveR4	.BLKW #1	;save blank space for R4


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
		ST R3, POP_SaveR3	;save R3
		ST R4, POP_SaveR4	;save R3
		AND R5, R5, #0		;clear R5
		LD R3, STACK_START	;load R3 with value of STACK_START
		LD R4, STACK_TOP	;load R4 with top of the STACK
		NOT R3, R3			;negate R3
		ADD R3, R3, #1		;add 1 to R3
		ADD R3, R3, R4		;add R4 to R3
		BRz UNDERFLOW		;check underflow
		ADD R4, R4, #1		;increment R4
		LDR R0, R4, #0		;load R0 with memory at R4
		ST R4, STACK_TOP	;store R4 in STACK_TOP
		BRnzp DONE_POP		;pop
UNDERFLOW
		ADD R5, R5, #1		;if underflow, set R5 to 1
DONE_POP
		LD R3, POP_SaveR3	;load R3 with saved value
		LD R4, POP_SaveR4	;load R4 with saved value
		RET					;return to original code


POP_SaveR3	.BLKW #1	;save blank space for R3
POP_SaveR4	.BLKW #1	;save blank space for R4
STACK_END	.FILL x3FF0	;fill STACK_END with x3FF0
STACK_START	.FILL x4000	;fill STACK_START with x4000
STACK_TOP	.FILL x4000	;fill STACK_TOP with x4000


BADOUT		.STRINGZ "Invalid Expression"	;fill BADOUT with 'Invalid Expression' string
EQUALS		.FILL x3D						;ASCII value of =
SPACE		.FILL x20						;ASCII value of space
EXPSIGN		.FILL x5E						;ASCII value of ^
ZEROSIGN	.FILL x30						;ASCII value of 0
MULSIGN		.FILL x2A						;ASCII value of *
ADDSIGN		.FILL x2B						;ASCII value of +
SUBSIGN		.FILL x2D						;ASCII value of -
DIVSIGN		.FILL x2F						;ASCII value of /
NINESIGN	.FILL x39						;ASCII value of 9
RAND1		.FILL x2C						;ASCII value of ,
RAND2		.FILL x2E						;ASCII value of .
NUM			.FILL x30						;ASCII value of 0
CAP 		.FILL x41						;ASCII value of A
PRINT_SAVE	.BLKW #1						;save blank space


.END										;we're done :)
