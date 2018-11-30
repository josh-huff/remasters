#include <iostream>

// Determine number of steps in a positive integer's hailstone sequence.
// (Precondition: "start" is a positive int)
int hailstone(int current_num){

    int steps = 0;

    while (current_num != 1){

        steps++;

        if (current_num % 2 == 0){
            current_num /= 2;
            continue;
        }

        current_num = (current_num * 3) + 1;
    }

    return steps;
}

int main(){

    int hs_input;

    // Simple test: No input validation.
    std::cout << "Enter a positive integer: ";
    std::cin >> hs_input;

    std::cout << "\nThe hailstone sequence for " << hs_input << " is " 
            << hailstone(hs_input) << " steps.\n";

    return 0;
}


/*********************************************************************
 * ** Author: Josh Huff
 * ** Date: October 5, 2016
 * ** Description: Project 2.f -- Hailstone Sequence -- Takes a positive integer and halves it if it's even, or triples it and adds one if it's odd, then repeats. This function returns the number of iterations necessary for the integer to be equivalent to 1.
 * ********************************************************************

#include <iostream>

using namespace std;

int hailstone(int posInt)
{

    int stepCount;

    // If the starting value is 1, the function returns zero and exits immediately.
    if (posInt == 1)
    {
        return 0;
    }


    while (posInt != 1) // Loops until the integer becomes equivalent to 1
    {

        // If the integer is currently even, it is halved. The loop count is updated.
        if (posInt % 2 == 0)
        {
            posInt /= 2;
            stepCount++;
        }

        // If the integer is odd, it is tripled then increased by one. The loop count is updated.
        else
        {
            posInt *= 3;
            posInt++;
            stepCount++;
        }
    }

    return stepCount; // When the loop exits, the function returns the number of iterations.
}


int main()
{
    int hailstoneInput;

    cout << "Enter a positive integer: " << endl;
    cin >> hailstoneInput;

    int result = hailstone(hailstoneInput);

    cout << "The hailstone sequence for " << hailstoneInput << " is " << result << " steps." << endl;
    return 0;
}
*/
