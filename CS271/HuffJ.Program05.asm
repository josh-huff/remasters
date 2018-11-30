TITLE Program 5 - Sorting Random Numbers (HuffJ.Project05.asm)

; Author: Josh Huff
; Course / Project ID: CS 271 / Project 5	Date: Mar 6, 2017 (used grace days on Canvas)
; Description: Using MASM to generate, sort, and display an array of random numbers

INCLUDE Irvine32.inc

.const

; Declared constants
	
	max		EQU		200		; Maximum user input
	min		EQU		10		; Minimum user input
	lo		EQU		100		; Lowest possible randomly generated integer
	hi		EQU		999		; Highest possible randomly generated integer
	range	EQU		900		; range = hi - lo + 1
	maxLn	EQU		10		; Maximum elements per displayed line

.data

	request	DWORD	?											; User input number of integers to be created and sorted	
	array	DWORD	MAX DUP(?)									; An array for storing and sorting integers
	tUnSort	BYTE	"The unsorted random numbers:", 13, 0		; Unsorted title
	tSort	BYTE	"The sorted list:", 13, 0					; Sorted title

.code

main PROC

	call	introduction	; No arguments necessary

	push	OFFSET request
	call	getData			; Passing request to getData

	call	Randomize		; Calling Randomize once to seed

	push	request
	push	OFFSET array
	call	fillArray		; Passing request and array to fillArray

	push	request
	push	OFFSET array
	push	OFFSET tUnSort
	call	displayList		; Passing request, array, and tUnSort to displayList

	push	request
	push	OFFSET array
	call	sortList		; Passing request and array to sortList

	push	request
	push	OFFSET array
	call	displayMedian	; Passing request and array to displayMedian

	push	request
	push	OFFSET array
	push	OFFSET tSort
	call	displayList		; Passing request, array, and tSort to displayList


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

	intro	BYTE	"Sorted Random Integers          Programmed by Josh Huff", 13, 10, 0

.code

	mov		edx, OFFSET intro
	call	WriteString
	call	CrLf

	ret

introduction ENDP

;----------------------------------------------------------------------
getData PROC
; Prompts user for number of random integers to be generated and validates it
; Receives: request (required label given to user-input number of integers to be generated)
; Returns: request (populated with a valid integer)
;----------------------------------------------------------------------
.data

	instr1	BYTE	"This program generates random numbers in the range [100 .. 999],", 13, 10, 0
	instr2	BYTE	"displays the original list, sorts the list, and calculates the", 13, 10, 0
	instr3	BYTE	"median value. Finally, it displays the list sorted in descending order.", 13, 10, 10, 0
	prompt	BYTE	"How many numbers should be generated? [10 .. 200]: ", 0
	rngErr	BYTE	"Invalid input", 10, 0

.code

	; ---- Set up stack frame and store the value of request in ebx
	push	ebp
	mov		ebp, esp
	mov		ebx, [ebp + 8]

	; ---- Display Instructions
	mov		edx, OFFSET instr1
	call	WriteString
	mov		edx, OFFSET instr2
	call	WriteString
	mov		edx, OFFSET instr3
	call	WriteString

	; ---- Validate user's input
	mov		edx, OFFSET prompt
	call	WriteString

	call	ReadInt

retest:			; Execution goes here if user input is out of range and needs retesting

	cmp		eax, max
	jg		outOfRange
	
	cmp		eax, min
	jl		outofRange

	call	CrLf

	jmp		inRange
	
outOfRange:		; Execution goes here if the cmp to eax exceeds max or min 

	mov		edx, OFFSET rngErr
	call	WriteString
	mov		edx, OFFSET prompt
	call	WriteString
	call	ReadInt
	jmp		retest	

inRange:		; Execution goes here if eax's content is within bounds of valid input

	mov		[ebx], eax			; Once valid, copy the contents of eax to the value at request's address

	pop		ebp

	ret		4					; Clean request from the stack

getData ENDP

;----------------------------------------------------------------------
fillArray PROC
; Populates an array with a requested number of random integers
; Receives: array, request
; Returns: array (populated with integers)
;----------------------------------------------------------------------
.data

	; No local data labels

