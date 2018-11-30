/*********************************************************************
** Description: Implementation of class "Student"
*********************************************************************/

#include <string>
#include "Student.hpp"

Student::Student(std::string inputName, double inputScore)
{
    name = inputName;
    score = inputScore;
}

std::string Student::getName()
{
    return name;
}

double Student::getScore()
{
    return score;
}

