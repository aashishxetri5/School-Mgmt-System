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

using namespace std;

class DataController {

public:

	template <typename className> 
	void searchRecord(User &user, int userId, ifstream &record, ifstream &login_record);

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
		record.open("../Files/personal_Infos/Student.dat");
		login_record.open("../Files/Logins/Login_std.dat");
		user.setUserType("Student");
		searchRecord<Student>(user, userId, record, login_record);
	}

	if(!whoseInfo.compare("Staff")){
		record.open("../Files/personal_Infos/Staff.dat");
		login_record.open("../Files/Logins/Login_Staff.dat");
		user.setUserType("Staff");
		searchRecord<Staff>(user, userId, record, login_record);

	}

}

template <typename className> 
void DataController::searchRecord(User &user, int userId, ifstream &record, ifstream &login_record){

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
		record.open("../Files/personal_Infos/"+oldname, ios::in);
		isuser  = update <Student> (temp_student, record, userId, oldname);

	}

	if(!whoseInfo.compare("Staff")){
		oldname = "Staff.dat";
		record.open("../Files/personal_Infos/"+oldname, ios::in);
		isuser = update <Staff> (temp_staff, record, userId, oldname);
	}

	ofstream update_record(("../Files/personal_Infos/" + oldname).c_str(), ios::out|ios :: app);
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
	ofstream newFile("../Files/personal_Infos/newfile.txt", ios::out | ios:: app);

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

	remove(("../Files/personal_Infos/" + oldname).c_str());
	rename("../Files/personal_Infos/newfile.txt", ("../Files/personal_Infos/" + oldname).c_str());

	return isuser;

}

