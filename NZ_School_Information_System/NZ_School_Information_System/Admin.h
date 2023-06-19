#pragma once
#include <string>
#include "Parent.h"
#include "Login.h"

class Admin
{
private:
	std::string userName;
	Parent parent;
	int classroom;

public:
	void viewClassRecords();
	void viewParentRecords();
};

