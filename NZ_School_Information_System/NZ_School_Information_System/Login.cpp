#include <iostream>
#include <fstream>
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
	// TODO: Fix up login screen (can't figure out functionality)
	while (readTeacher.is_open() && readAdmin.is_open() /*&& readParent.is_open()*/)
	{
		if (!readTeacher.eof() && !readAdmin.eof() /*&& !readParent.eof()*/ && loginAttempts > 0)
		{
			while (getline(readTeacher, line, ','))
			{
				if (line == entry)
				{
					cout << "Successfully logged in!\n\n";
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
					cout << "Successfully logged in!\n\n";
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
					cout << "Successfully logged in!\n\n";
					system("pause");
					parentLogin.displayParentScreen();
					readParent.close();
					break;
				}
			}
		}
		else
		{
			loginAttempts--;
			if (loginAttempts <= 0)
			{
				cout << "Too many failed attempts, please try again later\n\n";
			}
			else
			{
				cout << "Invalid username or password\n\n";
			}
			break;
		}
	}
	system("pause");
	readTeacher.close();
	readAdmin.close();
	readParent.close();
}

void Login::userLogout()
{
	system("CLS");
	cout << "					             ***********\n";
	cout << "					             LOGGING OUT\n";
	cout << "					             ***********\n";
	cout << "\n					     Returning to the Main Menu\n\n";
}
