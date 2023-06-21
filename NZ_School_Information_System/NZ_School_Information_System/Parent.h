#pragma once
#include <string>
#include <vector>
#include "Login.h"
class Parent
{
private:
	std::string fullName;
	char gender = 0;
	std::string dob;
	std::string email;
	std::string contactNum;
	std::string userName;
	std::string password;
	struct Child
	{
		std::string childName;
		int childClass = 0;
		std::string emergencyContactName;
		std::string emergencyContactNum;
		Child(std::string _childName, int _childClass, std::string _emergencyContactName,
			std::string _emergencyContactNum);
		Child();
	};
	Login login;
public:
	void displayParentScreen();
	void viewChildReport();
	void viewNotices();
	void parentSignUp();
	Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, std::string _userName);

	Parent();
};

