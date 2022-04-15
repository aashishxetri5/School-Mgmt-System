/*
Name of class should be Same as the file name.

This shall have the properties/details of a teacher/staff. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/
#include<iostream>
#include"Person.cpp"

using namespace std;

class Staff : public Person{
    string subject;
    int salary;
public:
    Staff() {}
    
    Staff(int userId, string firstname, string lastname, string email, string address, string phone_num, string subject, int salary) : 
    Person(userId, firstname, lastname, email, address, phone_num) {
        this -> subject = subject;
        this -> salary = salary;
    }

    Staff(const Staff &staff) {
        userId = staff.Person::userId;
        firstname = staff.Person::firstname;
        lastname = staff.Person::lastname;
        email = staff.Person::email;
        address = staff.Person::address;
        phone_num = staff.Person::phone_num;
        salary = staff.salary;
        subject = staff.subject;
    }

    //setter function for each data members
    void setSubject(string subject);

    string getSubject();

    void setSalary(int salary);

    int getSalary();

};

void Staff::setSubject(string subject){
    this -> subject = subject;
}

string Staff::getSubject(){
    return subject;
}

void Staff::setSalary(int salary){
    this -> salary = salary;
}

int Staff::getSalary(){
    return salary;
}
