#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Teacher.h"
#include "Main.h"

using namespace std;

/// <summary>
/// Get the data in the teacher_registration.txt file, read it and display it to the console when necessary
/// </summary>
/// <param name="line"> - Holds the data for the current line in the file</param>
/// <param name="lineNum"> - Tells the program which line to read out</param>
void Teacher::checkLineInTeacherFile(string& line, int lineNum)
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

	checkLineInTeacherFile(line, 2); // Get the value of line from the file to display the name of the teacher in the home screen

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
		inputFail();
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
		break;
	case 2:
		editRecord();
		break;
	case 3:
		removeStudent(); 
		break;
	case 4:
		updateRecord();
		break;
	case 5:
		viewRecords();
		break;
	case 6:
		displayTeacherScreen();
		break;
	default:
		inputFail();
		system("pause");
		recordsScreen();
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
	checkLineInTeacherFile(line, 7);
	tempStudentData.saveData(line);
	return;
}

// Allow teachers to edit student records and modify data
void Teacher::editRecord()
{
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	
	string line, id, path, studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, detail, newDetail;
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

	path = "Classes/room_" + line + ".txt";

	cout << "*****************************\n";
	cout << "Student Records - Edit Record\n";
	cout << "*****************************\n";

	cout << "Class Number: " << line << "\n"; // Temp output to track classroom number.

	cout << "\nEnter a Student ID to edit in your class (or type 'exit' to go back): ";
	getline(cin >> ws, id);
	if (id == "exit")
	{
		recordsScreen();
		return;
	}
	readFile.open(path);
	while (getline(readFile, line, ','))
	{
		if (!readFile.eof())
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			line.erase(remove(line.begin(), line.end(), '*'), line.end());

			if (line == id)
			{
				getline(readFile, studentName, ',');
				getline(readFile, gender, ',');
				getline(readFile, matMarks, ',');
				getline(readFile, sciMarks, ',');
				getline(readFile, writeMarks, ',');
				getline(readFile, readMarks, ',');
				getline(readFile, otherMarks, ',');

				// Display Record Data for Editing
				cout << "\nStudent Name: " << studentName;
				const char* fullGender = gender.c_str();
				cout << "\nGender: " << displayGender(*fullGender);
				cout << "\n\nMarks";
				cout << "\n-----------------";
				matMarks.erase(remove(matMarks.begin(), matMarks.end(), ':'), matMarks.end());
				matMarks.erase(remove(matMarks.begin(), matMarks.end(), 'M'), matMarks.end());
				cout << "\nMaths: " << matMarks;
				sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), ':'), sciMarks.end());
				sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), 'S'), sciMarks.end());
				cout << "\nScience: " << sciMarks;
				writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), ':'), writeMarks.end());
				writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), 'W'), writeMarks.end());
				cout << "\nWriting: " << writeMarks;
				readMarks.erase(remove(readMarks.begin(), readMarks.end(), ':'), readMarks.end());
				readMarks.erase(remove(readMarks.begin(), readMarks.end(), 'R'), readMarks.end());
				cout << "\nReading: " << readMarks;
				otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), ':'), otherMarks.end());
				otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), 'O'), otherMarks.end());
				cout << "\nOther: " << otherMarks << "\n";
				break;
			}
		}
		else
		{
			cout << "\nSorry, this student does not exist.\n";
			readFile.close();
			system("pause");
			recordsScreen();
			return;
		}
	}
	readFile.close();

	// Get the user to input a detail they want to modify and then the value they want to replace it with
	cout << "\nEnter a detail to modify: ";
	getline(cin >> ws, detail);
	for (int i = 0; i < size(detail); i++) // Convert all the characters in the 'detail' string to lowercase
	{
		detail[i] = tolower(detail[i]);
	}

	cout << "Change To: ";
	getline(cin >> ws, newDetail);

	// Intialise variables for opening files, grabbing and replacing the data
	ifstream infile;
	infile.open(path);
	string strSearch;
	string strReplace;
	string strTemp;

	// Find the detail using "if else" statements
	if (detail == "name")
	{
		cout << "\nSorry, but the students name is currently unmodifable.\n";
		system("pause");
		infile.close();
		editRecord();
		return;
	}
	else if (detail == "gender")
	{
		detail = "Gender";
		strSearch = gender;
		strReplace = newDetail;
	}
	else if (detail == "maths")
	{
		detail = "Maths Mark";
		strSearch = "M:" + matMarks;
		strReplace = "M:" + newDetail;
	}
	else if (detail == "science")
	{
		detail = "Science Mark";
		strSearch = "S:" + sciMarks;
		strReplace = "S:" + newDetail;
	}
	else if (detail == "writing")
	{
		detail = "Writing Mark";
		strSearch = "W:" + writeMarks;
		strReplace = "W:" + newDetail;
	}
	else if (detail == "reading")
	{
		detail = "Read Mark";
		strSearch = "R:" + readMarks;
		strReplace = "R:" + newDetail;
	}
	else if (detail == "other")
	{
		detail = "Other Mark";
		strSearch = "O:" + otherMarks;
		strReplace = "O:" + newDetail;
	}
	else
	{
		cout << "\nWe could not find the detail you were looking for, please try again.\n";
		system("pause");
		infile.close();
		editRecord();
		return;
	}

	ofstream outfile("Classes/temp.txt");

	while (getline(infile, strTemp, ','))
	{
		line = strTemp;
		while (strTemp == "\n*" + id || strTemp == "*" + id)
		{
			line += ",";
			outfile << line;
			getline(infile, line, ',');
			if (line == strSearch)
			{
				strTemp = strReplace;
				break;
			}
		}
		if (strTemp != "\n*")
		{
			strTemp += ",";
		}
		outfile << strTemp;
		if (strTemp == "*" + id)
		{
			strTemp += "\n";
			break;
		}
	}
	cout << "\n\n" << detail << " has now been changed to " << newDetail << ".\n";

	infile.close();
	outfile.close();

	remove(path.c_str());
	if (rename("Classes/temp.txt", path.c_str()) != 0)
	{
		cout << "ERROR: Failed to Remove Record"; // TEMP: Helps us fix errors easier
	}

	system("pause");
	recordsScreen();
	return;
}