.code

	; ---- Set up stack frame
	push	ebp
	mov		ebp, esp

	mov		ecx, [ebp + 12]		; Put user's requested number of integers into ecx
	mov		edi, [ebp + 8]		; Put address of array into edi

	; ---- Random number generation 
	; ---- (written based off lecture 20's pseudocode)

nextElement:		; Execution jumps here after successful completion of loop below

	mov		eax, range			; Place range constant (900) in eax
	call	RandomRange			; call RandomRange
	add		eax, lo				; Add lo constant (100) to eax 

	mov		[edi], eax			; Place pseudorandom 100-999 int into edi 
	add		edi, 4				; Move to next element location
	loop	nextElement

	pop		ebp

	ret		8					; Clean request and array from stack

fillArray ENDP

;----------------------------------------------------------------------
sortList PROC
; Uses bubble sort to order the array passed to it
; Receives: request, array
; Returns: sorted array (in descending order)
;----------------------------------------------------------------------
.data

	; No local labels

.code

	; ---- BubbleSort, adapted from textbook example

	; ---- Set up stack frame
	push	ebp
	mov		ebp, esp

	mov		ecx, [ebp + 12]		; Put user's requested number of integers into ecx
	
	dec		ecx					; Prime the loop

Loop1:
	
	push	ecx					; Preserve the "outer" count
	mov		esi, [ebp + 8]		; Store the array address in esi

Loop2:

	mov		eax, [esi]			; Put the value of the current array element in eax 
	cmp		[esi+4], eax		; Check to see if its right neighbor is larger
	jl		Loop3
	xchg	eax, [esi+4]		; If so, exchange them
	mov		[esi], eax			 

Loop3:							; Execution jumps here when an exchange is not necessary

	add		esi, 4				; Advance the pointer
	loop	Loop2				; Continue to loop until current element is in place

	pop		ecx					; Restore "outer" count and move on to next element
	loop	Loop1

	pop		ebp

	ret		8					; Clean up the stack

sortList ENDP

;----------------------------------------------------------------------
displayMedian PROC
; Finds and displays the median of an array of integers
; Receives: array, request
; Returns: n/a
;----------------------------------------------------------------------
.data

	median		BYTE	"The median is ", 0		; Median display text
	medEnd		BYTE	".", 13, 10, 0			; More median display text

.code

	; ---- Set up stack frame
	push	ebp
	mov		ebp, esp

	mov		esi, [ebp + 8]		; Put address of array into esi
	mov		eax, [ebp + 12]		; Put user's requested number of integers into eax

	; ---- Prepare edx and ebx to halve eax (the value of request)
	mov		ebx, 2
	xor		edx, edx
	div		ebx

	; ---- If there is a remainder of 1 in edx, the median element already exists 
	cmp		edx, 1
	jne		medianArithmetic

	; ---- Contents of eax are equal to the median's logical index 
	mov		ebx, 4				
	mul		ebx					; Multiply by 4, per DWORD's byte value
	add		esi, eax			; Add result to esi -- result is median's actual index
	mov		eax, [esi]			; Dereference esi and put to eax
	jmp		display

medianArithmetic:		; Execution jumps here if a median needs to be created

	; ---- Find "lower" half of median
	dec		eax					; Decrement to "lower" half of median
	mov		ebx, 4
	mul		ebx					; Multiply by 4, per DWORD's byte value
	add		esi, eax			; Add result to esi -- result is lower half of median's actual index
	mov		eax, [esi]			; Dereference esi and put to eax

	; ---- Find "higher" half of median
	add		eax, [esi + 4]		; Dereference "higher" half of median and add to eax
	
	; ---- Prepare edx and ebx to halve eax (the value of "high half" and "low half" of median)
	mov		ebx, 2
	xor		edx, edx
	div		ebx		

display:				; Execution jumps here if a median is already present in the array


	; ---- Print the median strings with the contents of eax between them
	call	CrLf
	mov		edx, OFFSET median
	call	WriteString
	
	call	WriteDec

	mov		edx, OFFSET medEnd
	call	WriteString

	pop		ebp

	ret		8			; Clean up the stack

displayMedian ENDP

;----------------------------------------------------------------------
displayList PROC
; Displays the contents of an array of integers and gives it a title
; Receives: array, request, title
; Returns: n/a
;----------------------------------------------------------------------
.data

	numPerLine	BYTE	0			; The current number of ints per line
	spaces		BYTE	"   ", 0	; Adds three spaces

.code

	; ---- Set up stack frame
	push	ebp
	mov		ebp, esp

	mov		ecx, [ebp + 16]		; Put user's requested number of integers into ecx
	mov		esi, [ebp + 12]		; Put address of array into esi
	mov		edx, [ebp + 8]		; Put title into edx


	; ---- Display status of array being displayed (sorted or not)
	call	CrLf
	call	WriteString


	; ---- Iterate through array and print each element
	; ---- (written with help from lecture 20)

	inc		ecx					; "Primes" the loop, because newLine causes the counter to decrement once too early

newLine:			; Execution jumps here if the numPerLine meets or exceeds the maximum

	call	CrLf
	mov		numPerLine, 0
	jmp		returnToLoop

nextElement:		; Execution jumps here after successful completion of loop below

	; ---- Write array element value and formatting to console
	mov		eax, [esi]			
	call	WriteDec
	mov		edx, OFFSET spaces
	call	WriteString			

	; ---- Update esi position and count of elements per line, create a newline if necessary, then return to loop
	add		esi, 4
	inc		numPerLine
	cmp		numPerLine, maxLn
	jge		newLine

returnToLoop:

	loop	nextElement
	call	CrLf	

	pop		ebp

	ret		12					; Clean up stack

displayList ENDP

END main