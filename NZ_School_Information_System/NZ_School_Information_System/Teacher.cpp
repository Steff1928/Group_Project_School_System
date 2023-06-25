#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include "Teacher.h"
#include "Main.h"

using namespace std;

/// <summary>
/// Get the data in the teacher_registration.txt file, read it and display it to the console when necessary
/// </summary>
/// <param name="line"> - Holds the data for the current line in the file</param>
/// <param name="lineNum"> - Tells the program which line to read out</param>
void Teacher::checkLineInFile(string& line, int lineNum)
{
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	while (getline(readFile, line, '*'))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		if (line == login.savedUser)
		{
			for (int i = 0; i < lineNum; i++) // Fixed number used here to loop to a certain line we require in a file
			{
				getline(readFile, line, ',');
			}
			readFile.close();
			break;
		}
	}
}

// Display restricted options for users logged in as a teacher 
void Teacher::displayTeacherScreen()
{
	system("CLS");
	int choice;

	string line;

	checkLineInFile(line, 2); // Get the value of line from the file to display it later

	cout << "************************************           Welcome: " << line << "\n";
	cout << "Yoobee Portal - Logged in as Teacher           --------------------------\n";
	cout << "************************************\n";
	cout << "\n1. Student Records Options"
		<< "\n2. Logout\n";
	cout << "\nEnter corresponding number for selection: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		recordsScreen(); 
		break;
	case 2:
		if (!login.userLogout())
		{
			displayTeacherScreen();
		}
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
		displayTeacherScreen();
	}
}

// Display options for creating a student record
void Teacher::recordsScreen()
{
	system("CLS");
	int choice;

	cout << "***************\n";
	cout << "Student Records\n";
	cout << "***************\n";

	cout << "\n1. Add Student"
		<< "\n2. Edit Record"
		<< "\n3. Delete Record"
		<< "\n4. Update Record"
		<< "\n5. View Records"
		<< "\n6. Back\n";
	cout << "\nEnter corresponding number for selection: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		addStudent();
		recordsScreen();
		break;
	case 2:
		editRecord(); // TODO: Make the editRecord function prompts and functionality
		recordsScreen();
		break;
	case 3:
		removeStudent(); 
		recordsScreen();
		break;
	case 4:
		updateRecord(); // TODO: Make the updateRecord function prompts and functionality
		recordsScreen();
		break;
	case 5:
		viewRecords(); // TODO: Make the viewRecord function prompts and functionality
		recordsScreen();
		break;
	case 6:
		displayTeacherScreen();
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
	}
}

// Allow teachers to add students to their class and save data to a file
void Teacher::addStudent()
{
	system("CLS");
	cout << "*****************************\n";
	cout << "Student Records - Add Student\n";
	cout << "*****************************\n";

	string line;
	checkLineInFile(line, 7);
	tempStudentData.saveData(line);

	cout << "Student details have been added to your class (Room " << line << ")\n";
	system("pause");
}

// Allow teachers to edit student records and modify data
void Teacher::editRecord()
{

}

// Allow teachers to remove a student and all of their data from their class
void Teacher::removeStudent()
{
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	string line, name;
	string path;
	while (getline(readFile, line, '*'))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		if (line == login.savedUser)
		{	
			for (int i = 0; i < 7; i++)
			{
				getline(readFile, line, ',');
			}
			readFile.close();
			break;
		}
	}
	//readFile.open("Classroom_Number_" + line);
	int studentID = 0;
	path = "Classes/room_" + line + ".txt";
	cout << "*******************************\n";
	cout << "Student Records - Delete Record\n";
	cout << "*******************************\n\n";
	cout << "Class Number: " << line << "\n"; //Temp output to track classroom number.
	cout << "Enter a student ID to remove from your class: ";
	//cin >> studentID;
	getline(cin >> ws, name);
	readFile.open(path);
	writeFile.open("Classes/temp.txt");
	while (getline(readFile, line, '*'))
	{
		if (line.substr(0, name.size()) != name)
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			writeFile << "*" << line   << endl;
		}
	}
	readFile.close();
	writeFile.close();
	remove(path.c_str());
	if (rename("Classes/temp.txt", path.c_str()) != 0)
	{
		cout << "Record Removed"; // TEMP
	}
	system("pause");
	return;
}

// Allow teachers to add new/update a students learning progress for each term
void Teacher::updateRecord()
{

}

// Allow the teacher to view all the records of students in their class
void Teacher::viewRecords()
{

}

// Function to manage teacher registration
void Teacher::teacherSignUp()
{
	system("CLS");
	ofstream writeFile("Sign_Up_And_Login_Details/teacher_registration.txt", ios_base::app);
	int classNum = 0;
	
	// Prompt the user to enter all the inital data for teacher registration
	cout << "********************\n";
	cout << "Teacher Registration\n";
	cout << "********************\n";
	cout << "\nFull name: ";
	getline(cin >> ws, fullName);
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	cout << "DOB (dd/mm/yy): ";
	cin >> dob;
	cout << "Email: ";
	cin >> email;
	cout << "Contact Number: ";
	cin >> contactNum;
	cout << "Assigned Classroom Number: ";
	cin >> classroomNum;
	cout << "Assigned Year Group: ";
	getline(cin >> ws, teachingYear);
	cout << "\n\n";

	system("pause");
	
	// Prompt the user to enter data for account info (loop through until password matches confirm password)
	while (true)
	{
		system("CLS");
		cout << "***********************************\n";
		cout << "Teacher Registration - Account Info\n";
		cout << "***********************************\n";
		cout << "\nUsername: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;
		string confirmPassword;
		cout << "Confirm Password: ";
		cin >> confirmPassword;
		if (password == confirmPassword) // Only save the data if confirm password matches the initial password
		{
			cout << "Successfully signed up as a teacher!\n\n";
			writeFile << userName << "*" << password << "," << fullName << "," << gender << "," 
				<< dob << "," << email << "," << contactNum << "," << classroomNum
				<< "," << teachingYear << "," << "\n" << "*";
			login.savedUser = userName;
			writeFile.close();
			system("pause");
			displayTeacherScreen();	
			break;
		}
		else
		{
			cout << "Confirm Password is not the same as Password, please re-enter account info\n\n";
			system("pause");
		}
	}
	writeFile.close();
}

// Initialise all the values
Teacher::Teacher(std::string _fullName, char _gender, std::string _dob, std::string _email, 
	std::string _contactNum, int _classroomNum, std::string _teachingYear, 
	std::string _userName, std::string _password)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	classroomNum = _classroomNum;
	teachingYear = _teachingYear;
	password = _password;
}

Teacher::Teacher()
{

}