// Allow teachers to remove a student and all of their data from their class
void Teacher::removeStudent()
{
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	string line, id, name;
	string path;
	char confirmation;
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
	cout << "Enter a student ID to remove from your class (or type 'exit' to go back): ";
	getline(cin >> ws, id);
	if (id == "exit")
	{
		recordsScreen();
		return;
	}
	readFile.open(path);
	while (getline(readFile, line, ','))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		if (!readFile.eof())
		{
			if (line == id)
			{
				getline(readFile, name, ',');
				break;
			}
		}
		else
		{
			cout << "\nSorry, this student does not exist.\n";
			readFile.close();
			system("pause");
			recordsScreen();
			return;
		}
	}
	readFile.close();

	readFile.open(path);
	writeFile.open("Classes/temp.txt");
	getline(readFile, line, '*');

	while (getline(readFile, line, '*'))
	{
		if (line.substr(0, id.size()) != id)
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			writeFile << "*" << line << endl;
		}
	}
	cout << "\nAre you sure you want to remove " << name << " from your class? (y/n): ";
	cin >> confirmation;
	if (confirmation == 'n')
	{
		recordsScreen();
		return;
	}
	else
	{
		writeFile << "*";
		readFile.close();
		writeFile.close();
		remove(path.c_str());
		if (rename("Classes/temp.txt", path.c_str()) != 0)
		{
			cout << "ERROR: Failed to Remove Record"; // TEMP: Helps us fix errors easier
		}
		cout << "\n" << name << " has been removed from your class.\n";
	}
	system("pause");
	recordsScreen();
	return;
}

