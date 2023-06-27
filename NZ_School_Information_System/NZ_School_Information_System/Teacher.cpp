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

	cout << "Student details have been added to your class (Room " << line << ")\n";
	system("pause");
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

	cout << "Class Number: " << line << "\n"; //Temp output to track classroom number.

	cout << "\nEnter a Student ID to edit in your class: ";
	getline(cin >> ws, id);
	readFile.open(path);
	while (getline(readFile, line, ','))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(remove(line.begin(), line.end(), '*'), line.end());

		if (line == id)
		{
			getline(readFile, studentName, ',');
			getline(readFile, gender, ',');
			getline(readFile, matMarks, ',');
			getline(readFile, sciMarks, ',');
			getline(readFile, readMarks, ',');
			getline(readFile, writeMarks, ',');
			getline(readFile, otherMarks, ',');

			// Display Record Data for Editing
			cout << "\nStudent ID: " << id;
			cout << "\nStudent Name: " << studentName;
			const char* fullGender = gender.c_str();
			cout << "\nGender: " << displayGender(*fullGender);
			cout << "\n\nMarks";
			cout << "\n-----------------";
			cout << "\nMaths: " << matMarks;
			cout << "\nScience: " << sciMarks;
			cout << "\nWriting: " << writeMarks;
			cout << "\nReading: " << readMarks;
			cout << "\nOther: " << otherMarks << "\n";
			break;
		}
	}
	readFile.close();

	cout << "\nEnter a detail to modify: ";
	getline(cin >> ws, detail);
	cout << "Change To: ";
	getline(cin >> ws, newDetail);

	readFile.open(path);
	writeFile.open(path, ios_base::app);
	ifstream infile(path);
	string str_search;
	string str_replace;

	if (detail == "id")
	{
		detail = "Student ID";
		str_search = id;
		str_replace = newDetail;
	}
	else if (detail == "name")
	{
		detail = "Student Full Name";
		str_search = studentName;
		str_replace = newDetail;
	}
	else if (detail == "gender")
	{
		detail = "Gender";
		str_search = gender;
		str_replace = newDetail;
	}
	else if (detail == "maths")
	{
		detail = "Maths Mark";
		str_search = matMarks;
		str_replace = newDetail;
	}
	else if (detail == "science")
	{
		detail = "Science Mark";
		str_search = sciMarks;
		str_replace = newDetail;
	}
	else if (detail == "writing")
	{
		detail = "Writing Mark";
		str_search = writeMarks;
		str_replace = newDetail;
	}
	else if (detail == "reading")
	{
		detail = "Read Mark";
		str_search = readMarks;
		str_replace = newDetail;
	}
	else if (detail == "other")
	{
		detail = "Other Mark";
		str_search = otherMarks;
		str_replace = newDetail;
	}
	ostringstream text;
	text << infile.rdbuf();
	string str = text.str();
	size_t pos = str.find(str_search);
	if (pos != string::npos)
	{
		str.replace(pos, string(str_search).length(), str_replace);
	}
	infile.close();

	ofstream outfile(path);
	outfile << str;
	
	cout << "\n\n" << detail << " has now been changed to " << newDetail << ".\n";
	system("pause");

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
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	string line, id, path, termChoice, learningProgress, termOne, termTwo, termThree, termFour;
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

	cout << "\nEnter a Student ID to update their learning progression: ";
	getline(cin >> ws, id);
	readFile.open(path);
	while (getline(readFile, line, ','))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		if (line == id)
		{
			for (int i = 0; i < 7; i++)
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
		}
		else
		{
			cout << "Sorry, this student does not exist.\n";
			break;
		}
		readFile.close();
	}
	cout << "Choose a Term Number: ";
	cin >> termChoice;
	cout << "Learning Progress (Achieved, Progressing, Needs Help): ";
	getline(cin >> ws, learningProgress);
	ifstream infile(path);
	string str_search;
	string str_replace;
	if (termChoice == "1")
	{
		str_search = "1:"+termOne;
		str_replace = learningProgress;
		termChoice = "Term 1";
	}
	else if (termChoice == "2")
	{
		str_search = "2:" + termTwo;
		str_replace = learningProgress;
		termChoice = "Term 2";
	}
	else if (termChoice == "3")
	{
		str_search = "3:" + termThree;
		str_replace = learningProgress;
		termChoice = "Term 3";
	}
	else if (termChoice == "4")
	{
		str_search = "4:" + termFour;
		str_replace = learningProgress;
		termChoice = "Term 4";
	}
	ostringstream text;
	text << infile.rdbuf();
	string str = text.str();
	size_t pos = str.find(str_search);
	str.replace(pos, string(str_search).length(), str_replace);
	infile.close();

	ofstream outfile(path);
	outfile << str;

	system("pause");
}

// Allow the teacher to view all the records of students in their class
void Teacher::viewRecords()
{
	system("CLS");
	int studentCount = 0;
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	string line, id, path, studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, learningProgress;

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
		studentCount++;
	}
	readFile.close();

	cout << "\nThere are a total of " << studentCount - 1 << " students in your class\n";
	cout << "\nID    Full Name                Gender    Maths    Science    Writing    Reading    Other    Learning Progress";
	cout << "\n-------------------------------------------------------------------------------------------------------------";
	
	readFile.open(path);
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
			getline(readFile, readMarks, ',');
			getline(readFile, writeMarks, ',');
			getline(readFile, otherMarks, ',');
			getline(readFile, learningProgress, ',');

			break;
		}
		if (line != "")
		{
			cout << "\n" << left << setw(6) << line << setw(25) << studentName << setw(10) 
				<< displayGender(*fullGender) << setw(9) << matMarks << setw(11) << sciMarks << setw(11) 
				<< readMarks << setw(11) << writeMarks << setw(9) << otherMarks << learningProgress;
			cout << "\n-------------------------------------------------------------------------------------------------------------";
		}
		if (readFile.eof())
		{
			readFile.close();
		}
	}
	cout << "\n\n";
	system("pause");
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