//This shall contain functions for the menu.
#include <conio.h>

#include "..\Controller\LoginController.cpp"
#include "..\Controller\registration.cpp"

class Menu {
    int menuChoice;
public:

    /* Displays the welcome message on top of the screen */
    void welcome(string loggedInUserType) {
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
    int loginMenu() {
    	cout << "\n\t1. Student Login";
        cout << "\n\t2. Staff Login";
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
        while(true) {
            temp = getch();
            /*Checks if user hit 'Enter'. If yes, the password end is declared by breaking out of the loop. */
            if(temp == 13) {
                break;
            }
            cout <<"*";
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

    //This is the main option. It contains several options like add, update, delete, search, etc.
    bool mainOptions(User *user) {
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
            
	    }else if( (!user->getUserType().compare("Student") || !user->getUserType().compare("Staff")) && (menuChoice >= 3 && menuChoice < 10)){
            /* Preventing Students and Staffs from accessing Administrative Controls. */
	    	cout <<"\n\tInvalid input...\n\t";
	    	system("pause");
	    	system("cls");
            return false;
	    }

        return performRequestionOperation(user->getUserType());

    }

// This method will call the respective method from any other class which implements the functionality of the requested operation.
    bool performRequestionOperation(string userType) {
        switch(menuChoice){
		case 1:
			if(!userType.compare("Admin") ) {
                cout << "view admin record";
				// viewGeneralRecord();
			} else {
                cout << "view student/staff record";
				// getLoggedUserInfo();
			}
			break;
		case 2:
			if(!userType.compare("Admin") ){
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
            cout << "add rec";
			Registration reg;
			reg.get_data(userType);
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
			cout << "\n\tLogging out...\n\t";
            //reset the user object through address.
			system("pause");
			break;
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

};