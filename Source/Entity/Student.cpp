/*
Name of class should be Same as the file name.

This shall have the properties/details of a student. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/
#ifndef STUDENT_CPP
#define STUDENT_CPP
#include <string>
#include "Person.cpp"

class Student : public Person {
    int grade; //Current Standard
    string dob = "";

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

    string getDate(); //Returns the date in string format

    //read from the file and write to the obj
    friend istream& operator >> (istream& stream, Student &sObj);

    //write to the file by reading from the obj
    friend ostream& operator << (ostream& stream, Student &sObj);

    void display_data();
};

void Student::display_data(){
    cout << "\n\tID: "<< userId;
    cout << "\tFirst Name: "<< firstname;
    cout << "\tLast Name: "<< lastname;
    cout << "\tEmail: "<< email;
    cout << "\tAddress: "<< address;
    cout << "\tcontact number: "<< phone_num;
    cout << "\tGrade: "<< grade;
    cout << "\tDate [DD/MM/YY]: "<< dob;
    cout << "\n";
}

void Student::setGrade(int grade){
    this->grade = grade;
}

int Student::getGrade() {
    return grade;
}

void Student::setDate(string dob) {
    this->dob = dob;
    cout << "from setter: " << dob << endl;
}

string Student::getDate() {
    //This returns the date in string type in format MM-DD-YYYY
    return dob;
}

//This overloaded operatior reads the content from the file and sets into the student object.
istream& operator >> (istream& stream, Student &sObj){
    stream >> sObj.userId;
    stream >> sObj.firstname;
    stream >> sObj.lastname;
    stream >> sObj.address;
    stream >> sObj.email;
    stream >> sObj.phone_num;
    stream >> sObj.grade;
    stream >> sObj.dob;

    return stream;
}

//This overloaded operatior writes the content of student object received via parameter to the file.
ostream& operator << (ostream& stream, Student &sObj){
    stream << sObj.userId << "\t"; //unique
    stream << sObj.firstname<< "\t";
    stream << sObj.lastname << "\t";
    stream << sObj.address << "\t";
    stream << sObj.email << "\t";
    stream << sObj.phone_num << "\t";
    stream << sObj.grade << "\t";
    stream << sObj.dob<<"\n";
     
    return stream;
}

#endif