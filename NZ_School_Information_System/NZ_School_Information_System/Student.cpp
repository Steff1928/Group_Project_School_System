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

/// <summary>
/// Prompt the user to enter data for a student and save it to a class file.
/// (This will be called when a teacher wants to add a student so their data will be saved to that class)
/// </summary>
/// <param name="line">- Gets the designated class number from the teacher registration file to write the data in a class file</param>
void Student::saveData(string line)
{
	cout << "\nStudent Name: ";
	getline(cin >> ws, fullName);
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	gender = tolower(gender);

	cout << "\nMarks (0 - 100)";
	cout << "\n---------------\n";
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
	writeClassroom << studentId << "," << fullName << "," << gender << "," << "M:" << math << "," << "S:" << science << "," << "W:" << writing << ","
		<< "R:" << reading << "," << "O:" << other << "," << "1:" << learningProgress << ",2:n/a" << ",3:n/a" << ",4:n/a" << "\n" << "*";
	
	writeClassroom.close();

	ofstream writeCount("student_count.txt");
	writeCount << count;
	writeCount.close();
}

// Intialise the values for Student
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
