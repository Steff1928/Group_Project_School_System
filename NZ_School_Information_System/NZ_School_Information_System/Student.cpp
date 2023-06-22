#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Student.h"
using namespace std;

vector<Student> students;

void Student::getRecord()
{
	
}

void Student::saveData(string line)
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
	getline(cin >> ws, learningProgress);

	ofstream writeClassroom;
	writeClassroom.open("Classes/room_" + line + ".txt", ios_base::app);

	writeClassroom << studentId << "," << fullName << "," << gender << "," << math << "," << science << "," << writing << ","
		<< reading << "," << other << "," << learningProgress << "\n" << "*";
	
	writeClassroom.close();

	ifstream readClassroom("Classes/room_" + line + ".txt");
	string lineTwo;

	while (getline(readClassroom, lineTwo, ','))
	{
		if (lineTwo == to_string(studentId))
		{
			studentId++;
		}
	}	
	readClassroom.close();
}

Student::Student()
{
	studentId = 1;
}
