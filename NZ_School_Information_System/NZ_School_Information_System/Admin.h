#pragma once
#include <string>
#include "Parent.h"
#include "Login.h"

// Intialise the Admin class to be able to view all data from registered users
class Admin
{
private:
	// Define variables to be used exclusively for admin purposes
	std::string userName;
	std::string password;
	Parent parent;
	Login login;
	int classroom;

public:
	// Declare functions to be used in any source file
	void displayAdminScreen();
	void viewClassRecords();
	void viewParentRecords();
	void generateReportsScreen();
	void generateProgressionReports();
	void generateHelpReports();
	void initialiseAccount();
	Admin();
};

