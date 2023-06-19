#pragma once
#include <string>
class Login
{
private:
	std::string userName;
	std::string password;
public:
	void userLogin(std::string userName);
	void userLogout();
};

