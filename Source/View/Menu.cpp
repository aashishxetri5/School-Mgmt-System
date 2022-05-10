//This shall contain functions for the menu.
#include <conio.h>
#include <cstdio>
#include <windows.h>

#include "..\Controller\LoginController.cpp"
#include "..\Controller\registration.cpp"
#include "..\Controller\DataController.cpp"

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);  
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

//void fontsize(int a, int b){
//	static CONSOLE_FONT_INFOEX  fontex;
//     GetCurrentConsoleFontEx(hOut, 0, &fontex);
//    // fontex.FontWeight = 700;
//     fontex.dwFontSize.X = a;
//     fontex.dwFontSize.Y = b;
//     SetCurrentConsoleFontEx(hOut, NULL, &fontex);
//}

void gotoxy(int x, int y){

	COORD CRD;
	CRD.X = x;
	CRD.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);	

}



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
	int y_cord = 10;

	gotoxy(50, ++y_cord );
//	fontsize(40, 40);
    cout << "\t School Management System\n";
    gotoxy(50, ++y_cord );
	cout << "\t**************************\n\n";
	gotoxy(54, ++y_cord );
    if(loggedInUserType.length() == 0){
	    cout << "\t<== Login ==>\n";
	}else{
        cout << "\t<== " << loggedInUserType << " Panel ==>\n";
 	}
}

/* lets user select which  */
int Menu::loginMenu() {
	
	int y_cord = 15;
	gotoxy(50, y_cord);
    cout << "\t1. Student Login";
	gotoxy(50, ++y_cord );
    cout << "\t2. Staff Login";
	gotoxy(50, ++y_cord );
    cout << "\t3. Accounts Login";
	gotoxy(50, ++y_cord );
    cout << "\t0. Exit\n";
	gotoxy(50, y_cord += 2);
    cout << "\tEnter your choice: ";
    cin >> menuChoice;
        
    return menuChoice;
}

//take credentials
bool Menu::login(User *user) {
	int y_cord = 21;
    string temp_data = "";
    char temp;

	gotoxy(50, y_cord);
    cout << "\tEnter your username: ";
	cin >> temp_data;
    user->set_username(temp_data);

	gotoxy(50, y_cord += 2);
    cout << "\tEnter your password: ";
    /* Accepts Password and displays '*' instead of entered character. */
	temp_data="";
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
		gotoxy(50, y_cord += 2);
        cout << "\tOopsies!! Login Failed.\n\n\t";
		gotoxy(50, y_cord + 2);
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
	int y_cord = 15;

	gotoxy(50, ++y_cord );
	cout <<"\t1. View Record(s)";
	gotoxy(50, ++y_cord );
	cout <<"\t2. Update Record\n";
        
    /* Restricting Staffs from viewing marksheet*/
	if( user->getUserType().compare("Staff") != 0){
		gotoxy(50, y_cord + 1);
	    cout <<"\t3. Show Marksheet\n";
	}

	gotoxy(50, ++y_cord );
	/* Only administrative users will be able to access these options. */
	if( !user->getUserType().compare("Admin")){
	    cout << "\t4. Add Record(s)";
		gotoxy(50, ++y_cord );
	    cout << "\t5. Delete Record";
		gotoxy(50, ++y_cord );
	    cout << "\t6. Search Record";
		gotoxy(50, ++y_cord );
	    cout << "\t7. View Login Information";
		gotoxy(50, ++y_cord );
	    cout << "\t8. Save Marks";
		gotoxy(50, ++y_cord );
		
	}

	cout << "\t9. Change Password\n";
	gotoxy(50, ++y_cord );
	cout << "\t10.Logout\n";
	gotoxy(50, ++y_cord );
	cout << "\t0. Exit\n";
	gotoxy(50, ++y_cord );
	cout << "\tEnter your choice: ";
	cin >> menuChoice;
    
	/* Prevents Staff members from accessing Administrative Controls. */
	if( user->getUserType().compare("Staff") == 0 && menuChoice == 3){
		gotoxy(50, y_cord + 2);
	    cout <<"\n\tInvalid input...\n\t";
		gotoxy(50, ++y_cord);
	    system("pause");
	    system("cls");
        return false;
            
	}else if( (!user->getUserType().compare("Student") || !user->getUserType().compare("Staff")) && (menuChoice > 3 && menuChoice < 10)){
        /* Preventing Students and Staffs from accessing Administrative Controls. */
		gotoxy(50, y_cord += 2);
	    cout <<"\tInvalid input...\n\t";
		gotoxy(50, y_cord + 2);
	    system("pause");
	    system("cls");
        return false;
	}

    return performRequestionOperation(user);
}

// This method will call the respective method from any other class which implements the functionality of the requested operation.
bool Menu::performRequestionOperation(User *user) {
	char resp;
	DataController dc;
    switch(menuChoice){
	case 1:
		if(!user->getUserType().compare("Admin") ) {
			dc.viewGeneralRecord(user->getUserType());
		} 
		else {
			dc.getLoggedUserInfo(user);
			
		}
		dc.~DataController();
		system("pause");
		system("cls");
		mainOptions(user);
		break;
	case 2:
		// if(!user->getUserType().compare("Admin") ){
        //     cout << "udpate admin record";
		// 	dc.updateRecord();
		// } else {
        //     cout << "udpate std/student record";
		// 	dc.up;
		// }
		dc.updateRecord(user->getUserType());
		system("pause");
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
		dc.deleteRecord();
		dc.~DataController();
		break;
	case 6:
        cout << "search record";
		dc.search();
		break;
	case 7:
		DataController dc;
		dc.viewLoginInfo(); 		///--> will open the login file
		break;
	case 8:
        cout << "save marks";
		// saveMarks();
		break;
	case 9:
        cout << "change password";
		dc.changePassword(user);
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

