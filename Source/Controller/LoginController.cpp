#include "../Entity/User.cpp"
#include "../Entity/Staff.cpp"
#include "../Entity/Student.cpp"

class LoginController {

public:
    /*
    Recevies the address of the user object and checks if the credentials are valid. If yes, the function returns true.
    Otherwise the function returns false which indicates invalid login.

    Address is used so that the memory consumption is low. Creating new object would allocate new memory location each time
    object is created. This way, we pass only the memory location so that no any new memory is allocated.
    */
    bool isValidUser(User *user);

    void addLoginCredential(string username, string password);

};

bool LoginController::isValidUser(User *user) {

    /*
    Compares the username and the password with that of the data in file.
    If matched, the compare() returns 0 else it returns -1. On this basis the login is validated.
    */
    if(!user->get_username().compare("User") && !user->get_password().compare("123") && !user->getUserType().compare("Admin")) {
        cout << "\n\tHurray!! Login Successful.\n\n\t";
        return true;

    } else {

        ifstream login_file;

        if(user->getUserType().compare("Student") == 0) {
            login_file.open("../Files/Logins/Login_Std.dat", ios::in);
        } else if(user->getUserType().compare("Staff") == 0) {
            login_file.open("../Files/Logins/Login_Staff.dat", ios::in);
        } else {
            login_file.open("../Files/Logins/Login_Admin.dat", ios::in);
        }
        
        //check the username from the file 
        User user_data;
        
        int flag = 0;

        if(login_file){ //If it returns 1, it indicates that the file exists.

            //Checks the validity of login credentails with that in the file.
            while(!login_file.eof()){
                login_file >> user_data;

                if(!user_data.get_username().compare(user->get_username()) && 
                    !user_data.get_password().compare(user -> get_password()) && 
                    user_data.getUserId() == user->getUserId()){
                    login_file.close();
                    cout << "\n\tHurray!! Login Successful.\n\n\t";
                    return true;
                }
            }
        }

        login_file.close();
    }
    return false;
        
}
