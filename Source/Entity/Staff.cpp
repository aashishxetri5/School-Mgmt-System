/*
Name of class should be Same as the file name.

This shall have the properties/details of a teacher/staff. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/
#ifndef STAFF_CPP
#define STAFF_CPP
#include"Person.cpp"
#include <iomanip>

using namespace std;

class Staff : public  Person{
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
        userId = staff.userId;
        firstname = staff.firstname;
        lastname = staff.lastname;
        email = staff.email;
        address = staff.address;
        phone_num = staff.phone_num;
        salary = staff.salary;
        subject = staff.subject;
    }

    //setter function for each data members
    void setSubject(string subject);

    string getSubject();

    void setSalary(int salary);

    int getSalary();

    //write to the file
    friend ostream& operator << (ostream& stream, Staff sObj);

    //read from the file
    friend istream& operator >> (istream& stream, Staff &sObj);

    //display the data 

    void display_data();

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


//This overloaded operator reads the content from the file and sets into the staff object.
ostream& operator << (ostream& stream, Staff sObj){
    stream << sObj.userId << "\t";
    stream << sObj.firstname << "\t";
    stream << sObj.lastname << "\t";
    stream << sObj.email << "\t";
    stream << sObj.address << "\t";
    stream << sObj.phone_num << "\t";
    stream << sObj.salary << "\t";
    stream << sObj.subject << "\n";

    return stream;
}

//This overloaded operator writes the content of staff object received via parameter to the file.
istream& operator >> (istream& stream, Staff &sObj){
    stream >> sObj.userId;
    stream >> sObj.firstname;
    stream >> sObj.lastname;
    stream >> sObj.email;
    stream >> sObj.address;
    stream >> sObj.phone_num;
    stream >> sObj.salary;
    stream >> sObj.subject;

    return stream;
}

void Staff::display_data(){
    
    cout << setw(10) << left << to_string(userId);
    cout << setw(22) << left << getFullname();
    cout << setw(33) << left << email;
    cout << setw(18) << left << address;
    cout << setw(16) << left << phone_num;
    cout << setw(16) << left << subject;
    cout << setw(10) << left << "Rs. " + to_string(salary) << "\n" ;

    for(int i = 0; i < 127; i++){
        cout << "-";
    }
    cout << "\n";

}
#endif
