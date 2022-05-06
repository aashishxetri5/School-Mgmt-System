//This shall contain functions for the menu.
#include <conio.h>

#include "..\Controller\LoginController.cpp"
#include "..\Controller\registration.cpp"

class Menu {
    int menuChoice;
public:
static int isLoggedOut;

void welcome(string);

int loginMenu();

bool login(User*);

bool mainOptions(User*);

bool performRequestedOperation(User*);

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
    cout << "\n\t3. Admin Login";
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
    while(true) {
        temp = getch();
        /*Checks if user hit 'Enter'. If yes, the password end is declared by breaking out of the loop. */
        if(temp == 13) {
            break;
        }
        cout <<"*";
        temp_data = temp_data + temp;
    }

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

    return performRequestedOperation(user);
}

// This method will call the respective method from any other class which implements the functionality of the requested operation.
bool Menu::performRequestedOperation(User *user) {
	char resp;
    switch(menuChoice){
	case 1:
		if(!user->getUserType().compare("Admin") ) {
            cout << "view admin record";
			// viewGeneralRecord();
		} else {
            cout << "view student/staff record";
			// getLoggedUserInfo();
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
			return performRequestedOperation(user);
		}
		break;
	case 5:
        cout << "delete record";
		// deleteRecord();
		break;
	case 6:
        cout << "search record";
		// search();
		break;
	case 7:
        cout << "login info";
		// viewLoginInfo();
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
        user = nullptr;
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