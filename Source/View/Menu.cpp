//This shall contain functions for the menu.
#include <conio.h>
#include <cstdio>

#include "..\Controller\LoginController.cpp"
#include "..\Controller\registration.cpp"

void getLoggedUserInfo(User *);
void viewGeneralRecord(string);
void password_hide(string &);
void deleteRecord();
template <typename T>
void delete_file(int key, T &temp_user, string file_name, ifstream &record);

class Menu {
    int menuChoice;
public:
static int isLoggedOut;

void welcome(string);

int loginMenu();

bool login(User*);

bool mainOptions(User*);

bool performRequestionOperation(User*);

};


/* Displays the welcome message on top of the screen */
void Menu::welcome(string loggedInUserType) {
	system("cls");
    cout << "\t School Management System\n";
    cout << "\t**************************\n\n";
    if(loggedInUserType.length() == 0){
	    cout << "\t<== Login ==>\n";
	}else{
        cout << "\t<== " << loggedInUserType << " Panel ==>\n";
 	}
}

/* lets user select which  */
int Menu::loginMenu() {
    cout << "\n\t1. Student Login";
    cout << "\n\t2. Staff Login";
    cout << "\n\t3. Accounts Login";
    cout << "\n\t0. Exit\n";
    cout << "\n\tEnter your choice: ";
    cin >> menuChoice;
        
    return menuChoice;
}

//take credentials
bool Menu::login(User *user) {
    string temp_data = "";
    char temp;

    cout << "\n\tEnter your username: ";
	cin >> temp_data;
    user->set_username(temp_data);

    cout << "\tEnter your password: ";
    /* Accepts Password and displays '*' instead of entered character. */
	temp_data = "";
    password_hide(temp_data);

    user->set_password(temp_data);

    if(!LoginController().isValidUser(user)) {
        cout << "\n\tOopsies!! Login Failed.\n\n\t";
        system("pause");
        return false;
    }
    return true;

}

//This is the main option. It contains several options like add, update, delete, search, etc.
bool Menu::mainOptions(User *user) {
	system("cls");
	welcome(user->getUserType());

	/* Displays main menu of the program */
	cout <<"\t1. View Record(s)\n";
	cout <<"\t2. Update Record\n";
        
    /* Restricting Staffs from viewing marksheet*/
	if( user->getUserType().compare("Staff") != 0){
	    cout <<"\t3. Show Marksheet\n";
	}
    
	/* Only administrative users will be able to access these options. */
	if( !user->getUserType().compare("Admin")){
	    cout << "\t4. Add Record(s)\n";
	    cout << "\t5. Delete Record\n";
	    cout << "\t6. Search Record\n";
	    cout << "\t7. View Login Information\n";
	    cout << "\t8. Save Marks\n";
	}

	cout << "\t9. Change Password\n";
	cout << "\t10.Logout\n";
	cout << "\t0. Exit\n";
	cout << "\n\tEnter your choice: ";
	cin >> menuChoice;
    
	/* Prevents Staff members from accessing Administrative Controls. */
	if( user->getUserType().compare("Staff") == 0 && menuChoice == 3){
	    cout <<"\n\tInvalid input...\n\t";
	    system("pause");
	    system("cls");
        return false;
            
	}else if( (!user->getUserType().compare("Student") || !user->getUserType().compare("Staff")) && (menuChoice > 3 && menuChoice < 10)){
        /* Preventing Students and Staffs from accessing Administrative Controls. */
	    cout <<"\n\tInvalid input...\n\t";
	    system("pause");
	    system("cls");
        return false;
	}

    return performRequestionOperation(user);
}

// This method will call the respective method from any other class which implements the functionality of the requested operation.
bool Menu::performRequestionOperation(User *user) {
	char resp;
    switch(menuChoice){
	case 1:
		if(!user->getUserType().compare("Admin") ) {
            cout << "view admin record";
			viewGeneralRecord(user->getUserType());
			system("pause");
			system("cls");
			mainOptions(user);
		} 
		else {
            cout << "view student/staff record";
			getLoggedUserInfo(user);
		}
		break;
	case 2:
		if(!user->getUserType().compare("Admin") ){
            cout << "udpate admin record";
			// updateRecord();
		} else {
            cout << "udpate std/student record";
			// updateSelfRecord();
		}
		break;
	case 3:
        cout << "marksheet";
		// displayMarksheet();
		break;
	case 4:
		Registration reg;
		resp = reg.get_data(user->getUserType());
		system("cls");
		if ( resp != 'N' && resp != 'n' ) {
			return performRequestionOperation(user);
		}
		break;
	case 5:
        cout << "delete record";
		deleteRecord();
		break;
	case 6:
        cout << "search record";
		// search();
		break;
	case 7:
        cout << "login info";
		//viewLoginInfo(); --> will open the login file
		break;
	case 8:
        cout << "save marks";
		// saveMarks();
		break;
	case 9:
        cout << "change password";
		// changePassword();
		break;
	case 10:
		cout << "\n\tLogged out successfully...\n\t";
		//delete user;
        //user = nullptr;
		system("pause");
		isLoggedOut = 1;
		return false;

	case 0:
		cout << "\tExiting...";
		exit(0);
	default:
		cout << "\tInvalid choice!!!\n\t";
		system("pause");
		return false;
	}
    return true;
}


void deleteRecord(){
	int key;
	Registration temp_registration;
	string whoseInfo = temp_registration.chooseWhoseInfo();   //admin chooses the type of user to delete
	string file_name;

	ifstream record;

	if(!whoseInfo.compare("Student")){
		record.open("Student.dat", ios::in);
		file_name = "Student.dat";
		cout << "Enter a User Id: ";
		cin >> key;
		Student temp_user;
		delete_file <Student> (key,temp_user, file_name, record);


	}
	else if(!whoseInfo.compare("Staff")){
		record.open("Staff.dat", ios::in);
		file_name = "Staff.dat";
		cout << "Enter a User Id: ";
		cin >> key;
		Staff temp_user;
		delete_file <Staff> (key,temp_user, file_name, record);
	}

	//;;;Could add admin file in the future.
	
}

template <typename T>
void delete_file(int key, T &temp_user, string file_name, ifstream &record){

	ofstream temp_file("newFile.dat", ios::out);

	record >> temp_user;

	while(!record.eof()){

		if(key != temp_user.getUserId()){
			temp_file << temp_user << "\n";
		}

		record >> temp_user;
	}

	temp_file.close();
	record.close();
	
	remove(file_name.c_str());  //c_str converts the string to char*
	rename("newFile.dat", file_name.c_str());

}

void viewGeneralRecord(string whoseInfo){

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
			//exit(1);
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

void password_hide(string &password){

	while(true){
		char temp = getch();
		
		if(temp == 13){ //\r carriage return ascii value
			break;
		}
		cout << "*";
		password = password + temp;
	}
	
}

void getLoggedUserInfo(User *user){
	user->display_user_data();
}

