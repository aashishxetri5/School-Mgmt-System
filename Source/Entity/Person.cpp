// This shall have the common properties/details of a person

#include <iostream>
using namespace std;

class Person {
protected:
    string firstname, lastname, email, address, phone_num;
    int userId;
public:
    Person() {}

    //Constructor for accepting data while entry. It is initialized from its child class and rarely initialized with by creating an object.
    Person(int userId, string firstname, string lastname, string email, string address, string phone_num) {
        this -> userId = userId;
        this -> firstname = firstname;
        this -> lastname = lastname;
        this -> email = email;
        this -> address = address;
        this -> phone_num = phone_num;    
    }

    void setUserId(int userId);

    int getUserId();

    void setFirstname(string firstname);

    string getFirstname();

    void setLastname(string lastname);

    string getLastname();

    string getFullname();

    void setEmail(string email);

    string getEmail();

    void setAddress(string address);

    string getAddress();

    void setPhonenum(string phone_num);

    string getPhonenum();

};

/*
    The setters are used to set data received via the parameter to the current class variables.
    The getters return the value set via setters or the constructor to the location it is being called from.
*/
void Person::setUserId(int userId) {
    this -> userId = userId;
}

int Person::getUserId() {
    return userId;
}

void Person::setFirstname(string firstname) {
    this -> firstname = firstname;
}

string Person::getFirstname() {
    return firstname;
}

void Person::setLastname(string lastname) {
    this -> lastname = lastname;
}

string Person::getLastname() {
    return lastname;
}

string Person::getFullname() {
    return (firstname + " " + lastname);
}

void Person::setEmail(string email) {
    this -> email = email;
}

string Person::getEmail() {
    return email;
}

void Person::setAddress(string address) {
    this -> address = address;
}

string Person::getAddress() {
    return address;
}

void Person::setPhonenum(string phone_num) {
    this -> phone_num = phone_num;
}

string Person::getPhonenum() {
    return phone_num;
}
