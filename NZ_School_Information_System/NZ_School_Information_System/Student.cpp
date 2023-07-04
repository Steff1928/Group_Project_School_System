#include <iostream>
#include <string>
#include <fstream>
#include "Student.h"
#include "Teacher.h"

using namespace std;

/// <summary>
/// Prompt the user to enter data for a student and save it to a class file.
/// (This will be called when a teacher wants to add a student so their data will be saved to that class)
/// </summary>
/// <param name="line">- Gets the designated class number from the teacher registration file to write the data in a class file</param>
void Student::saveData(const string line)
{
	Teacher teacher;
	cout << "\nStudent Name (or type 'exit' to go back): ";
	getline(cin >> ws, fullName); // Use getline to allow spaces between words
	if (fullName == "exit") // Create an exit function if users don't want to continue signing up
	{
		teacher.recordsScreen();
		return; // Returns an empty value from this function
	}
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	gender = tolower(gender); // Convert uppercase to lowercase in gender in necessary

	// Enter the marks for the student
	cout << "\nMarks (0 - 100)";
	cout << "\n---------------\n";
	cout << "Maths: ";
	cin >> math;
	cout << "Science: ";
	cin >> science;
	cout << "Writing: ";
	cin >> writing;
	cout << "Reading: ";
	cin >> reading;
	cout << "Other: ";
	cin >> other;

	// Enter the learning observation for Term 1 for this student
	cout << "\nTerm 1 Observations\n";
	cout << "-------------------\n";
	cout << "Learning Progress (Achieved/Progressing/Needs Help): ";
	getline(cin >> ws, learningProgress);

	// Create an open a new classroom file (in append mode) to store the new student data (number depends on teachers classroom)
	ofstream writeClassroom;
	writeClassroom.open("Classes/room_" + line + ".txt", ios_base::app);

	// Open a file to edit the total student count to determine the id for each student
	ifstream readCount("student_count.txt");
	string count;
	int idCount = 0;

	// Get the student count in the file an increase it once a student is added
	while (getline(readCount, count))
	{
		idCount = stoi(count);
		idCount++;
		count = to_string(idCount);
	}
	readCount.close();

	// Assign the student count to studentId and write it into the classroom file, along with all the other data
	// Add data for learning observations at the end of the line so teachers can update their students learning progress
	studentId = idCount;
	writeClassroom << studentId << "," << fullName << "," << gender << "," << "M:" << math << "," << "S:" << science << "," << "W:" << writing << ","
		<< "R:" << reading << "," << "O:" << other << "," << "1:" << learningProgress << ",2:n/a" << ",3:n/a" << ",4:n/a" << ",\n" << "*";

	writeClassroom.close(); // Close the classroom file when finished

	// Write the new count into the student count file
	ofstream writeCount("student_count.txt");
	writeCount << count;
	writeCount.close();

	// Notify the user their class has been updated with the new student details
	cout << "\nStudent details have been added to your class (Room " << line << ")\n";
	system("pause");
	teacher.recordsScreen();
}

// Intialise the values for Student
Student::Student()
{
	gender = 0;
	math = 0;
	science = 0;
	writing = 0;
	reading = 0;
	other = 0;
	studentId = 1;
}
