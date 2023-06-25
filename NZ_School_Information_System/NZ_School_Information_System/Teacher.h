#pragma once
#include <string>
#include "Student.h"
#include "Login.h"

// Intialise the Teacher class for teacher registration and classroom initialisation
class Teacher
{
private:
	// Define variables, exclusively used for teacher registration
	std::string fullName;
	char gender = 0;
	std::string dob;
	std::string email;
	std::string contactNum;
	int classroomNum = 0;
	std::string teachingYear;
	Student tempStudentData;
	std::string userName;
	std::string password; 
public:
	// Declare functions to be used elsewhere when deemed necessary
	void checkLineInTeacherFile(std::string& line, int lineNum);
	void displayTeacherScreen();
	void recordsScreen();
	std::string displayGender(char gender);
	void addStudent();
	void editRecord();
	void removeStudent();
	void updateRecord();
	void viewRecords();
	void teacherSignUp();
	Teacher(std::string _fullName, char _gender, std::string _dob, std::string _email, 
		std::string _contactNum, int _classroomNum, std::string _teachingYear, 
		std::string _userName, std::string _password);
	Teacher();
};