// Allow teachers to add new/update a students learning progress for each term
void Teacher::updateRecord()
{
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	string line, id, path, name, termChoice, learningProgress, termOne, termTwo, termThree, termFour, strTemp;
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

	path = "Classes/room_" + line + ".txt";

	cout << "*******************************\n";
	cout << "Student Records - Update Record\n";
	cout << "*******************************\n\n";
	cout << "Class Number: " << line << "\n"; //Temp output to track classroom number.

	cout << "Enter a Student ID to update their learning progression (or type 'exit' to go back): ";
	getline(cin >> ws, id);
	if (id == "exit")
	{
		recordsScreen();
		return;
	}
	readFile.open(path);

	while (getline(readFile, line, ','))
	{
		if (!readFile.eof())
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			line.erase(remove(line.begin(), line.end(), '*'), line.end());
			getline(readFile, name, ',');

			if (line == id)
			{
				cout << "\nLearning Observations for " << name << "\n";
				cout << "------------------------------------------\n";
				for (int i = 0; i < 6; i++)
				{
					getline(readFile, line, ',');
				}
				getline(readFile, termOne, ',');
				termOne.erase(remove(termOne.begin(), termOne.end(), ':'), termOne.end());
				termOne.erase(remove(termOne.begin(), termOne.end(), '1'), termOne.end());
				cout << "Term 1: " << termOne << "\n";
				getline(readFile, termTwo, ',');
				termTwo.erase(remove(termTwo.begin(), termTwo.end(), ':'), termTwo.end());
				termTwo.erase(remove(termTwo.begin(), termTwo.end(), '2'), termTwo.end());
				cout << "Term 2: " << termTwo << "\n";
				getline(readFile, termThree, ',');
				termThree.erase(remove(termThree.begin(), termThree.end(), ':'), termThree.end());
				termThree.erase(remove(termThree.begin(), termThree.end(), '3'), termThree.end());
				cout << "Term 3: " << termThree << "\n";
				getline(readFile, termFour, ',');
				termFour.erase(remove(termFour.begin(), termFour.end(), ':'), termFour.end());
				termFour.erase(remove(termFour.begin(), termFour.end(), '4'), termFour.end());
				cout << "Term 4: " << termFour << "\n";
				cout << "------------------------------------------\n";
				break;
			}
		}
		else
		{
			cout << "\nSorry, this student does not exist.\n";
			readFile.close();
			system("pause");
			recordsScreen();
			return;
		}
	}
	readFile.close();

	int choice;
	ifstream infile(path);
	string str_search;
	string str_replace;
	ofstream outfile("Classes/temp.txt");

	cout << "\n1. Record New/Update Observation"
		<< "\n2. Back";
	cout << "\n\nEnter corresponding number for selection: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "\nChoose a Term Number (1 - 4): ";
		cin >> termChoice;
		cout << "Learning Progress (Achieved, Progressing, Needs Help): ";
		getline(cin >> ws, learningProgress);
		if (termChoice == "1")
		{
			str_search = "1:" + termOne;
			str_replace = "1:" + learningProgress;
			termChoice = "Term 1";
		}
		else if (termChoice == "2")
		{
			str_search = "2:" + termTwo;
			str_replace = "2:" + learningProgress;
			termChoice = "Term 2";
		}
		else if (termChoice == "3")
		{
			str_search = "3:" + termThree;
			str_replace = "3:" + learningProgress;
			termChoice = "Term 3";
		}
		else if (termChoice == "4")
		{
			str_search = "4:" + termFour;
			str_replace = "4:" + learningProgress;
			termChoice = "Term 4";
		}

		while (getline(infile, strTemp, ','))
		{
			line = strTemp;
			while (strTemp == "\n*" + id || strTemp == "*" + id)
			{
				line += ",";
				outfile << line;
				getline(infile, line, ',');
				if (line == str_search)
				{
					strTemp = str_replace;
					break;
				}
			}
			if (strTemp != "\n*")
			{
				strTemp += ",";
			}
			outfile << strTemp;
			if (strTemp == "*" + id)
			{
				strTemp += "\n";
				break;
			}
		}
		cout << "\n\nSuccessfully updated " << name << "'s learning progression to " << learningProgress
			<< " for " << termChoice << ".\n";

		infile.close();
		outfile.close();

		remove(path.c_str());

		if (rename("Classes/temp.txt", path.c_str()) != 0)
		{
			cout << "ERROR: Failed to Remove Record"; // TEMP: Helps us fix errors easier
		}

		system("pause");
		recordsScreen();
		return;
	case 2:
		infile.close();
		outfile.close();
		recordsScreen();
		return;
	default:
		inputFail();
		system("pause");
		updateRecord();
	}
}

