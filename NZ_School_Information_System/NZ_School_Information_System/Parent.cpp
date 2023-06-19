#include "Parent.h"

void Parent::viewChildReport()
{

}

void Parent::viewNotices()
{

}

void Parent::parentSignUp()
{

}

Parent::Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, 
	std::string _childName, int _childClass, std::string _emergencyContactName, 
	int _emergencyContactNum, std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	childName = _childName;
	childClass = _childClass;
	emergencyContactName = _emergencyContactName;
	emergencyContactNum = _emergencyContactNum;
	userName = _userName;
}
