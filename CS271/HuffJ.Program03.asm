TITLE Program 3 - Integer Accumulator (HuffJ.Project03.asm)

; Author: Josh Huff
; Course / Project ID: CS 271 / Project 3	Date: Feb 12, 2017
; Description: Using MASM to accumulate negative integers and display their sum and average

INCLUDE Irvine32.inc

.const

; Declared constants
	
	lowLim	EQU		-100 ; Minimal user input

.data

; Introductory strings

	intro	BYTE	"Welcome to the Integer Accumulator by Josh Huff", 13, 10, 0
	ec1		BYTE	"EC: Numbers lines during user input", 13, 10, 0

; Prompts and user input for name and negative terms

	getName	BYTE	"What is your name? ", 0
	uName	BYTE	33 DUP(0)
	hi		BYTE	"Hello, ", 0
	instr1	BYTE	"Please enter numbers in [-100, -1].", 13, 10, 0
	instr2	BYTE	"Enter a non-negative number when you are finished to see results.", 13, 10, 0
	prompt	BYTE	"Enter number: ", 0
	validN1	BYTE	"You entered ", 0
	curTerm	DWORD	?
	numTerm	DWORD	?
	validN2 BYTE	" valid numbers.", 0
	sumMsg	BYTE	"The sum of your valid numbers is ", 0
	sumTerm	DWORD	?
	avgMsg	BYTE	"The rounded average is ", 0
	avg		DWORD	?
	dzErr	BYTE	"Division by zero is undefined. Please try again.", 13, 10, 0

	; Extra Credit: numbering the lines during user input
	lnMsg	BYTE	"Line ", 0
	lnMsg2	BYTE	" - ", 0
	lnCnt	DWORD	?

; farewell

	bye		BYTE	"Thank you for playing Integer Accumulator! It's been a pleasure to meet you, ", 13, 10, 0

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

	mov		edx, OFFSET hi
	call	WriteString
	mov		edx, OFFSET uName
	call	WriteString
	call	CrLf
	call	CrLf

;----User Instructions----;

	mov		edx, OFFSET instr1
	call	WriteString

	mov		edx, OFFSET instr2
	call	WriteString

	; Initializes line count
	mov		lnCnt, 1

;----Get Data----;
getInput:
	
	; Prints line count, then prompt, then updates line count after input is received
	mov		edx, OFFSET lnMsg
	call	WriteString

	mov		ecx, lnCnt
	mov		eax, ecx
	call	WriteDec

	mov		edx, OFFSET lnMsg2
	call	WriteString

	mov		edx, OFFSET prompt
	call	WriteString
	call	ReadInt
	inc		lnCnt
	
; Checks to see that input is within range, and either processes it or moves to print results.

	; If the input is too low, execution jumps to the beginning so the user can try again.
	cmp		eax, lowLim
	jl		getInput

	; If user inputs a non-negative number, execution shifts to displaying the results
	cmp		eax, -1
	jg		printResults


;----Process Input----;
	
	; If input makes it to this point, it can be accumulated and the count is incremented.
	mov		curTerm, eax
	mov		ebx, sumTerm
	add		ebx, curTerm
	mov		sumTerm, ebx
	inc		numTerm

	jmp		getInput

;----Print Results----;

; Execution shifts to this point when user has chosen to stop by entering a non-negative number.
printResults:

	; Jumps to an error message if number of terms is zero
	cmp		numTerm, 0
	je		divideByZero

	; Displaying the total number of valid terms
	mov		edx, OFFSET validN1
	call	WriteString
	
	mov		eax, numTerm
	call	WriteDec

	mov		edx, OFFSET validN2
	call	WriteString
	call	CrLf

	; Displaying the sum of the valid terms
	mov		edx, OFFSET sumMsg
	call	WriteString
	
	mov		eax, sumTerm
	call	WriteInt
	call	CrLf

	; Finding the average
	mov		edx, OFFSET avgMsg
	call	WriteString
	mov		eax, sumTerm
	mov		ebx, numTerm
	cdq
	idiv	ebx
	call	WriteInt
	call	CrLf

	; Skip the divide-by-zero error message to the end
	jmp		farewell

divideByZero:

	; Execution arrives here if user did not enter any valid terms

	call	CrLf
	mov		eax, 0
	mov		edx, OFFSET dzErr
	call	WriteString
	call	CrLf


;----Farewell----;
farewell:

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