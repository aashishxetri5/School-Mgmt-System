/*
Name of class should be Same as the file name.

This shall have the properties/details of a student. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/

#include <string>
#include "Person.cpp"

class Student : public Person {
    int grade; //Current Standard
    string dob;

public:

    Student() {}

    /*
    This constructor can be used when passing the data to the other functions while adding the new data.
    Recevies all the data of a student and passes the data other than the data members of this class to the parent class.
    */
    Student(int userId, string firstname, string lastname, string email, string address, string phone_num, 
    int grade, string dob) : Person(userId, firstname, lastname, email, address, phone_num) {

        this->grade = grade;
        this->dob = dob;
    }

    //Copy constructor. Copies value from one object to other.
    Student(const Student &student) {
        userId = student.userId;
        firstname = student.firstname;
        lastname = student.lastname;
        email = student.email;
        address = student.address;
        phone_num = student.phone_num;
        grade = student.grade;
        dob = student.dob;
    }

    void setGrade(int); //Sets the the grade of student

    int getGrade(); //Returns the Grade of the student
    
    //Accepts the date in partitioned form
    void setDate(string);

    std::string getDate(); //Returns the date in string format

};

void Student::setGrade(int grade){
    this->grade = grade;
}

int Student::getGrade() {
    return grade;
}

void Student::setDate(string dob) {
    this->dob = dob;
}

string Student::getDate() {
    //This returns the date in string type in format MM-DD-YYYY
    return dob;
}