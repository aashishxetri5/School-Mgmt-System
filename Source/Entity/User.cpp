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

void login();

class User{
    string email, password;

    public:
        User(){}

        User(string e, string p){
            email = e;
            password = p;
        }

        User(const User &obj){
            email = obj.email;
            password = obj.password;
        }

        //setter
        void set_email(){}
        void set_password(){}

        //getter 
        string get_email(){}
        string get_password(){}

    //    bool operator == (User obj){}

     
};


void User::set_email(){
    cout << "Email: ";
    cin  >> email;

}

void User::set_password(){
    cout << "Password: ";
    cin >> password;
}

string User::get_email(){
    return email;
}

string User::get_password(){
    return password;
}

//bool User::operator == (User obj){}


/*
void login(){
    User login_user;

    cout << "Email: ";
    login_user.get_email();
    
    cout << "Password: ";
    login_user.get_password();

    
}

*/

