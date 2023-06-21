#include <iostream>
#include <fstream>
#include <string>
#include "Teacher.h"
#include "Login.h"

using namespace std;

void Teacher::displayTeacherScreen()
{
	system("CLS");
	int choice;

	cout << "************************************\n";
	cout << "Yoobee Portal - Logged in as Teacher\n";
	cout << "************************************\n";
	cout << "\n1. Student Records Options"
		<< "\n2. Logout\n";
	cout << "\nEnter corresponding number for selection: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		recordsScreen();
		break;
	case 2:
		if (!login.userLogout())
		{
			displayTeacherScreen();
		}
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
		displayTeacherScreen();
	}
}

void Teacher::recordsScreen()
{
	system("CLS");
	int choice;

	cout << "***************\n";
	cout << "Student Records\n";
	cout << "***************\n";

	cout << "\n1. Add Student"
		<< "\n2. Edit Record"
		<< "\n3. Delete Record"
		<< "\n4. Update Record"
		<< "\n5. View Records"
		<< "\n6. Back\n";
	cout << "\nEnter corresponding number for selection: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		addStudent(); // TODO: Allow teachers to add students to their class and save data in a file
		recordsScreen();
		break;
	case 2:
		editRecord(); // TODO: Allow teachers to edit student records and modify data
		recordsScreen();
		break;
	case 3:
		removeStudent(); // TODO: Allow teachers to remove a student and all of their data from their class
		recordsScreen();
		break;
	case 4:
		updateRecord(); // TODO: Allow teachers to add new/update a students learning progress for each term
		recordsScreen();
		break;
	case 5:
		viewRecords(); // TODO: Allow the teacher to view all the records of students in their class
		recordsScreen();
		break;
	case 6:
		displayTeacherScreen();
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
	}
}

void Teacher::addStudent()
{

}

void Teacher::editRecord()
{

}

void Teacher::removeStudent()
{

}

void Teacher::updateRecord()
{

}

void Teacher::viewRecords()
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
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	cout << "DOB (dd/mm/yy): ";
	cin >> dob;
	cout << "Email: ";
	cin >> email;
	cout << "Contact Number: ";
	cin >> contactNum;
	cout << "Assigned Classroom Number: ";
	cin >> classroomNum;
	cout << "Assigned Year Group: ";
	getline(cin >> ws, teachingYear);
	cout << "\n\n";

	system("pause");
	
	while (true)
	{
		system("CLS");
		cout << "***********************************\n";
		cout << "Teacher Registration - Account Info\n";
		cout << "***********************************\n";
		cout << "\nUsername: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;
		string confirmPassword;
		cout << "Confirm Password: ";
		cin >> confirmPassword;
		if (password == confirmPassword)
		{
			cout << "Successfully signed up as a teacher!\n\n";
			writeFile << fullName << "," << gender << "," << dob << "," << email << "," << contactNum << "," << classroomNum
				<< "," << teachingYear << "," << userName << password << ",\n";
			writeFile.close();
			system("pause");
			displayTeacherScreen();
			break;
		}
		else
		{
			cout << "Passwords do not match, please re-enter account info\n\n";
			system("pause");
		}
	}
	writeFile.close();
}

Teacher::Teacher(std::string _fullName, char _gender, std::string _dob, std::string _email, 
	std::string _contactNum, int _classroomNum, std::string _teachingYear, 
	std::string _userName, std::string _password)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	classroomNum = _classroomNum;
	teachingYear = _teachingYear;
	password = _password;
}

Teacher::Teacher()
{

}
