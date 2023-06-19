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
	void viewClassRecords();
	void viewParentRecords();
	void initialiseAccount();
	Admin();
};

