#pragma once
#include <string>
class Student
{
private:
	std::string fullName;
	char gender;
	int math;
	int science;
	int writing;
	int reading;
	int other;
	std::string learningProgress;
	int studentId;
public:
	void getRecord();
	void saveData();
};

