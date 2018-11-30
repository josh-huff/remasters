#include <iostream>
#include <cmath>
#include "Student.hpp"

// Finds standard deviation of students' scores
// The Student class is included in the repo for the sake of this function
double stdDev(Student* studentArray[], int size){

    double mean = 0.0;
    double sqrd_dev_sum = 0.0;

    // Accumulate all student scores and find the class mean
    for (int i = 0; i < size; i++){
        mean += studentArray[i]->getScore();
    }
    mean /= size;

    // Accumulate the squared differences of scores and mean to find variance
    for (int i = 0; i < size; i++){   
        sqrd_dev_sum += pow(studentArray[i]->getScore() - mean, 2.0);
    }

    // Standard deviation is the square root of variance
    return sqrt(sqrd_dev_sum / size);
}

int main(){
    
    // Student objects for testing the stdDev function
    Student s("huff", 65);
    Student j("jessica", 100);
    Student c("cj", 100);
    Student n("nicole", 100);   
    Student b("billy", 50);    

    Student* localArray[] = {&s, &j, &c, &n, &b};
    std::cout << "Standard deviation is: " << stdDev(localArray, 5) << "\n";
 
    return 0;
}

/*
#include <string>
#include "Student.hpp"
#include <cmath>

double stdDev(*ptrStudents[], int size)
{

    double mean;
    double meanSquared;
    double meanOfDiff;

    for (int count = 0; count < size; count++)
    {
        mean += &ptrStudents[count];
    }
 
    mean /= size;

    for (int count = 0; count < size; count++)
    {   
        meanSquared = pow(&ptrStudents[count] - mean, 2.0);
        meanSquared += meanOfDiff;
    }

    return sqrt(meanOfDiff);
}
*/

