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
/// Gets a line in the teacher_registration.txt file
/// </summary>
/// <param name="line"> - A string to hold the current line in the file</param>
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
		if (!login.userLogout()) // If the user did not confirm to logout, return back to the teacher home screen
		{
			displayTeacherScreen();
		}
		break;
	default:
		// Manage invalid input and return back to the teacher home screen
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
	tempStudentData.saveData(line); // Access the student source file to grab the required data
	return;
}

/// <summary>
/// Run through each character in a string and check to see if any characters are digits
/// </summary>
/// <param name="numCheck">- The string the program should check digits in</param>
/// <returns>A bool that returns true or false depending on if there were any digits in the string</returns>
bool checkString(string numCheck)
{
	for (int i = 0; i < numCheck.length(); i++)
	{
		if (isdigit(numCheck[i]) == false)
		{
			return false;
		}
	}
	return true;
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
		if (line == login.savedUser) // Get the designated class number from the teacher file
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
	if (id == "exit") // Return to the records screen if the user types 'exit'
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

			// If a match for student id is found in the file, get all the student data following it
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

				// Remove characters in each mark variable so they just display as the number
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
			// If the program reaches the end of the file without finding an id, notify the user the student
			// does not exist and return to the teacher records screen.
			cout << "\nSorry, this student does not exist.\n";
			readFile.close();
			system("pause");
			recordsScreen();
			return;
		}
	}
	readFile.close(); // Close the file when the program is done with it

	// Get the user to input a detail they want to modify and then the value they want to replace it with
	cout << "\nEnter a detail to modify: ";
	getline(cin >> ws, detail);
	for (int i = 0; i < size(detail); i++) // Convert all the characters in the 'detail' string to lowercase
	{
		detail[i] = tolower(detail[i]);
	}
	cout << "Change To: ";

	while (true) // Keep running this loop until certain conditions are met
	{
		getline(cin >> ws, newDetail); // Take in input for the edited value
	
		// Check if the detail the user wants to change is a mark and ensure the new value entered is in between
		// 0 and 100.
		if (detail == "maths" || detail == "science" || detail == "reading" || detail == "writing" || detail == "other")
		{
			if (checkString(newDetail))
			{
				if (stoi(newDetail) >= 0 && stoi(newDetail) <= 100)
				{
				break;
				}
				else // Check if the user entered a value that was not between 0 and 100 and notify the user
				{
					cout << "Please enter a number between 0 and 100: ";
				}
			}
			else // Check if the user entered a string instead of a number and notify the user
			{
				cout << "Please input numbers only: ";
			}
		}
		else // If the user didn't want to edit a students marks, break out of the loop
		{
			break;
		}
	}

	// Create a file and open it in the designated class so the program can look for its data
	ifstream infile; 
	infile.open(path);
	string strSearch; // A string which is used to find the data to edit
	string strReplace; // A string which holds the edited data
	string strTemp; // A string to store data in temporarily before it is written back into a file

	// Find the detail using "if else" statements
	if (detail == "name") // If the user change the students name, notify them it cannot be done
	{
		cout << "\nSorry, but the students name is currently unmodifable.\n";
		system("pause");
		infile.close();
		editRecord();
		return; // Add return keywords here to stop the program from coming back here if the user logs out
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
	else // Run this else statment if the user could not find a match for the detail the user wanted to edit
	{
		cout << "\nWe could not find the detail you were looking for, please try again.\n";
		system("pause");
		infile.close();
		editRecord(); 
		return;
	}

	ofstream outfile("Classes/temp.txt"); // Open a temporary file to write the edited data into

	while (getline(infile, strTemp, ','))
	{
		line = strTemp; // LIAM: Don't understand why we do this
		while (strTemp == "\n*" + id || strTemp == "*" + id)
		{
			// Add a comma to the line so it writes into the data into the file the same it was before
			line += ",";
			outfile << line;
			getline(infile, line, ',');
			// If a match is found in the file, replace the value with the new value and break out of the loop
			if (line == strSearch) 
			{
				strTemp = strReplace;
				break;
			}
		}
		if (strTemp != "\n*") // Keep adding the rest of the data to strTemp until it reaches "\n*" (signalling the end of the file) 
		{
			strTemp += ",";
		}
		outfile << strTemp; // Write the data from strTemp into the file so it stays the same as before
		if (strTemp == "*" + id) // LIAM: Don't understand what this does
		{
			strTemp += "\n";
			break;
		}
	}
	cout << "\n\n" << detail << " has now been changed to " << newDetail << ".\n";

	// Close the files after we're done using them
	infile.close();
	outfile.close();

	// Remove the previous class file and rename the new "temp.txt" file to the class file
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
	// Look through the teacher file to find the teacher who logged in and get their class number
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
	path = "Classes/room_" + line + ".txt"; // Set the path variable to the designated classroom file
	cout << "*******************************\n";
	cout << "Student Records - Delete Record\n";
	cout << "*******************************\n\n";
	cout << "Class Number: " << line << "\n"; //Temp output to track classroom number.
	cout << "Enter a student ID to remove from your class (or type 'exit' to go back): ";
	getline(cin >> ws, id);
	if (id == "exit") // Allow the user to go back to the records screen
	{
		recordsScreen();
		return;
	}
	readFile.open(path); // Open the file in the set path
	while (getline(readFile, line, ','))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		if (!readFile.eof())
		{
			if (line == id) // If an id match is found, get the name of the student
			{
				getline(readFile, name, ',');
				break;
			}
		}
		else // If there is no id match, notify the user the student does not exist
		{
			cout << "\nSorry, this student does not exist.\n";
			readFile.close();
			system("pause");
			recordsScreen();
			return;
		}
	}
	// Close the file and open it again to force the program to go back to the beginning of the file
	readFile.close(); 
	readFile.open(path);
	// Get the first asterisk in the file so that it isn't written into the first line
	getline(readFile, line, '*'); 
	while (getline(readFile, line, '*'))
	{
		// Keep writing lines back into the temp until the id is equal to the one the user wants to delete
		if (line.substr(0, id.size()) != id)
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			writeFile << "*" << line << endl;
		}
	}
	// Confirm the users choice and if the user says so, return back to the teacher records screen
	cout << "\nAre you sure you want to remove " << name << " from your class? (y/n): "; 
	cin >> confirmation;
	if (confirmation == 'y')
	{
		writeFile.open("Classes/temp.txt");// Open a temporary to file to write data to with updated values
		writeFile << "*";
		readFile.close();
		writeFile.close();
		remove(path.c_str());
		if (rename("Classes/temp.txt", path.c_str()) != 0) // LIAM: Not really sure how this works
		{
			cout << "ERROR: Failed to Remove Record\n"; // TEMP: Helps us fix errors easier if the record couldn't be deleted
		}
		cout << "\n" << name << " has been removed from your class.\n"; // Notification message
		system("pause");
		recordsScreen();
		return;
	}
	// If the user says yes, don't write the deleted student into the file and rename the temp file back to the class file
	else 
	{
		recordsScreen();
		return;
	}

}

