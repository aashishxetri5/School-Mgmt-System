#include "../Entity/User.cpp"

class LoginController {

public:
    /*
    Recevies the address of the user object and checks if the credentials are valid. If yes, the function returns true.
    Otherwise the function returns false which indicates invalid login.

    Address is used so that the memory consumption is low. Creating new object would allocate new memory location each time
    object is created. This way, we pass only the memory location so that no any new memory is allocated.
    */
    bool isValidUser(User *user) {

        if(user->getUserType().compare("Student") == 0) {
            //filename = student.dat; //(This will be done later.)
        }

        /*
        Compares the username and the password with that of the data in file.
        If matched, the compare() returns 0 else it returns -1. On this basis the login is validated.
        */
        if(!user->get_username().compare("User") && !user->get_password().compare("123456789")) {
            cout << "\n\tHurray!! Login Successful.\n\n\t";
            return true;
        }

        return false;
        
    }

};