  //so that the same header file will not be included multiple times
#include <iostream>
#include <string>

class person{
    string name, DOB, address;
    char gender;
    long long int phone_no;

    public:
        virtual void SetInfo(){
        }
        virtual void GetInfo(){
        }

};

class student: public person{
    string major;
    int roll_no;

    public:
        void SetInfo(){

        }

        void GetInfo(){

        }
};

class faculty: public person{

    string subject;

    public:
        void SetInfo(){

        }

        void GetInfo(){

        }

};

/*
class admin: private person{

};

*/


