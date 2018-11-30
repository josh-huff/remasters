#include <iostream>

double fallDistance(double seconds){
    return 0.5 * 9.8 * seconds * seconds;
}

int main(){

    double time;

    std::cout << "Enter time in seconds: " << "\n";
    std::cin >> time;
  
    std::cout << "Fall distance is " << fallDistance(time) << " meters.\n";
    
    return 0;
}

/*********************************************************************
** Author: Josh Huff
** Date: October 5, 2016
** Description: Project 2.d -- fallDistance -- Takes a number of seconds (expressed as a double) as a parameter and returns the distance (in meters) an object falls using the 1/2gt^2 freefall formula 
********************************************************************

#include <cmath>


double fallDistance(double seconds)
{
    const double g = 9.8;
    double distance;

    distance = 0.5 * g * (pow(seconds, 2));

    return distance;
}

*/
