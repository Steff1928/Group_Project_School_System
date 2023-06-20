#pragma once
#include <string>
#include "Student.h"
#include "Login.h"

class Teacher
{
private:
	std::string fullName;
	char gender;
	std::string dob;
	std::string email;
	std::string contactNum;
	int classroomNum;
	std::string teachingYear;
	Student tempStudentData;
	std::string userName;
	std::string password; // STEPHEN: Ask Liam/Lawrence about how to utilise the login class to use password as sign up detail
	Login login;
public:
	void displayTeacherScreen();
	void recordsScreen();
	void addStudent();
	void editStudent();
	void removeStudent();
	void updateStudent();
	void viewRecord();
	void teacherSignUp();
	Teacher(std::string _fullName, char _gender, std::string _dob, std::string _email, 
		std::string _contactNum, int _classroomNum, std::string _teachingYear, 
		std::string _userName, std::string _password);
	Teacher();
};

