#include <iostream>
#include <fstream>
#include "./Entity/User.cpp"
#include "./Entity/staff.cpp"
#include "./Entity/Student.cpp"



using namespace std;

void get_data(string type){
	Person person;

	string temp_data, temp_data2, temp_data3;
	int grade;

	cout << "First Name: ";
	cin >> temp_data;
	person.setFirstname(temp_data);

	cout << "Last Name: ";
	cin >> temp_data;
	person.setLastname(temp_data);

	cout << "Email: ";
	cin >> temp_data;
	person.setEmail(temp_data);

	cout << "Address: ";
	cin >> temp_data;
	person.setAddress(temp_data);

	cout << "Phone Number: ";
	cin >> temp_data;
	person.setPhonenum(temp_data);

    //SInce the staff and the student is the child of the parent
    //some of the data member of them overlap
    //thus down casting of the parent is done inorder to avoid redundancy {writing seperate setter code for both child}.

    if(type == "Student"){
        Student *student = (Student*) &person;   //downCasting

        cout << "Grade: ";
        cin >> grade;
        student->setGrade(grade);

        cout << "Date [DD/MM/YY]: ";
        cin >> temp_data >> temp_data2 >> temp_data3;
        student->setData(temp_data, temp_data2, temp_data3);

		store_student(student);

    }

    if(type == "Staff"){
        Staff *staff = (Staff *) &person;
        string temp_data;
        int temp;

        cout << "Subject: ";
        cin >> temp_data;
        staff->setSubject(temp_data);

        cout << "Salary: ";
        cin >> temp;
        staff->setSalary(temp);

		store_staff(staff);
    }
    

}

void store_student(Student *student){
	ofstream student_file("Student.txt", ios::out||ios::app);

	if(!student_file){
		cout  << "File not found !!!";
		return 1;
	}

	student_file << *student;

	student_file.close();
	
}

void store_staff(Staff *staff){
	ofstream staff_file("Staff.txt", ios::out||ios::app);

	if(!staff_file){
		cout  << "File not found !!!";
		return 1;
	}

	staff_file << *staff;

	staff_file.close();
}

//get is not necessary for the registration. 
//However, might be required in the future...

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
