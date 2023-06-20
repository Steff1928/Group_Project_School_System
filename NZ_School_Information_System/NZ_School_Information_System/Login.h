#pragma once
#include <string>
class Login
{
private:
	std::string userName;
	std::string password; 
	int loginAttempts = 3;
public:
	void userLogin();
	void userLogout();
};

