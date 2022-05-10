#ifndef DC_CPP
#define DC_CPP

#include <iostream>
#include <fstream>
#include <conio.h>

#include "..\Entity\User.cpp"
#include "..\Entity\Student.cpp"
#include "..\Entity\Staff.cpp"
#include "registration.cpp"


template <typename T>
bool update(T &obj, ifstream &record, int userId, string oldname);
int chooseUpdate(string whoseInfo);
void staff_header();
void student_header();
void user_header();
template <typename className> 
void searchRecord(User &user, int userId, ifstream &record, ifstream &login_record);



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

	void updateRecord(string whoseInfo);

	void search();


};


void DataController::search(){

	Registration temp;
	string whoseInfo = temp.chooseWhoseInfo();
	int userId;
	User user;
	user.setUserType("null");

	ifstream record, login_record;

	cout << "Enter the user Id: ";
	cin >> userId;

	if(!whoseInfo.compare("Student")){
		record.open("Student.dat");
		login_record.open("Login_std.dat");
		user.setUserType("Student");
		searchRecord<Student>(user, userId, record, login_record);
	}

	if(!whoseInfo.compare("Staff")){
		record.open("Staff.dat");
		login_record.open("Login_Staff.dat");
		user.setUserType("Staff");
		searchRecord<Staff>(user, userId, record, login_record);

	}

}


template <typename className> 
void searchRecord(User &user, int userId, ifstream &record, ifstream &login_record){

	className temp_obj;
	string whoseInfo = user.getUserType();
	User temp_user;

//login Information
	login_record >> temp_user;
	while(!login_record.eof()){
	
		if(temp_user.getUserId() == userId ){
			user = temp_user;
			break;
		} 
		login_record >> temp_user;
	}
	login_record.close();
	user.setUserType(whoseInfo);

//Presonal Information
	record >> temp_obj;
	while(!record.eof()){
	
		if(temp_obj.getUserId() == userId ){
			break;
		} 
		record >> temp_obj;
	}
	record.close();

	if(user.getUserType().compare("null")){//checks if the data is stored in user or not
		if(!whoseInfo.compare("Student")){
			student_header();
			temp_obj.display_data();
		}

		if(!whoseInfo.compare("Staff")){
			staff_header();
			temp_obj.display_data();
		}

		cout << "LOGIN INFORMATION:\n";
		user_header();
		user.display_user_data();
	}
	else{
		cout << "Data not available\n";
	}
	system("pause");

}

void DataController::updateRecord(string whoseInfo){

/* 
	for now:
		1.update the basic features of the user
		2. UserId is restricted to update.
		
	To do :
		- update the Login Crediantials if firstname is changed.
*/
 	enum Options{firstName = 1, lastName, email, address, contact, grade, dob, subject, salary};
	int newdata;
	string newString, oldname;
	int userId;
	bool isuser;
	
	Student temp_student;
	Staff temp_staff;

	ifstream record;

	if(!whoseInfo.compare("Admin")){
		Registration temp_registration;
		whoseInfo= temp_registration.chooseWhoseInfo();
	}

	
	int updateChoice = chooseUpdate(whoseInfo);

	cout << "User ID: ";
	cin >> userId;
	
	if(!whoseInfo.compare("Student")){
		oldname = "Student.dat";
		record.open(oldname, ios::in);
		isuser  = update <Student> (temp_student, record, userId, oldname);

	}

	if(!whoseInfo.compare("Staff")){
		oldname = "Staff.dat";
		record.open(oldname, ios::in);
		isuser = update <Staff> (temp_staff, record, userId, oldname);
	}

	ofstream update_record(oldname.c_str(), ios::out|ios :: app);
	switch(updateChoice){
	
		case firstName:
			cout << "New First Name: ";
			cin >> newString;
			if(!whoseInfo.compare("Student")){
				temp_student.setFirstname(newString);
			}
			if(!whoseInfo.compare("Staff")){
				temp_staff.setFirstname(newString);
			}
			break;

		case lastName:
			cout << "New Last Name: ";
			cin >> newString;
			if(!whoseInfo.compare("Student")){
				temp_student.setLastname(newString);
			}
			if(!whoseInfo.compare("Staff")){
				temp_staff.setLastname(newString);
			}
			break;

		case email:
		 	cout << "New Email: ";
			cin >> newString;
			if(!whoseInfo.compare("Student")){
				temp_student.setEmail(newString);
			}
			if(!whoseInfo.compare("Staff")){
				temp_staff.setEmail(newString);
			}
			
			break;

		case address:
			cout << "New Address: ";
			cin >> newString;
			if(!whoseInfo.compare("Student")){
				temp_student.setAddress(newString);
			}
			if(!whoseInfo.compare("Staff")){
				temp_staff.setAddress(newString);
			}
			break;

		case contact:
			cout << "New Contact: ";
			cin >> newString;
			if(!whoseInfo.compare("Student")){
				temp_student.setPhonenum(newString);
			}
			if(!whoseInfo.compare("Staff")){
				temp_staff.setPhonenum(newString);
			}
			break;

		case grade:
			cout << "New Grade: ";
			cin >> newdata;
			temp_student.setGrade(newdata);
			break;

		case dob:
			cout << "New Date of birth[mm/dd/yyyy]: ";
			cin >> newString;
			temp_student.setDate(newString);
			break;

		case subject:
			cout << "New Subject: ";
			cin >> newString;
			temp_staff.setSubject(newString);
			break;

		case salary: 
			cout << "New Salary: ";
			cin >> newdata;
			temp_staff.setSalary(newdata);
			break;

		default:
			cout << "Invalid choice";
			system("pause");
			system("cls");
			return updateRecord(whoseInfo);
	}
	
	if(isuser){
		if(!whoseInfo.compare("Student")){
			update_record << temp_student;
		}
		if(!whoseInfo.compare("Staff")){
			update_record << temp_staff;
		}
	}
	
	update_record.close();
	
}

