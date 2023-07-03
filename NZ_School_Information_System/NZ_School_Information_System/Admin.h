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
	// Ensure the admin username and password cannot be changed after program start up with "const"
	const std::string userName = "admin"; 
	const std::string password = "admin";
	Login login;
	Teacher teacher;
	int classroom;

public:
	// Declare functions to be used in any source file
	void displayAdminScreen();
	void viewClassRecords();
	void viewParentRecords();
	void generateReportsScreen();
	void generateReports(const int min, const int max, const std::string reportType);
	void initialiseAccount();
	Admin();
};