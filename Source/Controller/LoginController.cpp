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
            ifstream student_user("Student.dat", ios::in);

            //check the username from the file 
            User temp;
            int flag = 0;

            if(!student_user){
                cout << "\nFile not found!";
                cout << "In the login controller.";
                exit(1);
            }
            while(!student_user.eof()){
                student_user >> temp;
                if(temp.get_username().compare(user->get_username()) == 0 && temp.get_password().compare(user -> get_password()) == 0){
                    return true;
                }
            }
            return false;

        }

        if(user->getUserType().compare("Staff") == 0) {
            //filename = student.dat; //(This will be done later.)
            ifstream staff_user("Staff.dat", ios::in);

            //check the username from the file 
            User temp;
            int flag = 0;

            while(!staff_user.eof()){
                staff_user >> temp;
                if(temp.get_username().compare(user->get_username()) == 0 && temp.get_password().compare(user -> get_password()) == 0){
                    return true;
                }
            }
            return false;

        }

        /*
        Compares the username and the password with that of the data in file.
        If matched, the compare() returns 0 else it returns -1. On this basis the login is validated.
        */
        if(!user->get_username().compare("User") && !user->get_password().compare("123")) {
            cout << "\n\tHurray!! Login Successful.\n\n\t";
            return true;
        }

        return false;
        
    }

    void addLoginCredential(string username, string password);

};

