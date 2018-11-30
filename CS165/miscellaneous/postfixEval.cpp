#include <iostream>
#include <stack>

// Take a C-style string parameter representing a postfix expression
// Return the value of the expression as a double.
double postfixEval(char expr[]){

    std::stack<double> pf_stack;
    std::string operand_buffer;
    char look_ahead;
    double operand1, operand2, value;

    // Iterate through array until hitting \0    
    while(*expr){

        switch(*expr){ 
            case ' ':
                break;        

            // When an operator is encountered, apply it to the top two 
            // stack elements and replace them with the result.
            case '+':
            case '-':
            case '*':
            case '/':
                operand1 = pf_stack.top();
                pf_stack.pop();

                operand2 = pf_stack.top();
                pf_stack.pop();
               
                if(*expr == '+'){ value = operand2 + operand1; }
                if(*expr == '-'){ value = operand2 - operand1; }
                if(*expr == '*'){ value = operand2 * operand1; }
                if(*expr == '/'){ value = operand2 / operand1; }
              
                pf_stack.push(value);
                break;
            

            default:
                operand_buffer += *expr;
                look_ahead = *(expr + 1);
                
                // If the next character is not also a digit or decimal,
                // the number is complete and ready to be pushed.                
                if( isdigit(look_ahead) || look_ahead == '.' ){
                    break;
                } else{
                    pf_stack.push( std::stod(operand_buffer) );
                    operand_buffer = ""; 
                }
        }

        expr++;
    }

    // The result of evaluation should be the last item in the stack    
    return pf_stack.top();
}

int main(){

    char testArray[] =  "10 2 8 * + 3 -";
    char testArray2[] = "25 12 7 - 2 * /";
    char testArray3[] = "25.5 12.5 + 2 /";
    char testArray4[] = "2.5 3.5 *";
    char testArray5[] = "4.3 5.0 +";

    std::cout << postfixEval(testArray)  << "\n";
    std::cout << postfixEval(testArray2) << "\n"; 
    std::cout << postfixEval(testArray3) << "\n";
    std::cout << postfixEval(testArray4) << "\n";  
    std::cout << postfixEval(testArray5) << "\n";
    return 0;
}
/*
********************************************************************
** Author: Josh Huff
** Date: November 23, 2016
** Description: Project 9.b -- postfixEval.cpp -- Converts a postfix expression to infix 
********************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>

using namespace std;

double postfixEval (char postfixExp[])
{
    // Local variables 
    std::string expression = postfixExp;
    int size = expression.length();

    double convertedChar,
           operand1, 
           operand2;

    stack < double, vector<double> > doubleStack;

    // Iterates through expression
    for(int count = 0; count < size; count++)
    {   
        // If the character is an operator, it performs the necessary operation
        if (expression[count] == '+' ||
            expression[count] == '-' ||
            expression[count] == '*' ||
            expression[count] == '/')
        {
            operand1 = doubleStack.top();
            doubleStack.pop();

            operand2 = doubleStack.top();
            doubleStack.pop();
            
            switch (expression[count])
            {
                case '+':
                    convertedChar = operand2 + operand1;
                    break;
               
                case '-':
                    convertedChar = operand2 - operand1;    
                    break;
   
                case '*':
                    convertedChar = operand2 * operand1;
                    break;

                case '/':
                    convertedChar = operand2 / operand1;
                    break;
            }// end of switch

            doubleStack.push(convertedChar);
            expression[count] = ' ';
        
        }// end of If -- operators

        // If the character is a digit, it is converted to a double and added to the stack
        if (isdigit(expression[count]))
        {
            convertedChar = atof(expression.c_str());
            doubleStack.push(convertedChar);

            // An infinite loop writes over all characters in the string until it hits a non-decimal, non-digit character.
            for (int i = count; ; i++)
            {
                if(expression[i] == '.' || isdigit(expression[i]))
                {
                    expression[i] = ' ';
                    continue;
                }

                break;   
            }
            
        }// end of If -- digits         
    }// End of for loop -- Iterating through expression

    return doubleStack.top();
}


int main()
{
    char testArray[] =  {'1', '0', ' ', '2', ' ', '8', '*', '+', '3', '-'};
    char testArray2[] = {'2', '5', ' ', '1', '2', ' ', '7', ' ', '-', ' ', '2', '*', '/'};
    char testArray3[] = {'2', '5', '.', '5', ' ', '1', '2', '.', '5', ' ', '+', ' ', '2', '/'};
    char testArray4[] = {'2', '.', '5', ' ', '3', '.', '5', '*'};

    double testResult;

    testResult = postfixEval(testArray);
    std::cout << testResult << std::endl;

    testResult = postfixEval(testArray2);
    std::cout << testResult << std::endl;

    testResult = postfixEval(testArray3);
    std::cout << testResult << std::endl;

    testResult = postfixEval(testArray4);
    std::cout << testResult << std::endl;


    return 0;
}
*/
