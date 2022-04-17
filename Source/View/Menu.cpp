//This shall contain functions for the menu.
#include <conio.h>

#include "../Controller/LoginController.cpp"

class Menu {
    int menuChoice;
public:

    void welcome(string loggedInUserType) {
	    system("cls");
        cout << "\t School Management System\n";
        cout << "\t**************************\n\n";

        if(loggedInUserType.length() == 0){
    	    cout << "\t<== Login ==>\n";	
	    }else{
   	        cout << "\t<== <<" << loggedInUserType << " Panel ==>\n";
	    }
    }

    int loginMenu() {
    	cout << "\n\t1. Student Login";
        cout << "\n\t2. Teacher Login";
        cout << "\n\t3. Accounts Login";
        cout << "\n\t0. Exit\n";
        cout << "\n\tEnter your choice: ";
        cin >> menuChoice;
        
        return menuChoice;
    }

    //take credentials
    bool login(User *user) {
        string loginPassword = "";
        char temp;

        cout << "\tEnter your username: ";
        user->set_username();

        cout << "\tEnter your password: ";
        /* Accepts Password and displays '*' instead of entered character. */
        while(temp != 13) {
            temp = getch();
            printf("*");
            loginPassword = loginPassword + temp;
        }
        user->set_password(&loginPassword);

        if(!LoginController().isValidUser(user)) {
            cout << "\n\tOopsies!! Login Failed.\n\n\t";
            system("pause");
            return false;
        }
        return true;

    }

};