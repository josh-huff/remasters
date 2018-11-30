#include <string>
#include <iostream>
#include <cmath>

int binToDec_helper(std::string bin_rep, int len){

    // Base case: 
    if(len == 1){
        return (bin_rep[0] == '1') ? 1 : 0;
    }

    // Recursive case ("chopped up" for readability)
    int current_bit = 0;
    len--;
    if(bin_rep[0] == '1'){
        current_bit = pow(2, len);    
    }
     
    return current_bit + 
            binToDec_helper(bin_rep.substr(1), len);
}

int binToDec(std::string bin_rep){
    return binToDec_helper(bin_rep, bin_rep.length());
}

std::string decToBin_helper(int dec_rep, std::string working_str){

    // Base Cases
    if(dec_rep == 1){
        return "1" + working_str;
    }
    if(dec_rep == 0){
        return "0" + working_str;
    } 

    // Recursive Case
    if(dec_rep % 2 == 0){
        working_str = "0" + working_str;
    } else{
        working_str = "1" + working_str;
    }
    
    return decToBin_helper(dec_rep / 2, working_str);
}

std::string decToBin(int dec_rep){
    return decToBin_helper(dec_rep, "");
}

int main(){

    std::string binStr = "1111";
    std::cout << "Output from binToDec is : " << binToDec(binStr) << "\n";

    
    int decVal = 9;
    std::cout << "Output from decToBin is : " << decToBin(decVal) << "\n";

    return 0;
}

/*********************************************************************
** Author: Josh Huff
** Date: November 2, 2016
** Description: Project 6.a -- converter.cpp -- Recursive functions 
** that take a C++ string representing a value in binary, 
** and convert it to an integer (and vice versa). 
********************************************************************

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

********************************************************************
** Description: binToDec (recursive function) -- 
** Accumulates the 1 values in the string, 
** recursively raising the exponent.  
********************************************************************
int binToDec(string binaryValue, int strMax, int index)
{
    int total = 0;

    if (strMax > -1)
    {
        if (binaryValue[index] == '1')
            {
                total = pow(2, strMax);
            }

    // Set new values for upcoming recursive call
    strMax--;
    index++;

    return total + binToDec(binaryValue, strMax, index);    
    }//end outer if statement
}

********************************************************************
** Description: binToDec (helper function/main-facing function) -- 
** Hides the fact that it needs to pass integer values to be recursive.
** It comes second because function overloading only works if the function
** being called is defined.
**  
** This was my Zen enlightenment moment for using function prototypes.
********************************************************************
int binToDec(string binaryValue)
{ 
    int strMax = binaryValue.length() - 1;
    int index = 0;   

    return binToDec(binaryValue, strMax, index);
}

string decToBin(string input)
{
    string resultValue;
    resultValue += input;
    return resultValue;
}

string decToBin(int decimalValue)
{
    string output, result; 

    if ((decimalValue / 2) != 0)
    {
        decToBin(decimalValue / 2);
    }

    if (decimalValue % 2 == 0)
    {
        output = "0";
    }
    
    if (decimalValue % 2 == 1)
    {
        output = "1";
    }

    string binaryValue = "";

    binaryValue += decToBin(output);

    return binaryValue;
}

int main()
{
    string binStr = "1111";
    int decOutput = binToDec(binStr);
    cout << "Output from binToDec is : " << decOutput << endl;

    
    int decVal = 72;
    string binOutput = decToBin(decVal);
    cout << "Output from decToBin is : " << binOutput << endl;

    return 0;
}
*/
