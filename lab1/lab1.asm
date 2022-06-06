.ORIG x3000
; write your code here

			AND		R1, R1, #0		;Clear R1
			LD		R1, NUMBER		;load number into R1			
			AND 	R2, R2, #0  	;Clear R2
			ADD 	R3, R2, #4  	;Set loop counter R3 to 4
LOOP		ADD		R2, R2, R2		;Shift R2 to hold next bit
			ADD		R1, R1, #0		;Loop to check highest order bits
			BRzp	LEFTSHIFT		;If highest order bit is zero or positive, skip addition
			ADD		R2, R2, #1		;Add 1 to R2 if highest order bit is 1
LEFTSHIFT	ADD		R1, R1, R1		;Left shift R1
			ADD		R3, R3, #-1		;Decrement loop counter
			BRp		LOOP			;Loop back
NUMBER		.Fill	x5813
			HALT
			.end