// Allow the teacher to view all the records of students in their class
void Teacher::viewRecords()
{
	system("CLS");
	int studentCount = 0;
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	string line, id, path, studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, learningProgress;
	int totalMarks = 0;

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

	path = "Classes/room_" + line + ".txt";
	readFile.open(path);
	const char* fullGender = gender.c_str();

	cout << "******************************\n";
	cout << "Student Records - View Records\n";
	cout << "******************************\n";

	while (getline(readFile, line))
	{
		if (line == "*")
		{
			break;
		}
		studentCount++;
	}
	readFile.close();
	readFile.open(path);

	if (studentCount == 0)
	{
		cout << "\nThere are no records to show, please first add some students to your class.\n";
		system("pause");
		readFile.close();
		recordsScreen();
		return;
	}

	checkLineInTeacherFile(line, 7);
	cout << "\nThere are a total of " << studentCount << " students in your class (Room " << line << ")\n";
	cout << "\nID    Full Name                Gender    Maths    Science    Writing    Reading    Other    Learning Progress";
	cout << "\n-------------------------------------------------------------------------------------------------------------";

	while (readFile.is_open())
	{
		while (getline(readFile, line, ','))
		{
			line.erase(remove(line.begin(), line.end(), '*'), line.end());
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());

			getline(readFile, studentName, ',');
			getline(readFile, gender, ',');
			getline(readFile, matMarks, ',');
			getline(readFile, sciMarks, ',');
			getline(readFile, writeMarks, ',');
			getline(readFile, readMarks, ',');
			getline(readFile, otherMarks, ',');

			matMarks.erase(remove(matMarks.begin(), matMarks.end(), 'M'), matMarks.end());
			matMarks.erase(remove(matMarks.begin(), matMarks.end(), ':'), matMarks.end());
			sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), 'S'), sciMarks.end());
			sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), ':'), sciMarks.end());
			writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), 'W'), writeMarks.end());
			writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), ':'), writeMarks.end());
			readMarks.erase(remove(readMarks.begin(), readMarks.end(), 'R'), readMarks.end());
			readMarks.erase(remove(readMarks.begin(), readMarks.end(), ':'), readMarks.end());
			otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), 'O'), otherMarks.end());
			otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), ':'), otherMarks.end());

			break;
		}
		if (line != "")
		{
			totalMarks = stoi(matMarks) + stoi(sciMarks) + stoi(readMarks) + stoi(writeMarks) + stoi(otherMarks);
			cout << "\n" << left << setw(6) << line << setw(25) << studentName << setw(10)
				<< displayGender(*fullGender) << setw(9) << matMarks << setw(11) << sciMarks << setw(11)
				<< writeMarks << setw(11) << readMarks << setw(9) << otherMarks << displayOverallProgress(totalMarks);
			cout << "\n-------------------------------------------------------------------------------------------------------------";
			for (int i = 0; i < 4; i++)
			{
				getline(readFile, line, ',');
			}
		}
		if (readFile.eof())
		{
			readFile.close();
		}
	}
	cout << "\n\n";
	system("pause");
	recordsScreen();
}

// Function to manage teacher registration
void Teacher::teacherSignUp()
{
	system("CLS");
	ofstream writeFile("Sign_Up_And_Login_Details/teacher_registration.txt", ios_base::app);
	
	// Prompt the user to enter all the inital data for teacher registration
	cout << "********************\n";
	cout << "Teacher Registration\n";
	cout << "********************\n";
	cout << "\nFull name (or type 'exit' to go back to the home screen): ";
	getline(cin >> ws, fullName);
	if (fullName == "exit") // Create an exit function if users don't want to continue signing up
	{
		return;
	}
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	gender = tolower(gender);
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
			ofstream writeClassroom("Classes/room_" + to_string(classroomNum) + ".txt");
			writeClassroom << "*";
			writeClassroom.close();

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