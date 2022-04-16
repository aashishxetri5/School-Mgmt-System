#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//Global variable declaration

//Function Decalrations
void welcome();

int main() {
    /*
	- To set the width and height of window to 1200px and 650px respectively. 
	- This code works in windows only.
	*/
	HWND wh = GetConsoleWindow();
	MoveWindow(wh, 40, 20, 1200, 650, TRUE);

	welcome();

    getch();
    return 0;
}

void welcome(){
	system("cls");
    printf("\t School Management System\t\n");
    printf("\t**************************\n\n");
//    if(who == NULL){
    	printf("\t<== Login ==>\n");	
//	}else{
//    	printf("\t<== %s Panel ==>\n", who);
//	}
}
