#pragma once
#include <string>
#include "Parent.h"
#include "Login.h"

class Admin
{
private:
	std::string userName;
	std::string password;
	Parent parent;
	int classroom;

public:
	void displayAdminScreen();
	void viewClassRecords();
	void viewParentRecords();
	void generateReportsScreen();
	void initialiseAccount();
	Admin();
};