// Allow teachers to add new/update a students learning progress for each term
void Teacher::updateRecord()
{
	system("CLS");
	ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
	ofstream writeFile;
	string line, id, path, name, termChoice, learningProgress, termOne, termTwo, termThree, termFour, strTemp;
	// Look through the teacher file to find the teacher who logged in and get their class number
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

	path = "Classes/room_" + line + ".txt"; // Set the path to the designated classroom file

	cout << "*******************************\n";
	cout << "Student Records - Update Record\n";
	cout << "*******************************\n\n";
	cout << "Class Number: " << line << "\n"; //Temp output to track classroom number.

	cout << "Enter a Student ID to update their learning progression (or type 'exit' to go back): ";
	getline(cin >> ws, id);
	if (id == "exit") // Allow the user to go back if they change their mind
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

			if (line == id) // If an id match is found, list the students current learning observations for each term
			{
				cout << "\nLearning Observations for " << name << "\n";
				cout << "------------------------------------------\n";
				for (int i = 0; i < 6; i++)
				{
					getline(readFile, line, ','); // Keep getting the line until the first terms learning progress is found
				}
				// Get the line for each term and display it in the console, removing unecessary data in the file
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
		else // If an id match is not found, notify the user the student doesn't exist
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
	ofstream outfile;
	// Prompt the user to either update the progress or return back to the records screen
	cout << "\n1. Record New/Update Observation"
		<< "\n2. Back";
	cout << "\n\nEnter corresponding number for selection: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		// Take in input for the users term choice, switch on the term, and replace the learning observation 
		// for that term.
		outfile.open("Classes/temp.txt");
		cout << "\nChoose a Term Number (1 - 4): ";
		cin >> termChoice;
		cout << "Learning Progress (Achieved, Progressing, Needs Help): ";
		getline(cin >> ws, learningProgress);

		switch (stoi(termChoice))
		{
		case 1:
			str_search = "1:" + termOne;
			str_replace = "1:" + learningProgress;
			termChoice = "Term 1";
			break;
		case 2:
			str_search = "2:" + termTwo;
			str_replace = "2:" + learningProgress;
			termChoice = "Term 2";
			break;
		case 3:
			str_search = "3:" + termThree;
			str_replace = "3:" + learningProgress;
			termChoice = "Term 3";
			break;
		case 4:
			str_search = "4:" + termFour;
			str_replace = "4:" + learningProgress;
			termChoice = "Term 4";
			break;
		default: // If there are no matches, notify the user the term doesn't exist and ask them to enter an id again
			cout << "\nThat term doesn't exist, please try again.\n";
			system("pause");
			infile.close();
			outfile.close();
			updateRecord();
			return;
		}

		// LIAM: Don't really understand what the below does
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

		// Close the files once we're done using them
		infile.close();
		outfile.close();

		// Remove the previous class file and rename the "temp.txt" file back to the class file
		remove(path.c_str());

		if (rename("Classes/temp.txt", path.c_str()) != 0)
		{
			cout << "ERROR: Failed to Remove Record"; // TEMP: Helps us fix errors easier
		}

		system("pause");
		recordsScreen();
		return;
	case 2: // If the user entered 2 for back, go back to the records screen
		infile.close();
		outfile.close();
		recordsScreen();
		return;
	default: // If there was no choice match, manage conversion errors with inputFail() and display error message accordingly
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
	string line, id, path;

	// Look through the teacher file to find the teacher who logged in and get their class number
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

	path = "Classes/room_" + line + ".txt"; // Set the path to the designated classroom file
	readFile.open(path);

	cout << "******************************\n";
	cout << "Student Records - View Records\n";
	cout << "******************************\n";

	// Increase the student count as long as the program doesn't find a single "*" taking up a line
	// ("*" is one of our delimiters).
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

	// If the program couldn't find any students, notify the user there are no records to show and return to the 
	// records screen.
	if (studentCount == 0) 
	{
		cout << "\nThere are no records to show, please first add some students to your class.\n";
		system("pause");
		readFile.close();
		recordsScreen();
		return;
	}

	// Run the checkLineInTeacherFile() function to get the classroom number and display it below
	checkLineInTeacherFile(line, 7);
	cout << "\nThere are a total of " << studentCount << " students in your class (Room " << line << ")\n";

	// Run the getRecordData() to get all the student data and display it in a table
	getRecordData(readFile, line);
	
	cout << "\n\n";
	system("pause");
	recordsScreen();
}

/// <summary>
/// Get the record data for each student in the teachers class and display it
/// </summary>
/// <param name="readFile"> - Takes in the file that the program will read data from</param>
/// <param name="line"> - Takes in a string to read the data into</param>
void Teacher::getRecordData(std::ifstream& readFile, std::string& line)
{
	string studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, learningProgress;
	int totalMarks = 0;
	const char* fullGender = gender.c_str();

	// Print out the different categories to the console
	cout << "\nID    Full Name                Gender    Maths    Science    Writing    Reading    Other    Learning Progress";
	cout << "\n-------------------------------------------------------------------------------------------------------------";

	while (readFile.is_open())
	{
		getline(readFile, line, ','); // Skip the idea so the next line starts from the student name
		
		// Remove unecessary characters the program shouldn't read out
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());

		// Get each line, seperated by commas, following the student ID and hold the data in designated variables
		getline(readFile, studentName, ',');
		getline(readFile, gender, ',');
		getline(readFile, matMarks, ',');
		getline(readFile, sciMarks, ',');
		getline(readFile, writeMarks, ',');
		getline(readFile, readMarks, ',');
		getline(readFile, otherMarks, ',');

		// Remove unecessary characters that the program doesn't need to print out but are necessary in the file
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
		
		// If the line in the file is not equal to an empty line, print out all the student data to fit their categories
		if (line != "")
		{
			// Add the marks up into a totalMarks variable to print out the overall learning progress
			totalMarks = stoi(matMarks) + stoi(sciMarks) + stoi(readMarks) + stoi(writeMarks) + stoi(otherMarks);
			cout << "\n" << left << setw(6) << line << setw(25) << studentName << setw(10)
				<< displayGender(*fullGender) << setw(9) << matMarks << setw(11) << sciMarks << setw(11)
				<< writeMarks << setw(11) << readMarks << setw(9) << otherMarks << displayOverallProgress(totalMarks);
			cout << "\n-------------------------------------------------------------------------------------------------------------";
			for (int i = 0; i < 4; i++)
			{
				getline(readFile, line, ','); // Keep getting lines until the next idea to skip term observations
			}
		}
		if (readFile.eof()) // If the file is at the end of it's contents, close it so no more data will be displayed
		{
			readFile.close();
		}
	}
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

// Default constructor (currently not needed to be used)
Teacher::Teacher()
{

}