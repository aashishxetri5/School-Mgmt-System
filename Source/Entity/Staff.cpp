/*
Name of class should be Same as the file name.

This shall have the properties/details of a teacher/staff. Create Getters and setters for each data member.
Also, create a parameterized constructor having all the data members. This class shall inherit the
Person class.

*/
#include<iostream>
#include"Person.cpp"

using namespace std;

// class Staff: public Person{}
class Staff{
    string Post, name, address;
    int Staff_id, age;
    long long int phone;
    public:
    Staff(string Pst, string nm, string add, int Stf_id, int ag, long long int phn){
        Post = Pst;
        name = nm;
        address = add;
        Staff_id = Stf_id;
        age = ag;
        phone = phn;
    }

    //setter function for each data members
    void setPost();
    void setName();
    void setAdr();
    void setStf_id();
    void setAge();
    void setPhone();

    //getter Function
    string getPost();
    string getName();
    string getAdr();
    int getStf_id();
    int getAge();
    long long int getPhone();

};

void Staff::setPost(){
    cout<<"Post: ";
    cin>>Post;
}

void Staff::setName(){
    cout<<"Name: ";
    cin>>name;
}

void Staff::setAdr(){
    cout<<"Address: ";
    cin>>address;
}

void Staff::setStf_id(){
    cout<<"Staff ID: ";
    cin>>Staff_id;
}

void Staff::setAge(){
    cout<<"Age: ";
    cin>>age;
}

void Staff::setPhone(){
    cout<<"Phone: ";
    cin>>phone;
}

string Staff::getPost(){
    return Post;
}

string Staff::getName(){
    return name;
}

string Staff::getAdr(){
    return address;
}

int Staff::getStf_id(){
    return Staff_id;
}

int Staff::getAge(){
    return age;
}

long long int Staff::getPhone(){
    return phone;
}
