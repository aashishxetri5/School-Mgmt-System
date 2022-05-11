#ifndef MARKC_CPP
#define MARKC_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../Entity/Marks.cpp"

using namespace std;

class MarksController {

public:

    void saveMarks();

    void displayMarksheet(int studentId);

    void getAllMarksheet();

    void marksHeader();

    void marksheet(Marks temp_marks);

};

void MarksController::saveMarks() {
    string subj1, subj2, subj3, subj4, subj5;
    int userId, mark1, mark2, mark3, mark4, mark5;

    system("cls");

    cout << "\n\tEnter the student's ID: ";
	cin >> userId;

    cin.ignore();
    cout << "\n\tEnter Subject1's title (No Spaces): ";
	cin >> subj1;

	cout << "\n\tEnter marks obtained in " << subj1 << ": ";
	cin >> mark1;
		
    cin.ignore();
    cout << "\n\tEnter Subject2's title (No Spaces): ";
	cin >> subj2;
		
	cout << "\n\tEnter marks obtained in " << subj2 << ": ";
	cin >> mark2;
		
    cin.ignore();
	cout << "\n\tEnter Subject3's title (No Spaces): ";
	cin >> subj3;
		
	cout << "\n\tEnter marks obtained in " << subj3 << ": ";
	cin >> mark3;
			
    cin.ignore();
	cout << "\n\tEnter Subject4's title (No Spaces): ";
	cin >> subj4;
		
	cout << "\n\tEnter marks obtained in " << subj4 << ": ";
	cin >> mark4;
		
    cin.ignore();
	cout << "\n\tEnter Subject5's title (No Spaces): ";
	cin >> subj5;
		
	cout << "\n\tEnter marks obtained in " << subj5 << ": ";
	cin >> mark5;

    Marks *mark = new Marks(userId, subj1, subj2, subj3, subj4, subj5, mark1, mark2, mark3, mark4, mark5);

    fstream marks_file("../Files/Marksheets/Marksheets.dat", ios::out | ios::app);

    if (!marks_file) {
		cout << "\n\tFile not found !!!";
	} else {
		marks_file << *mark << flush;
	}

	marks_file.close();
}

void MarksController::displayMarksheet(int studentId) {
    fstream marks_file("../Files/Marksheets/Marksheets.dat", ios::in);
        
    Marks temp_marks;

    system("cls");
	
    if(!marks_file){
    	cout << "\n\tfile not found";
    } else {
	    marks_file >> temp_marks;
	    while(!marks_file.eof()){
            if(temp_marks.getUserId() == studentId){
	    	    marksheet(temp_marks);
	    	    break;
            }
            marks_file >> temp_marks;
	    }
    }
    marks_file.close();
}

void MarksController::getAllMarksheet() {
    fstream marks_file("../Files/Marksheets/Marksheets.dat", ios::in);
    Marks temp_marks;

    system("cls");
	
    if(!marks_file){
    	cout << "\n\tfile not found";
    } else {
	    marks_file >> temp_marks;
	    marksHeader();
	    while(!marks_file.eof()){
	    	temp_marks.displayData();
	    	marks_file >> temp_marks;
	    }
    }
    marks_file.close();
}

void MarksController::marksHeader() {
    cout << setw(7) << "UserId";
    cout << setw(14) << "Subject1";
    cout << setw(11) << "Mark";
    cout << setw(11) << "Subject2";
    cout << setw(11) << "Mark";
    cout << setw(11) << "Subject3";
    cout << setw(11) << "Mark";
    cout << setw(11) << "Subject4";
    cout << setw(11) << "Mark";
    cout << setw(11) << "Subject5";
    cout << setw(11) << "Mark" << "\n";

	for(int i = 0; i < 125; i++){
	    cout << "-";
	}
	cout << "\n";

}

void MarksController::marksheet(Marks temp_marks) {

    cout << "\n\t**MARKSHEET**";
	cout << "\n\t--------------------------------------------------";
	cout << "\n\t ID: " << temp_marks.getUserId();
	cout << "\t\t Name: " << "Aashish Katwal";

	cout << "\n\t---------------------------------------------------\n";
	
    cout << "\t" << setw(40) << left << temp_marks.getSubj1() << temp_marks.getMark1() << "\n";
	cout << "\t" << setw(40) << left << temp_marks.getSubj2() << temp_marks.getMark2() << "\n";
	cout << "\t" << setw(40) << left << temp_marks.getSubj3() << temp_marks.getMark3() << "\n";
	cout << "\t" << setw(40) << left << temp_marks.getSubj4() << temp_marks.getMark4() << "\n";
	cout << "\t" << setw(40) << left << temp_marks.getSubj5() << temp_marks.getMark5() << "\n";

	cout << "\t---------------------------------------------------";
	
    cout << "\n\tFull Marks: " << temp_marks.getTotal();
	cout << "\n\tPercentage: " << temp_marks.getPercentage();
	cout << "\n\tResult: " << ((temp_marks.getPassOrFail() == 'F') ? "Fail" : "Pass");
    cout << "\n\n\t";
}

#endif