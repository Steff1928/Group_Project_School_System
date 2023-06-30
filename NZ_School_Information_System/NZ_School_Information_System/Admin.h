#pragma once
#include <string>
#include "Login.h"
#include "Parent.h"
#include "Teacher.h"

// Intialise the Admin class to be able to view all data from registered users
class Admin
{
private:
	// Define variables to be used exclusively for admin purposes
	std::string userName;
	std::string password;
	Login login;
	Teacher teacher;
	int classroom;

public:
	// Declare functions to be used in any source file
	void displayAdminScreen();
	void viewClassRecords();
	void viewParentRecords();
	void generateReportsScreen();
	void generateReports(int min, int max, std::string reportType);
	void initialiseAccount();
	Admin();
};

