#ifndef DC_CPP
#define DC_CPP

#include <iostream>
#include <fstream>
#include <conio.h>

#include "..\Entity\User.cpp"
#include "..\Entity\Student.cpp"
#include "..\Entity\Staff.cpp"
#include "registration.cpp"

using namespace std;

class DataController {

public:

    void getLoggedUserInfo(User *);
    
	template <typename T>
    void delete_file(int, T &, string [], ifstream &, ifstream &);

	void deleteRecord();
	
	void viewGeneralRecord(string);

};

void DataController::getLoggedUserInfo(User *user) {
	user->display_user_data();
}

template <typename T>
void DataController::delete_file(int userId, T &temp_user, string file_name[], ifstream &record, ifstream &lrec) {

	ofstream temp_file("newFile.dat", ios::out);
	ofstream temp_loginFile("newLoginFile.dat", ios::out);

	record >> temp_user;
	User t_user;
	lrec >> t_user; 

	while(!record.eof()){

		if(userId != temp_user.getUserId()){
			temp_file << temp_user << "\n";
		}

		if(userId != t_user.getUserId()){
			temp_loginFile << t_user << "\n";
		}

		record >> temp_user;
		lrec >> t_user;
	}

	temp_file.close();
	temp_loginFile.close();
	record.close();
	lrec.close();
	
	remove(file_name[0].c_str());  //c_str converts the string to char*
	remove(file_name[1].c_str());  //c_str converts the string to char*
	rename("newFile.dat", file_name[0].c_str());
	rename("newLoginFile.dat", file_name[1].c_str());

}


void DataController::viewGeneralRecord(string whoseInfo){

	system("cls");
	
	Registration temp;

	if(!whoseInfo.compare("Admin")) //If the logged in user is admin privilege to choose otherwise default.
		whoseInfo = temp.chooseWhoseInfo();

	if(!whoseInfo.compare("Student")){
		
		ifstream student_file("student.dat", ios::in|ios::app);
		Student temp_student;
		
		cout << "Student data: \n\n";
		if(!student_file){
			cout << "file not found";
		}

		student_file >> temp_student;

		while(!student_file.eof()){
			temp_student.display_data();
			student_file >> temp_student;
		}

		student_file.close();
	}

	else if(!whoseInfo.compare("Staff")){
		ifstream staff_file("Staff.dat", ios::in|ios::app);

		Staff temp_staff;

		if(!staff_file){
			cout << "File not found";
			exit(1);
		}

		cout << "\n\nStaff Data: \n\n";
		staff_file >> temp_staff;
		while(!staff_file.eof()){
			temp_staff.display_data();
			staff_file >> temp_staff;
		}
		staff_file.close();
	}
}

void DataController::deleteRecord() {
	int userId;
	Registration temp_registration;
	string whoseInfo = temp_registration.chooseWhoseInfo();   //admin chooses the type of user to delete
	string file_name[2];

	ifstream record, lrec;

	if(!whoseInfo.compare("Student")){
		record.open("Student.dat", ios::in);
		lrec.open("Login_Std.dat", ios::in);
		file_name[0] = "Student.dat";
		file_name[1] = "Login_std.dat";
		cout << "Enter a User Id: ";
		cin >> userId;
		Student temp_user;
		delete_file <Student> (userId, temp_user, file_name, record, lrec);


	}
	else if(!whoseInfo.compare("Staff")){
		record.open("Staff.dat", ios::in);
		file_name[0] = "Staff.dat";
		file_name[1] = "Login_Staff.dat";
		cout << "Enter a User Id: ";
		cin >> userId;
		Staff temp_user;
		delete_file<Staff> (userId, temp_user, file_name, record, lrec);
	}
	else if(!whoseInfo.compare("Admin")){
		record.open("Admin.dat", ios::in);
		file_name[0] = "Staff.dat";
		file_name[1] = "Login_Staff.dat";
		cout << "Enter a User Id: ";
		cin >> userId;
		Staff temp_user;
		delete_file<Staff> (userId,temp_user, file_name, record, lrec);
	}

	//;;;Could add admin file in the future.
	
}

#endif