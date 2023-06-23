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

	cout << "\nMarks (0 - 100)\n";
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

	ifstream readCount("student_count.txt");
	string count;
	int idCount = 0;

	while (getline(readCount, count))
	{
		idCount = stoi(count);
		idCount++;
		count = to_string(idCount);
	}
	readCount.close();

	studentId = idCount;
	writeClassroom << studentId << "," << fullName << "," << gender << "," << math << "," << science << "," << writing << ","
		<< reading << "," << other << "," << learningProgress << "\n" << "*";
	
	writeClassroom.close();

	ofstream writeCount("student_count.txt");
	writeCount << count;
	writeCount.close();
}

Student::Student()
{
	gender = 0;
	math = 0;
	science = 0;
	writing = 0;
	reading = 0;
	other = 0;
	studentId = 1;
}
