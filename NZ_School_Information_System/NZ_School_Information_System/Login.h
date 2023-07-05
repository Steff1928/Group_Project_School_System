#pragma once
#include <string>
#include "Teacher.h"

// Initialise the Login class for managing and comparing inputted data to data in files
class Login
{
private:
	// Define variables exclusively to manage the login functions

	std::string userName;
	std::string password; 
	int loginAttempts = 3;
	bool beginTimer = false;
	float seconds = 10.0f;
	clock_t start = 0;
public:
	// Define attributes that can be used elsewhere aswell as the login source file
	std::string savedUser;
	void manageLoginAttempts(bool& loginAgain);
	bool getMatchInFile(std::ifstream& readTeacher, std::string& line, std::string entry);
	void userLogin();
	bool userLogout();
};

