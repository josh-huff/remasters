TITLE Program 4 - Composite Numbers (HuffJ.Project04.asm)

; Author: Josh Huff
; Course / Project ID: CS 271 / Project 4	Date: Feb 19, 2017
; Description: Using MASM to calculate and display composite numbers

INCLUDE Irvine32.inc

.const

; Declared constants
	
	upLim	EQU		400 ; Maximum user input
	maxLn	EQU		10  ; Maximum items per line

.data

	; No global variables -- all variables are local to procedures
	; Most operations are carried out using register contents instead of variables.

.code

main PROC

	call	introduction
	call	getUserData
	call	showComposites
	call	farewell

	exit

main ENDP

;-----------------------------Procedures------------------------------;

;----------------------------------------------------------------------
introduction PROC
; Displays program name
; Receives: n/a
; Returns:	n/a
;----------------------------------------------------------------------
.data

	intro	BYTE	"Composite Numbers     Programmed by Josh Huff", 13, 10, 0
	ec1		BYTE	"**EC: Aligned output columns", 13, 10, 0

.code

	mov		edx, OFFSET intro
	call	WriteString

	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLf

	ret

introduction ENDP

;----------------------------------------------------------------------
getUserData PROC
; Prompts user for number of composite terms to be displayed
; Receives: n/a
; Returns: n/a
;----------------------------------------------------------------------
.data

	instr1	BYTE	"Enter the number of composite numbers you would like to see.", 13, 10, 0
	instr2	BYTE	"I'll accept orders for up to 400 composites.", 13, 10, 10, 0
	prompt	BYTE	"Enter the number of composites to display [1 .. 400]: ", 0

.code
	mov		edx, OFFSET instr1
	call	WriteString

	mov		edx, OFFSET instr2
	call	WriteString

	mov		edx, OFFSET prompt
	call	WriteString

	call	ReadInt

	call	CrLf
	call	validate	; Validate operates on the current contents of eax

	ret

getUserData ENDP

;----------------------------------------------------------------------
validate PROC
; Ensures user input is between 1 and 400
; Receives: n/a
; Returns: n/a
;----------------------------------------------------------------------
.data

	rngErr	BYTE	"Out of range. Try again.", 13, 10, 0
	rPrompt	BYTE	"Enter the number of composites to display [1 .. 400]: ", 0
	
.code

retest:		; Execution goes here if user input is out of range and needs retesting

	cmp		eax, upLim
	jg		outOfRange
	
	cmp		eax, 1
	jl		outofRange

	call	CrLf

	ret		; As soon as the value of eax passes the cmp statements above, the procedure returns execution to getUserData, which returns to main

outOfRange:

	mov		edx, OFFSET rngErr
	call	WriteString
	mov		edx, OFFSET rPrompt
	call	WriteString
	call	ReadInt
	jmp		retest	

validate ENDP

;----------------------------------------------------------------------
showComposites PROC
; Displays composite numbers
; Receives: n/a
; Returns: n/a
;----------------------------------------------------------------------
.data

	perLine	BYTE	0
	spaces3	BYTE	"   ", 0	; Three spaces
	spaces4	BYTE	"    ", 0	; Four spaces
	spaces5	BYTE	"     ", 0	; Five spaces

.code

	mov		ecx, eax		; Create loop counter with value of eax
	mov		eax, 0			; Initialize eax to 0 for iteration

display:

	inc		eax				; Starting at 1, eax represents the value being tested
	call	isComposite
	cmp		ebx, 0
	je		display			; If isComposite sets ebx to 0, skips that digit by returning to the beginning of the loop, where eax is incremented

	call	WriteDec		; When a value is composite, it is written and the perLine count is incremented
	inc		perLine

	cmp		eax, 10			; The value of eax is displayed according to its length
	jl		oneDigit
	cmp		eax, 100
	jl		twoDigit
	cmp		eax, 100
	jge		threeDigit	

oneDigit:	; Execution jumps to appropriate section based on length of eax value, then invaraibly jumps to nextTerm

	mov		edx, OFFSET spaces5
	call	WriteString
	jmp		nextTerm	

twoDigit:

	mov		edx, OFFSET spaces4
	call	WriteString
	jmp		nextTerm

threeDigit:

	mov		edx, OFFSET spaces3
	call	WriteString
	jmp		nextTerm
	
newLine:	; Execution jumps here and perLine count is reset when the max is reached

	call	CrLf
	mov		perLine, 0	

nextTerm:	; Execution jumps here when the composite term is properly displayed
	
	cmp		perLine, maxLn
	je		newLine

	loop	display

	ret

showComposites ENDP

;----------------------------------------------------------------------
isComposite PROC
; Determines if numbers are composite
; Receives: n/a
; Returns: n/a
;----------------------------------------------------------------------

	mov		ebx, 2		; A counter for cycling through the digits for determining prime/composite

	cmp		eax, 4
	jl		nonComp		; 4 is the first composite number

compTest:

	xor		edx, edx	; Clears edx to accept the modulus
	push	eax			; Preserves the eax value on the stack
	div		ebx			; Divides by current value
	pop		eax			; Restores eax

	cmp		eax, ebx	; Testing for primes -- if a value reaches this point, it is only divisible by itself
	je		nonComp

	cmp		edx, 0		; If the modulus is zero, execution shifts to isComp and a value of 1 is placed in ebx, then the procedure returns
	je		isComp

	inc		ebx			; If the modulus is non-zero, ebx is incremented to the next divisor
	cmp		ebx, 22		; This process is repeated for divisors 2 through 21 (while not mathematically rigorous, this will suffice for n <= 400)
	jl		compTest

nonComp:

	mov		ebx, 0		; If a divisor is not found, a value of 0 is placed in ebx, then the procedure returns
	ret

isComp:

	mov		ebx, 1
	ret

isComposite ENDP

;----------------------------------------------------------------------
farewell PROC
; Displays a farewell message
; Receives: n/a
; Returns: n/a
;----------------------------------------------------------------------
.data

	bye		BYTE	"Results certified by Josh Huff. Goodbye.", 13, 10, 13, 10, 0

.code

	call	CrLf
	call	CrLf
	mov		edx, OFFSET bye
	call	WriteString

	ret

farewell ENDP

END main