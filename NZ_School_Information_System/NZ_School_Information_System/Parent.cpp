#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parent.h"
#include "Login.h"
using namespace std;

void Parent::displayParentScreen()
{
	int choice;
	system("CLS");
	cout << "***********************************           Welcome: [Parent Name]\n";
	cout << "Yoobee Portal - Logged in as Parent           ----------------------\n";
	cout << "***********************************\n\n";
	cout << "1. View Child Record\n" 
		 << "2. View School notices\n" 
		 << "3. Logout\n";
	cout << "\nEnter corresponding number for the selection: ";
	cin >> choice;
	switch (choice) 
	{
	case 1:
		viewChildReport();
		displayParentScreen();
		break;
	case 2:
		viewNotices();
		displayParentScreen();
		break;
	case 3:
		if (!login.userLogout())
		{
			displayParentScreen();
		}
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
		displayParentScreen();
	}
}


void Parent::viewChildReport()
{
	string childName;
	system("CLS");
	cout << "************\n";
	cout << "Child Record\n";
	cout << "************\n\n";
	cout << "Enter Child's Full name: ";
	getline(cin >> ws, childName);
	cout << "\nChild Name: "<<  "Temp Name" << "\n";
	cout << "Gender: " << "Temp Gender" << "\n\n";

	cout << "Marks\n";
	cout << "------------------\n";
	cout << "Maths: " << "  Temp Score" << "\n";
	cout << "Science: " << "Temp Score" << "\n";
	cout << "Reading: " << "Temp Score" << "\n";
	cout << "Writing: " << "Temp Score" << "\n";
	cout << "Other: " << "  Temp Score" << "\n\n";
	system("pause");
}

void Parent::viewNotices()
{
	system("CLS");
	cout << "**************\n";
	cout << "School Notices\n";
	cout << "**************\n\n";
	cout << "Current Notices:\n\n";
	cout << "[Notice of Information Details]\n";
	cout << "[Notice of Information Details]\n";
	cout << "[Notice of Information Details]\n\n";
	system("pause");
}

void Parent::parentSignUp()
{
	Child child;
	vector<Child> childData;
	int childAmount = 0;
	string userInput;
	system("CLS");
	ofstream writeFile;
	writeFile.open("Sign_Up_And_Login_Details/parent_registration.txt", ios_base::app);

	cout << "*******************\n";
	cout << "Parent Registration\n";
	cout << "*******************\n";
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
	cout << "\n\n";

	system("pause");
	system("CLS");

	cout << "********************************\n";
	cout << "Parent Registration - Child Info\n";
	cout << "********************************\n";
	cout << "\nNumber of children attending Yoobee: ";
	cin >> childAmount;

	for (int i = 0; i < childAmount; i++)
	{
		cout << "Child " << i+1 << "\n";
		cout << "Child's full name: ";
		getline(cin >> ws, child.childName);
		cout << "Child's classroom number: ";
		cin >> child.childClass;
		cout << "Emergency Contact Caregiver's Full Name: ";
		getline(cin >> ws, child.emergencyContactName);
		cout << "Emergency Contact Number: ";
		cin >> child.emergencyContactNum;
		cout << "\n";
		childData.push_back({ child.childName,child.childClass,child.emergencyContactName,child.emergencyContactNum });
	}
	system("pause");

	while (true)
	{
		system("CLS");
		cout << "***********************************\n";
		cout << "Parent Registration - Account Info\n";
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
			cout << "Successfully signed up as a parent!\n\n";
			writeFile << userName << "*" << password << "," << fullName << "," << gender << "," << dob << "," << email << "," << contactNum;
			for (int i = 0; i < size(childData); i++)
			{
				writeFile << "\n" << childData[i].childName << "," << childData[i].childClass << "," << childData[i].emergencyContactName <<
					"," << childData[i].emergencyContactNum;
			}
			writeFile << endl <<"*";
			writeFile.close();
			system("pause");
			displayParentScreen();
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

Parent::Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	userName = _userName;
}

Parent::Parent()
{

}

Parent::Child::Child(std::string _childName, int _childClass, std::string _emergencyContactName, std::string _emergencyContactNum)
{
	childName = _childName;
	childClass = _childClass;
	emergencyContactName = _emergencyContactName;
	emergencyContactNum = _emergencyContactNum;
}

Parent::Child::Child()
{
}
