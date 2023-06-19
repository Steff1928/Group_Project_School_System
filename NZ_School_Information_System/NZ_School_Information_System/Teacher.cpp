#include <iostream>
#include <fstream>
#include <string>
#include "Teacher.h"

using namespace std;

void Teacher::addStudent()
{

}

void Teacher::editStudent()
{

}

void Teacher::removeStudent()
{

}

void Teacher::updateStudent()
{

}

void Teacher::viewRecord()
{

}

void Teacher::teacherSignUp()
{
	system("CLS");
	ofstream writeFile;
	writeFile.open("Sign_Up_And_Login_Details/teacher_registration.txt", ios_base::app);
	cout << "********************\n";
	cout << "Teacher Registration\n";
	cout << "********************\n";
	cout << "\nFull name: ";
	getline(cin >> ws, fullName);
	cout << "\nGender (m = male, f = female, o = other): ";
	cin >> gender;
	cout << "\nDOB (dd/mm/yy): ";
	cin >> dob;
	cout << "\nEmail: ";
	cin >> email;
	cout << "\nContact Number: ";
	cin >> contactNum;
	cout << "\nAssigned Classroom Number: ";
	cin >> classroomNum;
	cout << "\nAssigned Year Group: ";
	getline(cin >> ws, teachingYear);
	writeFile << fullName << "," << gender << "," << dob << "," << email << "," << contactNum << "," << classroomNum
		<< "," << teachingYear << '\n';
	cout << "\n\n";
	writeFile.close();
	system("pause");
}

Teacher::Teacher(std::string _fullName, char _gender, std::string _dob, std::string _email, 
	std::string _contactNum, int _classroomNum, std::string _teachingYear, 
	std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	classroomNum = _classroomNum;
	teachingYear = _teachingYear;
}

Teacher::Teacher()
{

}
