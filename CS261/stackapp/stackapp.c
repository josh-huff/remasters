/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

// A helper for isBalanced (mostly to factor out redundancy)
int isProperlyNested(DynArr* stack, char expected){

    char actual = topDynArr(stack);
    popDynArr(stack);
    return actual == expected;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
    DynArr* braces_stack = newDynArr(10);   
    char current = nextChar(s);
    int no_early_exit = 1;
 
    while(current != '\0'){    

        switch(current){ 
            case '(':
            case '{':
            case '[':
                pushDynArr(braces_stack, current);
                break;              
            case ')':
                no_early_exit = isProperlyNested(braces_stack, '(');
                break;
            case '}': 
                no_early_exit = isProperlyNested(braces_stack, '{');
                break;
            case ']':
                no_early_exit = isProperlyNested(braces_stack, '[');
                break;
        }
        current = (no_early_exit) ? nextChar(s) : '\0';
    }
  
    return isEmptyDynArr(braces_stack) && no_early_exit;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	

	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

