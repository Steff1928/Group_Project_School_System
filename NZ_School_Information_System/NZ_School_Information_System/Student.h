#pragma once
#include <string>

// Initialise the Student class to manage the record data
class Student
{
private:
	// Define variables to be read and displayed as record data, exclusively
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
	// Define functions to be used outside of this source file, as well as in it
	void getRecord();
	void saveData(std::string line);
	Student();
};

