/*
Name of class should be Same as the file name.

This shall have the properties/details of a student. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/

#include <iostream>
#include <string>
#include "Person.cpp"

class Student {
    int grade; //Current Standard
    unsigned short int day, month, year; //For DOB

public:

    Student() {}

    // This constructor can be used when passing the data to the other functions while adding the new data.
    Student(int grade, unsigned short int day, unsigned short int month, unsigned short int year) {
        this->grade = grade;
        this->day = day;
        this->month = month;
        this->year;
    }

    //Copy constructor. Copies value from one object to other.
    Student(const Student &student) {
        grade = student.grade;
        day = student.day;
        month = student.month;
        year = student.year;
    }

    void setGrade(int grade); //Sets the the grade of student

    int getGrade(); //Returns the Grade of the student
    
    //Accepts the date in partitioned form
    void setDate(unsigned short int day, unsigned short int month, unsigned short int year);

    std::string getDate(); //Returns the date in string format

};

void Student::setGrade(int grade){
    this->grade = grade;
}

int  Student::getGrade() {
    return grade;
}

void  Student::setDate(unsigned short int day, unsigned short int month, unsigned short int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

std::string  Student::getDate() {
    //This returns the date in string type in format MM-DD-YYYY
    return ( std::to_string(month) +"-" + std::to_string(day) + "-" + std::to_string(year) );
}