#pragma once
#include <string>
class Parent
{
private:
	std::string fullName;
	char gender;
	std::string dob;
	std::string email;
	std::string childName;
	int childClass;
	std::string emergencyContactName;
	int emergencyContactNum;
	std::string userName;
	std::string password;
public:
	void displayParentScreen();
	void viewChildReport();
	void viewNotices();
	void parentSignUp();
	Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, 
		std::string _childName, int _childClass, std::string _emergencyContactName,	
		int _emergencyContactNum, std::string _userName);
	Parent();

};

class Child : Parent
{
	std::string childName;
	int childClass;
	std::string emergencyContactName;
	int emergencyContactNum;
};

