#include <iostream>
#include <fstream>
#include <string>
#include "Parent.h"
using namespace std;

void Parent::displayParentScreen()
{

}

void Parent::viewChildReport()
{

}

void Parent::viewNotices()
{

}

void Parent::parentSignUp()
{
	int childAmount = 0;
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
		cout << "Child" << i;
		cout << "Child's full name: ";
		getline(cin >> ws, childName);
		cout << "Child's classroom number: ";
		cin >> childClass;
		cout << "Emergency Contact Caregiver's Full Name: ";
		cin >> emergencyContactName;
		cout << "Emergency Contact Number: ";
		cin >> emergencyContactNum;
	}
}

Parent::Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum,
	std::string _childName, int _childClass, std::string _emergencyContactName, 
	int _emergencyContactNum, std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	childName = _childName;
	childClass = _childClass;
	emergencyContactName = _emergencyContactName;
	emergencyContactNum = _emergencyContactNum;
	userName = _userName;
}

Parent::Parent()
{

}
