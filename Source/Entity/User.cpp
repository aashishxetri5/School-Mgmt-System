/*
Name of class should be Same as the file name.

This shall have the properties/details for a user to be logged in. 
Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members.

/*

/*
    User
    parent might teacher, student, or staff
    
    Features of User:
    Access:
        1. Email
        2. Password

    Properties:
        Generally a user is either
        1.Admin
        2.Teacher
        3.Students
        4.Staffs

        depending upon its inheritance.

    Functions:
        getter
        setters
    
    Possible features:
    * Password change feature
        -Old pass
        -New pass

*/ 
#include "../View/Menu.cpp"
#include "Student.cpp"
#include "Staff.cpp"
#include <iostream>
#include <string>

using namespace std;

class User{
    string username, password, userType;

public:
    User(){
        userType = "";
    }

    User(string uname, string pwd){
        username = uname;
        password = pwd;
    }
    
    User(const User &userObj){
        username = userObj.username;
        password = userObj.password;
        userType = userObj.userType;
    }
    
    //setter
    void set_username();
    void set_password(string*);
    void setUserType(string);
    
    //getter 
    string get_username();
    string get_password();
    string getUserType();

    //write to the file
    friend ostream& operator << (ostream &stream, User uObj);

    //read from the file
    friend istream& operator >> (istream &stream, User &uobj);
    
    void user_data();
    void register_user();
    
};


void User::set_username() {
    cin >> this->username;
}

void User::set_password(string *pwd) {
    password = *pwd;
}

void User::setUserType(string usertype) {
    userType = usertype;
}

string User::get_username() {
    return username;
}

string User::get_password() {
    return password;
}

string User::getUserType() {
    return userType;
}


//writes the data members of the user object to the file 
ostream& operator << (ostream& stream, User uObj){

    stream << uObj.userType << "\n";
    stream << uObj.username << "\t"; 
	stream << uObj.password << "\t";
	return stream;
}


//read from the file and sets the value of the Object
istream& operator >> (istream& stream, User &uObj){

    stream >> uObj.userType;
    stream >> uObj.username;
    stream >> uObj.password;

}

void User::user_data(){

        Person person;

        string temp_data, temp_data2, temp_data3;
        int grade;

        cout << "First Name: ";
        cin >> temp_data;
        temp.setFirstname(temp_data);

        cout << "Last Name: ";
        cin >> temp_data;
        temp.setLastname(temp_data);

        cout << "Email: ";
        cin >> temp_data;
        temp.setEmail(temp_data);

        cout << "Address: ";
        cin >> temp_data;
        temp.setAddress(temp_data);

        cout << "Phone Number: ";
        cin >> temp_data;
        temp.setPhonenum(temp_data);

    //SInce the staff and the student is the child of the parent
    //some of the data member of them overlap
    //thus down casting of the parent is done inorder to avoid redundancy {writing seperate setter code for both child}.

    if(userType == "Student"){
        Student student = (Student) &person;   //downCasting

        cout << "Grade: ";
        cin >> grade;
        student.setGrade(grade);

        cout << "Date [DD/MM/YY]: ";
        cin >> temp_data >> temp_data2 >> temp_data3;
        student.setData(temp_data, temp_data2, temp_data3);
    }

    else if(userType == "Staff"){
        Staff staff = (Staff) &person;
        string temp_data;
        int temp;

        cout << "Subject: ";
        cin >> temp_data;
        staff.setSubject(temp_data);

        cout << "Salary: ";
        cin >> temp;
        staff.setSalary(temp);

    }
        
}

User::void register_user(){
    
    //shall have the file handlig part to store the data of the registeres user.

    //For the student types

    //For the Staff Type
}


int main(){
    User user;

    Menu menu;
    menu.welcome(user.getUserType());
    menu.loginMenu();
    user.register_user();
}