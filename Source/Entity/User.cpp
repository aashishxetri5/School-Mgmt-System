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

#include <iostream>

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

