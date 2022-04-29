#include <windows.h>

#include "../View/Menu.cpp"

//Global variable declaration

// Variable and object Declaration

User *user = new User();
int Menu::isLoggedOut = 0; //Used to check whether the current user is logged out.

int main() {
    /*
	- To set the width and height of window to 1200px and 650px respectively. 
	- This code works in windows only.
	*/
	HWND wh = GetConsoleWindow();
	MoveWindow(wh, 40, 20, 1200, 650, TRUE);

	Menu menu;
	menu.welcome(user->getUserType());

	switch(menu.loginMenu()) {
		case 1:
			user->setUserType("Student");
        	break;
    	case 2:
    	    user->setUserType("Staff");
    	    break;
    	case 3:
			user->setUserType("Admin"); 
    	    break;
    	case 0:
    		cout << "\n\tExiting Program...";
    		exit(0);
    	default:
    	    cout << "\n\tInvalid Choice!!\n\t";
    	    system("pause");
    	    main();
	}

	if(!menu.login(user)) {
		delete user;
		user = nullptr;
		user = new User(); //Assigning new user. This resets the user object.
		Menu::isLoggedOut = 0;
		main();

	} else {
		system("pause");
		
		//Keeps calling the mainOptions (the main menu) until a valid menu option is selected.
		while( true ) {
			if(!menu.mainOptions(user)){
				break;
			}
		}

		//If logged out, re-login process starts.
		if(Menu::isLoggedOut == 1) {
		//	user = new User();
		//	cout << user->getUserType();
			main();
		}
	}

    getch();
    return 0;
}


