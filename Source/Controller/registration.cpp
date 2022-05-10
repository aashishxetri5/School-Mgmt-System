/*

Registration:
	1.Gets the type of user.
	2.Gets the data of the user.

		if unique data members:
			1. Username
			2. Userid
		else
			exception

	3.Store the data of the user to the file
	4.transfer the control to the logged in user.

Things to be added:

1. Logic to check whether the username is taken or not.
   [as no two person can have identical username | userId ?]

2. Store the credintials of the user.
	[Unsure to store in the same file where their data is stored]

*/

#ifndef REGISTRATION_CPP
#define REGISTRATION_CPP

#include <iostream>
#include "../Entity/staff.cpp"
#include "../Entity/Student.cpp"
#include "../Entity/User.cpp"

class Registration {
public:

	//Lets user choose whose data does the admin want to perform the requested operation on.
	string chooseWhoseInfo() {
		char choice;
		cout << "\n\tChoose on whose info do you want to perform the requested action\n\tstudent(s)\tteacher(t)\tadministration(a)";
		cout << "\n\tEnter your choice: ";
  		scanf(" %c", &choice);
		switch(choice){
  			case 's':
  				return "Student";
  				break;
  			case 't':
  				return "Staff";
  				break;
  			case 'a':
  				return "Admin";
  				break;
  			default:
  				cout << "\n\n\tInvalid Choice\n\t";
  				system("pause");
  				system("cls");
  				return chooseWhoseInfo();
  		}
	}

	//sets data into the object of respective Usertype.
	char get_data(string type) {

		string firstname, lastname, email, address, phone_num, dob; 
		int grade, userId;
		system("cls");
		string whoseInfo = chooseWhoseInfo();

		cout << "\n\tEnter your ID: ";
		cin >> userId;

		cout << "\n\tEnter the First Name: ";
		cin >> firstname;

		cout << "\n\tEnter the Last Name: ";
		cin >> lastname;

		cout << "\n\tEnter the Email: ";
		cin >> email;

		cout << "\n\tEnter the Address: ";
		cin >> address;

		cout << "\n\tEnter the contact number: ";
		cin >> phone_num;
 		
		if(type == "Admin") {
			if (whoseInfo == "Student") {

				cout << "\n\tEnter the Grade: ";
				cin >> grade;

				cout << "\n\tEnter the Date [DD/MM/YY]: ";
				cin >> dob;

				Student *student = new Student(userId, firstname, lastname, email, address, phone_num, grade, dob);
				
				store_student(student);

				delete student;
				student = nullptr;
			}

			if (whoseInfo == "Staff" || whoseInfo == "Admin") {
				string subject;
				int salary;

				if(whoseInfo == "Admin") {
					subject = "Admin"; //Admin doesn't have a subject.
				} else {
					cout << "\n\tEnter the Subject: ";
					cin >> subject;
				}

				cout << "\n\tEnter the Salary: ";
				cin >> salary;

				Staff *staff = new Staff(userId, firstname, lastname, email, address, phone_num, subject, salary);

				store_staff(staff, whoseInfo);
			}
		}

		char userResponse;
		cout << "\n\n\tDo you want to add more records? 'n' NO: ";
		cin >> userResponse;

		return userResponse;
	}


	//Creates/Opens the file to store the student's general data as well as the login data. 
	void store_student(Student *student) {
		fstream student_file("Student.dat", ios::out|ios::app);
		
		fstream student_loginfile("Login_Std.dat", ios::out|ios::app); //Create login file and add record when each new User is registered.

		User *user = new User(student->getUserId(), setLoginCredentials( student->getFirstname(), student->getUserId()), "qwerty");

		if (!student_file) {
			cout << "File not found !!!";
			exit(1);
		} else {
			student_file << *student << flush;
			student_loginfile << *user << flush;
		}
		
		delete user;
		user = nullptr;

		student_file.close();
		student_loginfile.close();
	}

	//Creates/Opens the file to store the Staff's or Admin's general data as well as the login data. 
	void store_staff(Staff *staff, string whoseInfo) {
		 fstream rec_file;
		 fstream rec_loginfile;

		if(whoseInfo == "Staff"){
			rec_file.open("Staff.dat", ios::out|ios::app);
			rec_loginfile.open("Login_Staff.dat", ios::out|ios::app); //Create login file and add record when each new User is registered.
		} else {
			rec_file.open("Admin.dat", ios::out|ios::app);
			rec_loginfile.open("Login_Admin.dat", ios::out|ios::app); //Create login file and add record when each new User is registered.
		}

		User *user = new User(staff->getUserId(), setLoginCredentials( staff->getFirstname(), staff->getUserId()), "qwerty");
		

		if (!rec_file) {
			cout << "File not found !!!";
			exit(1);
		} else {
			rec_file << *staff << flush;
			rec_loginfile << *user << flush;
		}
		
		delete user;
		user = nullptr;

		rec_file.close();
		rec_loginfile.close();
	}

// get is not necessary for the registration.
// However, might be required in the future...

// Student get_student(){
// 	ifstream student_file("Student.txt", ios::in);
// 	Student temp;
// 	student_file.seekg(0, ios::beg);
// 	if(!student_file){
// 		cout << "File not found";

// 	}

// 	student_file >> temp;
// 	student_file.close();
// 	return temp;
// }

// Staff get_staff(){
// 	Staff temp;

// 	ifstream staff_file("Staff.txt", ios::in);

// 	staff_file.seekg(0, ios::beg); //set the cursor to the beg of the file

// 	if(!staff_file){
// 		cout << "File not found";
// 	}

// 	staff_file >> temp;   //store the data of the student from the file to the tmeporary class
// 	staff_file.close();
// 	return temp;
// }


	string setLoginCredentials(string fname, int userId) {
		return ( fname + to_string(userId) );
	}

};

#endif