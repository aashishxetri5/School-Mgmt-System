/*
Name of class should be Same as the file name.

This shall have the properties/details for a user to be logged in. 
Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members.

*/

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
#ifndef USER_CPP
#define USER_CPP
#include <iostream>
#include <fstream>
using namespace std;

class User{
    string username, password, userType;

public:
    User(){
        userType = "";
    }
    
    User(string username, string password) {
        this->username = username;
        this->password = password;
    }

    User(const User &userObj){
        username = userObj.username;
        password = userObj.password;
        userType = userObj.userType;
    }
    
    //setter
    void set_username(string);
    void set_password(string);
    void setUserType(string);
    
    //getter 
    string get_username();
    string get_password();
    string getUserType();

    //write to the file
    friend ostream& operator << (ostream &stream, User &uObj);

    //read from the file
    friend istream& operator >> (istream &stream, User &uobj);
   
    
};


void User::set_username(string username) {
    this->username = username;
}

void User::set_password(string password) {
    this->password = password;
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
ostream& operator << (ostream& stream, User &uObj){

    stream << uObj.username << "\t"; 
	stream << uObj.password;
	return stream;
}

//read from the file and sets the value of the Object
istream& operator >> (istream& stream, User &uObj){

    stream >> uObj.username;
    stream >> uObj.password;
    return stream;
}

#endif