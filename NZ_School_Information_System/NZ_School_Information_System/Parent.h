#pragma once
#include <string>
#include <vector>

// Intialise the Parent class to store all the data for parent registration and details for their children
// attending the school
class Parent
{
private:
	// Define variables to be used exclusively for parent registration
	std::string fullName;
	char gender = 0;
	std::string dob;
	std::string email;
	std::string contactNum;
	std::string userName;
	std::string password;
	// Initialise the child data within a nested structure, making it easier for us to count and store the data
	// since parents can have multiple children
	struct Child 
	{
		std::string childName;
		int childClass = 0;
		std::string emergencyContactName;
		std::string emergencyContactNum;
		// Add a constructors to initilaise all the values for the child data
		Child(std::string _childName, int _childClass, std::string _emergencyContactName,
			std::string _emergencyContactNum);
		Child();
	};
public:
	// Declare functions to be used in any source file 
	void checkLineInFile(std::string& line, int lineNum);
	void displayParentScreen();
	void viewChildReport();
	void viewNotices();
	void parentSignUp();
	Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, std::string _userName);
	Parent();
};