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

    void getLoggedoldFile(User *);
    
	template <typename T>
    void delete_file(int, T &, string [], ifstream &, ifstream &);

	void deleteRecord();
	
	void viewGeneralRecord(string);

	void viewLoginInfo();

	void saveMarks();

	void changePassword(User *user);

	void getLoggedUserInfo(User *user);


};

void DataController::changePassword(User *user){

	Registration temp_registration;
	string new_pass, confirm_pass, username;
	User temp_user;

	ifstream oldFile;
	ofstream newFile("newfile.dat", ios::out|ios::app);
	string oldname, newname = "newfile.dat";

	string whoseInfo = user ->getUserType();

	if(!whoseInfo.compare("Admin")){
		whoseInfo = temp_registration.chooseWhoseInfo();
	}

	cout << "UserName: ";
	cin >>  username;

	if(!whoseInfo.compare("Student")){	
		oldFile.open("Login_std.dat", ios::in);
		oldname = "Login_std.dat";

	}
	else if(!whoseInfo.compare("Staff")){
		oldFile.open("Login_Staff.dat", ios::in);
		oldname = "Login_Staff.dat";
	
	}
	else{
		oldFile.open("Login_Admin.dat", ios::in);
		oldname = "Login_Admin.dat";
	}

	while(1){
	
		cout << "New password: ";
		cin >> new_pass;

		cout << "Confirm Password: ";
		cin >> confirm_pass;

		if(!new_pass.compare(confirm_pass)){
			break;
		}
		system("cls");
	}

	if(!oldFile){
		cout << "file open error";
		exit(0);
	}

	oldFile >> temp_user;
	while(!oldFile.eof()){
		
		if(!username.compare(temp_user.get_username())){
			temp_user.set_password(new_pass);
		}
		newFile << temp_user;
		oldFile >> temp_user;

	}

	oldFile.close();
	newFile.close();

	remove(oldname.c_str());
	rename(newname.c_str(), oldname.c_str());

	cout << "Password sucessfully changed!";
	system("pause");

}

void DataController::viewLoginInfo(){
	Registration temp_registration ;
	string whoseInfo = temp_registration.chooseWhoseInfo();

	User user;

	string username;
	ifstream userFile;


	cout << "Enter username: ";
	cin >> username;

	if(!whoseInfo.compare("Student")){	
		userFile.open("Login_std.dat", ios::in);
		user.setUserType("Student");

	}
	else if(!whoseInfo.compare("Staff")){
		userFile.open("Login_Staff.dat", ios::in);
		user.setUserType("Staff");
	}
	else{
		userFile.open("Login_Admin.dat", ios::in);
		user.setUserType("Admin");
	}

	if(!userFile){
		cout << "File open Error";
		exit(0);
	}

	
	while(!userFile.eof()){
		userFile >> user;
		if(!user.get_username().compare(username)){
			user.display_user_data();
			break;
		}
		//userFile >> user;
	}


	userFile.close();
	system("pause");

}


void DataController::getLoggedoldFile(User *user) {
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
		
		ifstream student_file("Student.dat", ios::in);
		Student temp_student;
		
		cout << "Student data: \n\n";
		if(!student_file){
			cout << "file not found";
		}
		else{
			cout << "File opened sucessfully";
		}

		student_file >> temp_student;

		do{
			temp_student.display_data();
			student_file >> temp_student;
		}while(!student_file.eof());
	
		//temp_student.display_data();

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

		do{
			temp_staff.display_data();
			staff_file >> temp_staff;
		}while(!staff_file.eof());

	
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