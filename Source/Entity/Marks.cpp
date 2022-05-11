#ifndef MARKS_CPP
#define MARKS_CPP

#include <iostream>

using namespace std;

class Marks {
    string subj1, subj2, subj3, subj4, subj5, result;
    int userId, mark1, mark2, mark3, mark4, mark5;
    int total;
    float percentage;


public:

    Marks(){}

    Marks(int userId, string subj1, string subj2, string subj3, string subj4, string subj5, int mark1, int mark2, int mark3, int mark4, int mark5) {
        this->userId = userId;

        this-> subj1 = subj1;
        this-> subj2 = subj2;
        this-> subj3 = subj3;
        this-> subj4 = subj4;
        this-> subj5 = subj5;

        this-> mark1 = mark1;
        this-> mark2 = mark2;
        this-> mark3 = mark3;
        this-> mark4 = mark4;   
        this-> mark5 = mark5;
    }

    Marks(const Marks &mark) {
        userId = mark.userId;

        subj1 = mark.subj1;
        subj2 = mark.subj2;
        subj3 = mark.subj3;
        subj4 = mark.subj4;
        subj5 = mark.subj5;

        mark1 = mark.mark1;
        mark2 = mark.mark2;
        mark3 = mark.mark3;
        mark4 = mark.mark4;   
        mark5 = mark.mark5;
    }

    int getUserId();

    string getSubj1();
    int getMark1();

    string getSubj2();
    int getMark2();

    string getSubj3();
    int getMark3();

    string getSubj4();
    int getMark4();

    string getSubj5();
    int getMark5();

    
    int getTotal();

    char getPassOrFail();

    float getPercentage();

    void displayData();


    //write to the file
    friend ostream& operator << (ostream &stream, Marks &mObj);

    //read from the file
    friend istream& operator >> (istream &stream, Marks &mobj);

};

int Marks::getUserId() {
    return userId;
}

string Marks::getSubj1() {
    return subj1;
}

int Marks::getMark1() {
    return mark1;
}

string Marks::getSubj2() {
    return subj2;
}

int Marks::getMark2() {
    return mark2;
}

string Marks::getSubj3() {
    return subj3;
}

int Marks::getMark3() {
    return mark3;
}

string Marks::getSubj4() {
    return subj4;
}

int Marks::getMark4() {
    return mark4;
}

string Marks::getSubj5() {
    return subj5;
}

int Marks::getMark5() {
    return mark5;
}

int Marks::getTotal() {
    return (mark1+mark2+mark3+mark4+mark5);
}

char Marks::getPassOrFail() {
    if(mark1>=40 && mark2>=40 && mark3>=40 && mark4>=40 && mark5>=40)
        return 'P';
    else
        return 'F';
}

float Marks::getPercentage() {
    return getTotal()/5.0;
}

void Marks::displayData() {
    cout << setw(7) << to_string(userId);
    cout << setw(9) << subj1;
    cout << setw(15) << to_string(mark1);
    cout << setw(6) << subj2;
    cout << setw(15) << to_string(mark2);
    cout << setw(10) << subj3;
    cout << setw(15) << to_string(mark3);
    cout << setw(9) << subj4;
    cout << setw(10) << to_string(mark4);
    cout << setw(15) << subj5;
    cout << setw(9) << to_string(mark5) << "\n";

    for(int i = 0; i < 125; i++){
        cout << "-";
    }
    cout << "\n";
}

//writes the data members of the user object to the file 
ostream& operator << (ostream& stream, Marks &mObj){

    stream << mObj.userId << "\t";
    stream << mObj.subj1 << "\t";
    stream << mObj.mark1 << "\t";
    stream << mObj.subj2 << "\t";
    stream << mObj.mark2 << "\t";
    stream << mObj.subj3 << "\t";
    stream << mObj.mark3 << "\t";
    stream << mObj.subj4 << "\t";
    stream << mObj.mark4 << "\t";
    stream << mObj.subj5 << "\t";
    stream << mObj.mark5 << "\t";
    stream << mObj.getTotal() << "\t";
    stream << mObj.getPercentage() << "\t";
    stream << mObj.getPassOrFail() << "\n";
    
	return stream;
}

//read from the file and sets the value of the Object
istream& operator >> (istream& stream, Marks &mObj){

    stream >> mObj.userId;
    stream >> mObj.subj1;
    stream >> mObj.mark1;
    stream >> mObj.subj2;
    stream >> mObj.mark2;
    stream >> mObj.subj3;
    stream >> mObj.mark3;
    stream >> mObj.subj4;
    stream >> mObj.mark4;
    stream >> mObj.subj5;
    stream >> mObj.mark5;
    stream >> mObj.total;
    stream >> mObj.percentage;
    stream >> mObj.result;
    return stream;
}

#endif