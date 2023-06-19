#include <iostream>
#include <fstream>
#include "Login.h"
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

	ifstream readFile;
	readFile.open("Sign_Up_And_Login_Details/teacher_registration.txt");
	string line;
	// TODO: Fix up login screen (can't figure out functionality)
	while (!readFile.eof())
	{
		while (getline(readFile, line, ','))
		{
			cout << line;
			if (line == password)
			{
				cout << "Successfully logged in!\n\n";
				break;
			}
			else
			{
				//cout << "We could not find a match for this account in our system\n\n";
			}
		}
	}
	readFile.close();
	system("pause");
}

void Login::userLogout()
{

}
