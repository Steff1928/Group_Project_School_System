#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Login.h"
#include "Teacher.h"
#include "Admin.h"
using namespace std;

void Login::userLogin()
{
	system("CLS");
	cout << "************\n";
	cout << "Yoobee Login\n";
	cout << "************\n";

	cout << "\nUsername: ";
	cin >> userName;
	cout << "Password: ";
	cin >> password;

	string entry = userName + password;

	ifstream readTeacher;
	ifstream readAdmin;
	ifstream readParent;
	readTeacher.open("Sign_Up_And_Login_Details/teacher_registration.txt");
	readAdmin.open("Sign_Up_And_Login_Details/admin_login.txt");
	readParent.open("Sign_Up_And_Login_Details/parent_login.txt");
	
	Teacher teacherLogin;
	Admin adminLogin;
	Parent parentLogin;
	string line;
	while (readTeacher.is_open() && readAdmin.is_open() /*&& readParent.is_open()*/)
	{
		if (!readTeacher.eof() && !readAdmin.eof() /*&& !readParent.eof()*/ && loginAttempts > 0)
		{
			while (getline(readTeacher, line, ','))
			{
				if (line == entry)
				{
					cout << "\nSuccessfully logged in!\n\n";
					loginAttempts = 3;
					system("pause");
					teacherLogin.displayTeacherScreen();
					readTeacher.close();
					break;
				}
			}
			while (getline(readAdmin, line, ','))
			{
				if (line == entry)
				{
					cout << "\nSuccessfully logged in!\n\n";
					loginAttempts = 3;
					system("pause");
					adminLogin.displayAdminScreen();
					readAdmin.close();
					break;
				}
			}
			// LIAM: Create parent screens and then this can be hooked up to the parent screen if a parent logs in
			while (getline(readAdmin, line, ','))
			{
				if (line == entry)
				{
					cout << "\nSuccessfully logged in!\n\n";
					loginAttempts = 3;
					system("pause");
					parentLogin.displayParentScreen();
					readParent.close();
					break;
				}
			}
		}
		else
		{
			if (loginAttempts <= 0)
			{
				cout << "\nToo many failed attempts, please try again later\n\n";
			}
			else
			{
				cout << "\nInvalid username or password\n\n";
			}
			loginAttempts--;
			break;
		}
	}
	system("pause");
	readTeacher.close();
	readAdmin.close();
	readParent.close();
}

bool Login::userLogout()
{
	char confirmAnswer;
	cout << "\nAre you sure you want to logout? (y/n): ";
	cin >> confirmAnswer;
	if (confirmAnswer == 'y')
	{
		system("CLS");
		cout << "					             ***********\n";
		cout << "					             LOGGING OUT\n";
		cout << "					             ***********\n";
		cout << "\n					     Returning to the Main Menu\n\n";
		return true;
	}
	return false;
}
