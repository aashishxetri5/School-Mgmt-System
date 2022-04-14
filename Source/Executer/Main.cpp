#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main() {
    /*
	- To set the width and height of window to 1200px and 650px respectively. 
	- This code works in windows only.
	*/
	HWND wh = GetConsoleWindow();
	MoveWindow(wh, 40, 20, 1200, 650, TRUE);


    getch();
    return 0;
}