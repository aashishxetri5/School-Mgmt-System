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
  				return "Teacher";
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


	void get_data(string type) {
		Person person;

		string temp_data, whoseInfo = chooseWhoseInfo();
		int int_data;

		cout << "\n\tEnter your ID: ";
		cin >> int_data;
		person.setUserId(int_data);

		cout << "\n\tEnter the First Name: ";
		cin >> temp_data;
		person.setFirstname(temp_data);

		cout << "\n\tEnter the Last Name: ";
		cin >> temp_data;
		person.setLastname(temp_data);

		cout << "\n\tEnter the Email: ";
		cin >> temp_data;
		person.setEmail(temp_data);

		cout << "\n\tEnter the Address: ";
		cin >> temp_data;
		person.setAddress(temp_data);

		cout << "\n\tEnter the contact number: ";
		cin >> temp_data;
		person.setPhonenum(temp_data);

		// SInce the staff and the student is the child of the parent
		// some of the data member of them overlap
		// thus down casting of the parent is done inorder to avoid redundancy {writing seperate setter code for both child}.
		if(type == "Admin") {
			if (whoseInfo == "Student") {
				Student *student = (Student *)&person; // downCasting

				cout << "\n\tEnter the Grade: ";
				cin >> int_data;
				student->setGrade(int_data);

				cout << "\n\tEnter the Date [DD/MM/YY]: ";
				cin >> temp_data;
				student->setDate(temp_data);

				store_student(student);
			}

			if (whoseInfo == "Staff" || whoseInfo == "Admin") {
				Staff *staff = (Staff *)&person;
				// string temp_data;
				int temp;

				cout << "\n\tEnter the Subject: ";
				cin >> temp_data;
				staff->setSubject(temp_data);

				cout << "\n\tEnter the Salary: ";
				cin >> temp;
				staff->setSalary(temp);

				store_staff(staff, whoseInfo);
			}
		}
	}

	void store_student(Student *student) {
		fstream student_file("Student.dat", ios::out|ios::app);
		
		fstream student_loginfile("Login_Std.dat", ios::out|ios::app); //Create login file and add record when each new User is registered.

		User *user;
		user->set_username( setLoginCredentials( student->getFirstname(), student->getUserId() ) );
		user->set_password("qwerty");

		if (!student_file) {
			cout << "File not found !!!";
			exit(1);
		} else {
			student_file << *student;
			student_loginfile << *user;
		}

		student_file.close();
		student_loginfile.close();
	}

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

		User *user;
		user->set_username( setLoginCredentials( staff->getFirstname(), staff->getUserId() ) );
		user->set_password("qwerty");

		if (!rec_file) 		{
			cout << "File not found !!!";
			exit(1);
		} else {
			rec_file << *staff;
			rec_loginfile << *user;
		}
		
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