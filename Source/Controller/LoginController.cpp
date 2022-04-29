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
    bool isValidUser(User *user) {

         if(user->getUserType().compare("Student") == 0) {
            //filename = student.dat; //(This will be done later.)
            ifstream student_login_file("Login_Std.dat", ios::in|ios::app);

        //     //check the username from the file 
            User user_data;
         //   Student student_data;
            int flag = 0;

            if(!student_login_file){
                cout << "\nFile not found!";
                exit(1);
            }

            student_login_file.seekg(0, ios::beg);
            
            while(!student_login_file.eof()){
                student_login_file >> user_data;
                if(!user_data.get_username().compare(user->get_username()) && !user_data.get_password().compare(user -> get_password()) ){
                    student_login_file.close();
                    return true;
                }
            }
            student_login_file.close();
            return false;
            


        }

        if(user->getUserType().compare("Staff") == 0) {

            ifstream staff_login_file("login_Staff.dat", ios::in);

            User user_data;

            if(!staff_login_file){
                cout << "\nFile not found!";
                exit(1);
            }
            while(!staff_login_file.eof()){
                staff_login_file >> user_data;
                if(!user_data.get_username().compare(user->get_username()) && !user_data.get_password().compare(user ->get_password()) ){
                    staff_login_file.close();
                    return true;
                }
            }
            staff_login_file.close();
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

