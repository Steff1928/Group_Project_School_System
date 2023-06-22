#pragma once
#include <string>
class Login
{
private:
	std::string password; 
	int loginAttempts = 3;
	bool beginTimer = false;
	float seconds = 10.0f;
	clock_t start = 0;
public:
	std::string userName;
	void manageLoginAttempts(bool& loginAgain);
	void userLogin();
	bool userLogout();
};

