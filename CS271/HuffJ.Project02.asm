TITLE Program 2 - Fibonacci Sequence (HuffJ.Project02.asm)

; Author: Josh Huff
; Course / Project ID: CS 271 / Project 2	Date: Jan 26, 2017
; Description: Using MASM to calculate and display a Fibonacci sequence

INCLUDE Irvine32.inc

.const

; Declared constants
	
	maxNum	EQU		46 ; Maximum number of Fibonacci terms

.data

; Introductory strings

	intro	BYTE	"Fibonacci Sequence", 13, 10, "Programmed by Josh Huff", 13, 10, 10, 0
	ec1		BYTE	"**EC: Displays the numbers in aligned columns", 13, 10, 0

; Prompts and user input for name and number of Fibonacci terms

	getName	BYTE	"What's your name? ", 0
	uName	BYTE	33 DUP(0)
	hi		BYTE	"Hello, ", 0
	instr1	BYTE	"Enter the Fibonacci terms to be displayed ", 13, 10, 0
	instr2	BYTE	"Give the number as an integer in the range [1 .. 46]: ", 13, 10, 0
	prompt	BYTE	"How many Fibonacci terms do you want? ", 0
	numTerm	DWORD	?
	errmsg	BYTE	"Out of range. Enter a number in [1 .. 46]: ", 0

; 
	tempFib	DWORD	?
	perLine	BYTE	?
	spaces5	BYTE	"     ", 0
	spaces4	BYTE	"    ", 0
	spaces3	BYTE	"   ", 0
	spaces2	BYTE	"  ", 0
	spaces1	BYTE	" ", 0

; farewell

	bye		BYTE	"Results certified by Josh Huff", 13, 10, "Goodbye, ", 0

.code
main PROC

;----Introduction----;

	mov		edx, OFFSET intro
	call	WriteString
	
	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLf

	mov		edx, OFFSET getName
	call	WriteString

	xor		edx, edx
	mov		edx, OFFSET uName
	mov		ecx, 32
	call	ReadString

	call	CrLf
	mov		edx, OFFSET hi
	call	WriteString
	mov		edx, OFFSET uName
	call	WriteString
	call	CrLf

;----userIntroductions----;

	mov		edx, OFFSET instr1
	call	WriteString

	mov		edx, OFFSET instr2
	call	WriteString
	call	CrLf

;----getUserData----;

	mov		edx, OFFSET prompt
	call	WriteString
	call	ReadInt
	mov		numTerm, eax
	call	CrLf
	
; Checks to see that input is within range, and loops until it is

	cmp		eax, maxNum
	jg		getInput

	cmp		eax, 1
	jl		getInput

	jmp		moveOn

getInput:

	mov		edx, OFFSET errmsg
	call	WriteString
	call	ReadInt
	mov		numTerm, eax
	call	CrLf
	
	cmp		numTerm, maxNum
	jg		getInput

	cmp		eax, 1
	jl		getInput

	jmp		moveOn


;----Extra Credit: Column alignment----;

; After each term is calculated, this rudimentary switch statement produces the appropriate number of
; spaces needed after the term is printed, then returns to the loop to see if a new line is needed.

formatSpace:
	
	cmp		eax, 10
	jl		oneDigit
	cmp		eax, 100
	jl		twoDigit
	cmp		eax, 1000
	jl		threeDigit
	cmp		eax, 10000
	jl		fourDigit
	cmp		eax, 100000
	jl		fiveDigit
	cmp		eax, 1000000
	jl		sixDigit
	cmp		eax, 10000000
	jl		sevenDigit
	cmp		eax, 100000000
	jl		eightDigit
	cmp		eax, 100000000
	jg		gtEightDigit

oneDigit:

	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	call	WriteString
	jmp		checkLine

twoDigit:

	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	mov		edx, OFFSET spaces4
	call	WriteString
	jmp		checkLine

threeDigit:

	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	mov		edx, OFFSET spaces3
	call	WriteString
	jmp		checkLine


 fourDigit:

	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	mov		edx, OFFSET spaces2
	call	WriteString
	jmp		checkLine

 fiveDigit:

	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	mov		edx, OFFSET spaces1
	call	WriteString
	jmp		checkLine

 sixDigit:

 	mov		edx, OFFSET spaces5
	call	WriteString
	call	WriteString
	jmp		checkLine

 sevenDigit:

 	mov		edx, OFFSET spaces5
	call	WriteString
	mov		edx, OFFSET spaces4
	call	WriteString
	jmp		checkLine

 eightDigit:

 	mov		edx, OFFSET spaces5
	call	WriteString
	mov		edx, OFFSET spaces3
	call	WriteString
	jmp		checkLine

 gtEightDigit:

 	mov		edx, OFFSET spaces5
	call	WriteString
 	mov		edx, OFFSET spaces2
	call	WriteString
	jmp		checkLine

; Execution shifts to this point when user has chosen valid number of terms.
moveOn:

;----displayFibs----;

	mov		eax, 0
	mov		ebx, 1
	mov		ecx, numTerm

fibLoop:

; Calculates Fibonacci terms, prints them, increments the count of terms per line, then jumps to formatting 
	mov		tempFib, eax
	add		tempFib, ebx
	mov		eax, ebx
	mov		ebx, tempFib
	call	WriteDec
	inc		perLine 
	jmp		formatSpace

newLine:

	call	CrLf
	mov		perLine, 0

; Determines if five terms are on the line and jumps to newline for a CrLf call
checkLine:

	cmp		perLine, 5
	je		newLine
	
	loop	fibLoop


;----farewell----;

	call	CrLf
	call	CrLf

	mov		edx, OFFSET bye
	call	WriteString
	mov		edx, OFFSET uname
	call	WriteString
	call	CrLf
	call	CrLf

	exit	; exit to operating system
main ENDP

; (no additional procedures)

END main