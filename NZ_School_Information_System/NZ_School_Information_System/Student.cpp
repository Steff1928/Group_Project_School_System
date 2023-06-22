#include <iostream>
#include <vector>
#include <string>
#include "Student.h"
using namespace std;

vector<Student> students;

void Student::getRecord()
{
	
}

void Student::saveData()
{
	cout << "\nStudent Name: ";
	getline(cin >> ws, fullName);
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;

	cout << "\nMarks\n";
	cout << "----------\n";
	cout << "Maths: ";
	cin >> math;
	cout << "Science: ";
	cin >> science;
	cout << "Writing: ";
	cin >> writing;
	cout << "Reading: ";
	cin >> reading;
	cout << "Other: ";
	cin >> other;

	cout << "\nTerm 1 Observations\n";
	cout << "-------------------\n";
	cout << "Learning Progress (Achieved/Progressing/Needs Help): ";
	cin >> learningProgress;


}

Student::Student()
{

}
