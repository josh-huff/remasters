TITLE Program 1 - Elementary Arithmetic	(HuffJ.Project01.asm)

; Author: Josh Huff
; Course / Project ID: CS 271 / Project 1	Date: Jan 19, 2017
; Description: Practicing MASM syntax to do basic arithmetic

INCLUDE Irvine32.inc

; (no constant definitions)

.data

; Introductory strings

	intro	BYTE	"		Elementary Arithmetic		by Josh Huff", 0
	ec1		BYTE	"**EC: Program repeats until user chooses to quit.", 0
	ec2		BYTE	"**EC: Program verifies second number is less than first.", 0
	ec3		BYTE	"**EC: Program displays quotient as a float, rounded to nearest thousandth.", 0
	instr1	BYTE	"Enter 2 numbers and I'll show the sum, difference,", 0
	instr2	BYTE	"product, quotient, and remainder.", 0

; Prompts and user input for two integers

	prompt1	BYTE	"First number: ", 0
	num1	DWORD	?
	prompt2 BYTE	"Second number: ", 0
	num2	DWORD	?
	errmsg	BYTE	"The second number must be less than the first!", 0

; Math operands, operator, and their string equivalents

	sum		DWORD	?
	plus	BYTE	" + ", 0
	diff	DWORD	?
	minus	BYTE	" - ", 0
	prod	DWORD	?
	times	BYTE	" x ", 0
	quot	DWORD	?
	divide	BYTE	" / ", 0
	remain	DWORD	?
	modulo	BYTE	" remainder ", 0
	fquot	REAL4	?
	thous	REAL4	1000.0
	equals	BYTE	" = ", 0

; Extra Credit: Jumping to the start

	eccont	BYTE	"Do you wish to try again(enter 1 for yes, hit enter for no)? ", 0
	again	DWORD	?	

; Goodbye message

	bye		BYTE	"Impressed? Bye!", 0

.code
main PROC

;----Introduction----;

	mov		edx, OFFSET intro
	call	WriteString
	call	CrLf
	call	CrLf
	
	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLf

	mov		edx, OFFSET ec2
	call	WriteString
	call	CrLf

	mov		edx, OFFSET ec3
	call	WriteString
	call	CrLf
	call	CrLf

; Extra Credit: Program returns to this point if user chooses to try again
beginning:

	mov		edx, OFFSET instr1
	call	WriteString
	call	CrLf

	mov		edx, OFFSET instr2
	call	WriteString
	call	CrLf
	call	CrLf

;----Get the Data----;

	mov		edx, OFFSET prompt1
	call	WriteString
	call	ReadInt
	mov		num1, eax

	mov		edx, OFFSET prompt2
	call	WriteString
	call	ReadInt
	mov		num2, eax
	call	CrLf
	
; Extra Credit: Checks to see that number 2 is less than number 1, and loops until it is

	.if num1 < eax
		.repeat
			mov		edx, OFFSET errmsg
			call	WriteString
			call	CrLf
			call	CrLf
			mov		edx, OFFSET prompt2
			call	WriteString
			call	ReadInt
			mov		num2, eax
		.until	num1 >= eax
	.endif
	
	call	CrLf

;----Calculate the Required Values----;

; Addition

	mov		eax, num1
	mov		ebx, num2
	add		eax, ebx
	mov		sum, eax

; Subtraction

	mov		eax, num1
	mov		ebx, num2
	sub		eax, ebx
	mov		diff, eax

; Multiplication

	mov		eax, num1
	mov		ebx, num2
	mul		ebx
	mov		prod, eax

; Division

	mov		eax, num1
	xor		edx, edx
	div		ebx
	mov		quot, eax
	mov		remain, edx

; Extra Credit: Float Division (special thanks to Google and caffeine)
; Divides the inputs as floats, multiplies by 1000, rounds appropriately, then divides by 1000	

	fild	num1		
	fidiv	num2
	fmul	thous
	frndint
	fdiv	thous 
	mov		fquot, eax

;----Display the Results----;

; Display addition

	mov		eax, num1
	call	WriteDec

	mov		edx, OFFSET plus
	call	WriteString

	mov		eax, num2
	call	WriteDec

	mov		edx, OFFSET equals
	call	WriteString

	mov		eax, sum
	call	WriteDec
	call	CrLf

; Display subtraction

	mov		eax, num1
	call	WriteDec

	mov		edx, OFFSET minus
	call	WriteString

	mov		eax, num2
	call	WriteDec

	mov		edx, OFFSET equals
	call	WriteString

	mov		eax, diff
	call	WriteDec
	call	CrLf

; Display multiplication

	mov		eax, num1
	call	WriteDec

	mov		edx, OFFSET times
	call	WriteString

	mov		eax, num2
	call	WriteDec

	mov		edx, OFFSET equals
	call	WriteString

	mov		eax, prod
	call	WriteDec
	call	CrLf

; Display division

	mov		eax, num1
	call	WriteDec

	mov		edx, OFFSET divide
	call	WriteString

	mov		eax, num2
	call	WriteDec

	mov		edx, OFFSET equals
	call	WriteString

	mov		eax, quot
	call	WriteDec

	mov		edx, OFFSET modulo
	call	WriteString

	mov		eax, remain
	call	WriteDec
	call	CrLf

; Display floating point division

	mov		eax, num1
	call	WriteDec

	mov		edx, OFFSET divide
	call	WriteString

	mov		eax, num2
	call	WriteDec

	mov		edx, OFFSET equals
	call	WriteString

	mov		eax, fquot
	call	WriteFloat
	call	CrLf
	call	CrLf

;----Extra Credit: Ask if User is Done----;

	mov		edx, OFFSET eccont
	call	WriteString
	call	ReadInt
	mov		again, eax
	call	CrLf

	.if	again == 1
		jmp		beginning
	.endif

;----Say Goodbye----;

	mov		edx, OFFSET bye
	call	WriteString
	call	CrLf
	call	CrLf

	exit	; exit to operating system
main ENDP

; (no additional procedures)

END main