#include <iostream>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include "Login.h"
#include "Teacher.h"
#include "Admin.h"
using namespace std;

// TODO: Add login timer (Use temp function for now that resets loginAttempts each time the user goes to the menu
void Login::userLogin()
{
	char confirmAnswer;
	//float seconds;
	ifstream readTeacher;
	ifstream readAdmin;
	ifstream readParent;
	
	Teacher teacherLogin;
	Admin adminLogin;
	Parent parentLogin;
	string line;

	// Temp function to reset login attempts once the user exits back to the menu and has no login attempts left
	if (loginAttempts <= 0) 
	{
		loginAttempts = 3;
	}

	do
	{
		/*float seconds = 10.0f - static_cast<time_t>(clock() / 1000);
		if (seconds <= 0)
		{
			loginAttempts = 3;
		}*/
		system("CLS");
		// Set confirmAnswer back to no by default so the loop does not run again after the user is finished in 
		// their screen
		confirmAnswer = 'n'; 
		cout << "************\n";
		cout << "Yoobee Login\n";
		cout << "************\n";
		readTeacher.open("Sign_Up_And_Login_Details/teacher_registration.txt");
		readAdmin.open("Sign_Up_And_Login_Details/admin_login.txt");
		readParent.open("Sign_Up_And_Login_Details/parent_registration.txt");

		cout << "\nUsername: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;
		string entry = userName + password;
		bool loginAgain = false;

		while (readTeacher.is_open() && readAdmin.is_open() && readParent.is_open())
		{
			if (!readTeacher.eof() && !readAdmin.eof() && !readParent.eof() && loginAttempts > 0)
			{
				// If there is a match in the "teacher_registration" file, login as a teacher
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
				// If there is a match in the "admin_login" file, login as an admin
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
				while (getline(readParent, line, ','))
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
			else // If there are no matches, minus a login attempt and notify the user they could find their account
			{
				loginAttempts--;
				if (loginAttempts <= 0)
				{
					cout << "\nToo many failed attempts, please try again later.\n";
				}
				else
				{
					cout << "\nInvalid username or password\n\n";
				}
				loginAgain = true;
				break;
			}
		}
		if (loginAgain)
		{
			cout << "Attempt to login again? (y/n): ";
			cin >> confirmAnswer;
			readTeacher.close();
			readAdmin.close();
			readParent.close();
		}
	} while (confirmAnswer == 'y');
	cout << "\n";
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
		system("pause");
		return true;
	}
	return false;
}
