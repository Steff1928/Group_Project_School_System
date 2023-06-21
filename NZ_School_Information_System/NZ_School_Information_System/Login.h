#pragma once
#include <string>
class Login
{
private:
	std::string userName;
	std::string password; 
	int loginAttempts = 3;
	bool beginTimer = false;
	float seconds = 10.0f;
	clock_t start = 0;
public:
	void userLogin();
	bool userLogout();
};