int chooseUpdate(string whoseInfo){

	int choice;

	cout << "Update options\n";
	cout << "1. First Name\n";
	cout << "2. last Name\n";
	cout << "3. Email\n";
	cout << "4. Address\n";
	cout << "5. Phone Numeber\n";

	if(!whoseInfo.compare("Student")){
		cout << "6. Grade\n";
		cout << "7. Date Of Birth\n";

	}

	if(!whoseInfo.compare("Staff")){
		cout << "6. Subject\n";  //8
		cout << "7. Salary\n";  //9
	}

	cout << "Enter your choice: ";
	cin >> choice;

	if(choice >= 1 && choice <= 7){
		return choice;
	}
	if(!whoseInfo.compare("Staff") && (choice == 6 || choice == 7)){
		return (choice + 2);
	}
	
	return chooseUpdate(whoseInfo);
}

template <typename T>
bool update(T &obj, ifstream &record, int userId, string oldname){

	bool isuser;

	if(!record){
		cout << "File not open error.";
		exit(0);
	}

	T temp_obj;
	ofstream newFile("newfile.txt", ios::out | ios:: app);

	record >> temp_obj;

	while(!record.eof()){

		if(temp_obj.getUserId() == userId ){
			obj = temp_obj;		//stores the updated object	
			isuser = 1;
			
		}
		else{
			newFile << temp_obj; //copies the file
		}   
		record >> temp_obj;

	}

	newFile.close();
	record. close();

	remove(oldname.c_str());
	rename("newfile.txt", oldname.c_str());

	return isuser;

}

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
			temp_file << temp_user;
		}

		if(userId != t_user.getUserId()){
			temp_loginFile << t_user;
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
	
	int y_cord = 15;
	Registration temp;

	if(!whoseInfo.compare("Admin")) //If the logged in user is admin privilege to choose otherwise default.
		whoseInfo = temp.chooseWhoseInfo();

	if(!whoseInfo.compare("Student")){
		
		ifstream student_file("Student.dat", ios::in);
		Student temp_student;
		
		cout << "Student data: \n\n";
		if(!student_file){
		//	gotoxy(50, y_cord);
			cout << "file not found";
		}

		student_file >> temp_student;

		student_header();

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

		staff_header();
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

void student_header(){
	
	for(int i = 0; i < 128; i++){
			cout << "-";
	}

	cout << "\n";
	cout << "|";
	cout <<  setw(10) << "USER ID" <<"|";
	cout <<  setw(14) << "FIRST NAME" <<"|";
	cout <<  setw(14) << "LAST NAME" <<"|";
	cout <<  setw(30)<< "EMAIL"<<"|";
	cout <<  setw(20) << "ADDRESS" <<"|";
	cout <<  setw(13) << "PHONE NUM" <<"|";
	cout <<  setw(5) << "GRADE" <<"|";
	cout <<  setw(13) << "D.O.B" <<"|\n" ;

	for(int i = 0; i < 128; i++){
		cout << "-";
	}
	cout << "\n";
}

void staff_header(){
	for(int i = 0; i < 128; i++){
		cout << "-";
	}
	cout << "\n";
	cout << "|";
	cout <<  setw(10) << "USER ID" <<"|";
	cout <<  setw(14) << "FIRST NAME" <<"|";
	cout <<  setw(14) << "LAST NAME" <<"|";
	cout <<  setw(30)<< "EMAIL"<<"|";
	cout <<  setw(20) << "ADDRESS" <<"|";
	cout <<  setw(13) << "PHONE NUM" <<"|";
	cout <<  setw(13) << "SUBJECT" <<"|";
	cout <<  setw(5) << "SALARY" <<"|\n" ;

	for(int i = 0; i < 128; i++){
		cout << "-";
	}
	cout << "\n";

}

void user_header(){

	for(int i = 0; i < 59; i++){
		cout << "-";
	}
	 cout << "\n|";
	cout << setw(20) <<"USERNAME" <<"|";
	cout << setw(20) << "PASSWORD" << "|";
	cout << setw(15)<<  "USERTYPE" << "|\n";

	for(int i = 0; i < 59; i++){
		cout << "-";
	}
	cout << "\n";
}

#endif
