/*********************************************************************
** Author: Josh Huff
** Date: October 19, 2016
** Description: Project 4.c -- Student Class -- models student names and test scores
*********************************************************************/

#ifndef STUDENT_HPP
#define STUDENT_HPP

class Student {

    private:
        std::string name;
        double score;
    
    public:
        Student(std::string name, double score);
        std::string getName();
        double getScore();
};

#endif