void DataController::changePassword(User *user){

	Registration temp_registration;
	string new_pass, confirm_pass, username;
	User temp_user;

	ifstream oldFile;
	ofstream newFile("../Files/personal_Infos/newfile.dat", ios::out|ios::app);
	string oldname, newname = "newfile.dat";

	string whoseInfo = user ->getUserType();

	if(!whoseInfo.compare("Admin")){
		whoseInfo = temp_registration.chooseWhoseInfo();
	}

	cout << "UserName: ";
	cin >>  username;

	if(!whoseInfo.compare("Student")){	
		oldFile.open("../Files/Logins/Login_std.dat", ios::in);
		oldname = "Login_std.dat";

	}
	else if(!whoseInfo.compare("Staff")){
		oldFile.open("../Files/Logins/Login_Staff.dat", ios::in);
		oldname = "Login_Staff.dat";
	
	}
	else{
		oldFile.open("../Files/Logins/Login_Admin.dat", ios::in);
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

	remove(("../Files/Logins/" + oldname).c_str());
	rename(("../Files/Logins/" + newname).c_str(), ("../Files/Logins/" + oldname).c_str());

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
		userFile.open("../Files/Logins/Login_std.dat", ios::in);
		user.setUserType("Student");

	}
	else if(!whoseInfo.compare("Staff")){
		userFile.open("../Files/Logins/Login_Staff.dat", ios::in);
		user.setUserType("Staff");
	}
	else{
		userFile.open("../Files/Logins/Login_Admin.dat", ios::in);
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

	ofstream temp_file("../Files/personal_Infos/newFile.dat", ios::out);
	ofstream temp_loginFile("../Files/Logins/newLoginFile.dat", ios::out);

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
	
	remove(("../Files/personal_Infos/"+file_name[0]).c_str());  //c_str converts the string to char*
	remove(("../Files/Logins/"+ file_name[1]).c_str());  //c_str converts the string to char*
	rename("../Files/personal_Infos/newFile.dat", ("../Files/personal_Infos/"+file_name[0]).c_str());
	rename("../Files/Logins/newLoginFile.dat", ("../Files/Logins/" + file_name[1]).c_str());

}

//Displays General records of student, admin and staff
void DataController::viewGeneralRecord(string whoseInfo){

	system("cls");
	
	int y_cord = 15;
	Registration temp;

	if(!whoseInfo.compare("Admin")) //If the logged in user is admin privilege to choose otherwise default.
		whoseInfo = temp.chooseWhoseInfo();

	if(!whoseInfo.compare("Student")){
		
		ifstream student_file("../Files/personal_Infos/Student.dat", ios::in);
		Student temp_student;
		
		cout << "Student data: \n\n";
		if(!student_file){
			cout << "file not found";
		} else {
			student_file >> temp_student;
			student_header();

			do{
				temp_student.display_data();
				student_file >> temp_student;
			} while(!student_file.eof());
	
		}

		student_file.close();
	}

	else if(!whoseInfo.compare("Staff")){
		ifstream staff_file("../Files/personal_Infos/Staff.dat", ios::in|ios::app);

		Staff temp_staff;

		if(!staff_file){
			cout << "File not found";
		} else {

			cout << "\n\nStaff Data: \n\n";
			staff_file >> temp_staff;

			staff_header();
			do {
				temp_staff.display_data();
				staff_file >> temp_staff;
			} while(!staff_file.eof());
		}
		staff_file.close();

	} else if(!whoseInfo.compare("Admin")){
		ifstream admin_file("Admin.dat", ios::in|ios::app);

		Staff temp_admin;

		if(!admin_file){
			cout << "File not found";
		} else {

			cout << "\n\nStaff Data: \n\n";
			admin_file >> temp_admin;
			staff_header();

			do {
				temp_admin.display_data();
				admin_file >> temp_admin;
			} while(!admin_file.eof());

		}
		admin_file.close();
	}

}

void DataController::deleteRecord() {
	int userId;
	Registration temp_registration;
	string whoseInfo = temp_registration.chooseWhoseInfo();   //admin chooses the type of user to delete
	string file_name[2];

	ifstream record, login_rec;

	if(!whoseInfo.compare("Student")){
		record.open("../Files/personal_Infos/Student.dat", ios::in);
		login_rec.open("../Files/personal_Infos/Login_Std.dat", ios::in);
    
		file_name[0] = "Student.dat";
		file_name[1] = "Login_std.dat";
		cout << "\n\tEnter a User Id: ";
		cin >> userId;
		Student temp_user;
		delete_file <Student> (userId, temp_user, file_name, record, login_rec);
	}
	else if(!whoseInfo.compare("Staff")){
		record.open("../Files/personal_Infos/Staff.dat", ios::in);
		file_name[0] = "Staff.dat";
		file_name[1] = "Login_Staff.dat";
		cout << "\n\tEnter a User Id: ";
		cin >> userId;
		Staff temp_user;
		delete_file<Staff> (userId, temp_user, file_name, record, login_rec);
	}
	else if(!whoseInfo.compare("Admin")){
		record.open("../Files/personal_Infos/Admin.dat", ios::in);
		file_name[0] = "Staff.dat";
		file_name[1] = "Login_Staff.dat";
		cout << "Enter a User Id: ";
		cin >> userId;
		Staff temp_user;
		delete_file<Staff> (userId, temp_user, file_name, record, login_rec);
	}
	
}

//To display the table headings for students
void student_header(){

	cout << setw(7) << "User Id";
	cout << setw(14) << "Fullname";
	cout << setw(16) << "Grade";
	cout << setw(10) << "Email";
	cout << setw(29) << "Address";
	cout << setw(16) << "Contact";
	cout << setw(13) << "Dob" << "\n";

	for(int i = 0; i < 120; i++){
		cout << "-";
	}
	cout << "\n";
}

//To display the table headings for staff and admin
void staff_header(){

	cout << setw(7) << "User Id";
	cout << setw(14) << "Fullname";
	cout << setw(22) << "Email";
	cout << setw(27) << "Address";
	cout << setw(16) << "Contact";
	cout << setw(15) << "Subject";
	cout << setw(10) << "Salary" << "\n";

	for(int i = 0; i < 120; i++){
		cout << "-";
	}
	cout << "\n";

}

void user_header(){

	cout << setw(20) << "User Id";
	cout << setw(20) << "Username";
	cout << setw(20) << "Password" ;
	cout << setw(15) << "UserType" << "\n";

	for(int i = 0; i < 59; i++){
		cout << "-";
	}
	cout << "\n";
}

#endif
