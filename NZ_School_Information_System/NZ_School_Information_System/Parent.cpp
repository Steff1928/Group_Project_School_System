#include <iostream>
#include <fstream>
#include <string> // Include the string library to gain access to various string properties
#include <vector> // Include vector library to gain acccess to vectors and additional properties
#include "Parent.h"
#include "Main.h"

using namespace std;

/// <summary>
/// Get the data in the parent_registration.txt file, read it and display it to the console when necessary
/// </summary>
/// <param name="line"> - Holds the data for the current line in the file</param>
/// <param name="lineNum"> - Tells the program which line to read out</param>
void Parent::checkLineInFile(std::string& line, const int lineNum)
{
	ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Open the parent file
	// Loops through the designated file storing each value in "line"
	// (Use "*" as a delimeter so it is not read by the program
	while (getline(readFile, line, '*')) 
	{
		// Remove any \n characters so they are not read
		line.erase(remove(line.begin(), line.end(), '\n'), line.end()); 
		// Use this if statement to only read out the line of the current user logged in
		if (line == login.savedUser)
		{
			for (int i = 0; i < lineNum; i++) // Number used here to loop to a certain line we require in a file
			{
				getline(readFile, line, ',');
			}
			readFile.close(); // Close the file once we're done with it to save memory
			break; // Once we have our data, exit the loop so we do not read any more lines
		}
	}
}

// Display restricted options for users logged in as a parent
void Parent::displayParentScreen()
{
	ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Open the parent file
	
	// Define a string to run the function to get the value of the teachers "fullName" in the file to display it in the
	// parent home screen.
	string line;
	checkLineInFile(line, 2); 

	int choice;
	system("CLS");
	cout << "***********************************           Welcome: " << line << "\n"; 
	cout << "Yoobee Portal - Logged in as Parent           --------------------------\n";
	cout << "***********************************\n\n";
	cout << "1. View Child Record\n" 
		 << "2. View School notices\n" 
		 << "3. Logout\n";
	cout << "\nEnter corresponding number for the selection: ";
	cin >> choice;
	switch (choice) // Depending on the key pressed, run the designated function by switching on "choice"
	{
	case 1:
		viewChildReport();
		displayParentScreen();
		break;
	case 2:
		viewNotices();
		displayParentScreen();
		break;
	case 3:
		if (!login.userLogout()) // Get the value of userLogout and if false, don't logout and re-display the parent screen
		{
			displayParentScreen();
		}
		break;
	default: // Manage invalid inputs if a case match is not found with "default"
		inputFail();
		system("pause");
		displayParentScreen();
	}
}
/// <summary>
/// Read lines in the parent file to get the child name(s) for the logged in parent user and add it to a vector of childData
/// </summary>
/// <param name="readParentFile"></param>
/// <param name="lineInFile"></param>
/// <param name="classNum"></param>
/// <param name="childName"></param>
/// <param name="childData"></param>
/// <param name="child"></param>
void Parent::readLineInParent(std::ifstream& readParentFile, std::string& lineInFile, std::string& classNum, std::string& childName, std::vector<Parent::Child>& childData, Parent::Child child)
{
	while (getline(readParentFile, lineInFile, '*')) // Loop through parent file to find a match for the logged in user
	{
		lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '\n'), lineInFile.end());
		// If match is found, get the next line and ensure the line is not equal to an asterisk
		if (lineInFile == login.savedUser)
		{
			getline(readParentFile, lineInFile);
			while (lineInFile != "*") // If not equal to an asterisk, get the next line and assign to childName
			{
				getline(readParentFile, lineInFile, ',');
				lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '\n'), lineInFile.end());
				getline(readParentFile, classNum, ','); // Get the line after childName and assign it to classNum
				childName = lineInFile;
				// Break out of the loop if standalone asterisks or empty lines are found in childName
				if (childName == "*" || childName == "") 
				{
					break;
				}
				// Push both childName and childClass into a vector of type Child in Parent
				child.childName = childName;
				child.childClass = stoi(classNum);

				childData.push_back(child);
				getline(readParentFile, lineInFile);		
			}
			break; // Break out of the loop when finished
		}
	}
}

/// <summary>
/// Opens and reads the data from the logged in parent's child's classroom file and displays it to the console
/// </summary>
/// <param name="classNum"></param>
/// <param name="lineInFile"></param>
/// <param name="childName"></param>
/// <param name="gender"></param>
/// <param name="mathMarks"></param>
/// <param name="scienceMarks"></param>
/// <param name="readingMarks"></param>
/// <param name="writingMarks"></param>
/// <param name="otherMarks"></param>
void Parent::readChildInfo(std::string& classNum, std::string& lineInFile, std::string& childName, std::string& gender, std::string& mathMarks, std::string& scienceMarks, std::string& readingMarks, std::string& writingMarks, std::string& otherMarks)
{
	ifstream readClassFile("Classes/room_" + classNum + ".txt"); // Open a file of the child's classroom number
	const char* fullGender = gender.c_str(); // Store gender as a fullword of a pointer of const char in fullGender

	while (getline(readClassFile, lineInFile, ',')) // Loop through class file to find a match for childName
	{
		lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '\n'), lineInFile.end());
		lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '*'), lineInFile.end());
		// If a match is found, get the following lines and store them in designated variables
		if (lineInFile == childName) 
		{
			lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '\n'), lineInFile.end());
			getline(readClassFile, gender, ',');
			getline(readClassFile, mathMarks, ',');
			getline(readClassFile, scienceMarks, ',');
			getline(readClassFile, writingMarks, ',');
			getline(readClassFile, readingMarks, ',');
			getline(readClassFile, otherMarks, ',');

			// Remove unecessary characters from the mark variables
			mathMarks.erase(remove(mathMarks.begin(), mathMarks.end(), ':'), mathMarks.end());
			mathMarks.erase(remove(mathMarks.begin(), mathMarks.end(), 'M'), mathMarks.end());
			scienceMarks.erase(remove(scienceMarks.begin(), scienceMarks.end(), ':'), scienceMarks.end());
			scienceMarks.erase(remove(scienceMarks.begin(), scienceMarks.end(), 'S'), scienceMarks.end());
			readingMarks.erase(remove(readingMarks.begin(), readingMarks.end(), ':'), readingMarks.end());
			readingMarks.erase(remove(readingMarks.begin(), readingMarks.end(), 'R'), readingMarks.end());
			writingMarks.erase(remove(writingMarks.begin(), writingMarks.end(), ':'), writingMarks.end());
			writingMarks.erase(remove(writingMarks.begin(), writingMarks.end(), 'W'), writingMarks.end());
			otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), ':'), otherMarks.end());
			otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), 'O'), otherMarks.end());

			cout << "Gender: " << displayGender(*fullGender) << "\n\n"; // Displaying gender as a full word with displayGender()
			cout << "Marks\n"; // Display the child's marks
			cout << "------------------\n";
			cout << "Maths: " << "  " << mathMarks << "\n";
			cout << "Science: " << scienceMarks << "\n";
			cout << "Reading: " << readingMarks << "\n";
			cout << "Writing: " << writingMarks << "\n";
			cout << "Other: " << "  " << otherMarks << "\n";
			break; // Break out of the loop when done
		}
		if (lineInFile == "") // If the line came up empty in the class file, notify the user accordingly
		{
			cout << "A report for " << childName << " has not been released from their teacher yet.\n";
		}
	}
	if (!readClassFile.is_open()) // If the class file could not be opened, notify the user accordingly
	{
		cout << "The class " << childName << " is attending has not yet been registered into the system.\n";
	}
	readClassFile.close(); // Close the class file when finished
	
}

// Allow the parent user to view the data for each of there children
void Parent::viewChildReport()
{
	Child child;
	system("CLS");
	ifstream readParentFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Open the parent file
	// Variables to store the child's data and line in file
	string classNum, line, childName, gender, mathMarks, scienceMarks, readingMarks, writingMarks, otherMarks;
	vector<Child> childData; // Vector of type child to hold childData accordingly

	cout << "************\n";
	cout << "Child Record\n";
	cout << "************\n";

	// Run the readParent() function to get the childs name
	readLineInParent(readParentFile, line, classNum, childName, childData, child);

	// Loop through the size of the vector to keep outputting the parent's children and store data
	for (unsigned int i = 0; i < size(childData); i++) 
	{
		cout << "\nChild Name: " << childData[i].childName << "\n";
		classNum = to_string(childData[i].childClass); // Assign childClass from the vector to classNum locally
		childName = childData[i].childName; // Assign childName from the vector to childName locally
		// Run the readChildInfo() function to get the child's details from their class
		readChildInfo(classNum, line, childName, gender, mathMarks, scienceMarks, readingMarks, writingMarks, otherMarks);
	}
	readParentFile.close(); // Close the file when finished
	cout << "\n";
	system("pause");
}


// Allow the parent to view the current day's school notices
void Parent::viewNotices()
{
	system("CLS");
	cout << "**************\n";
	cout << "School Notices\n";
	cout << "**************\n\n";
	cout << "Current Notices:\n\n";
	cout << "Guest Speaker today in Life Drawing Room at 12 PM.\n";
	cout << "Beautiful selection of Fruits up for grabs on the Help Yourself Shelf Today!\n";
	cout << "2023 Design Contest Entries are now open!\n\n";
	system("pause");
}

// Function to manage parent registration
void Parent::parentSignUp()
{
	Child child;
	vector<Child> childData; // Take in a vector of type Child to store multiple children in one parent registration

	system("CLS");
	ofstream writeFile("Sign_Up_And_Login_Details/parent_registration.txt", ios_base::app); // Open the parent file in append mode

	// Initial personal details
	cout << "*******************\n";
	cout << "Parent Registration\n";
	cout << "*******************\n";
	cout << "\nFull name (or type 'exit' to go back to the home screen): ";
	getline(cin >> ws, fullName); // Use getline to allow the user to enter a string with spaces (doesn't seperate strings)
	if (fullName == "exit") // Create an exit function if users don't want to continue signing up
	{
		return; // Returns an empty value from this function
	}
	cout << "Gender (m = male, f = female, o = other): ";
	cin >> gender;
	gender = tolower(gender); // Convert uppercase to lowercase in gender if necessary

	cout << "DOB (dd/mm/yyyy): ";
	cin >> dob;
	cout << "Email: ";
	cin >> email;
	cout << "Contact Number: ";
	getline(cin >> ws , contactNum);
	cout << "\n\n";

	system("pause");
	system("CLS");

	// Child registration and info
	cout << "********************************\n";
	cout << "Parent Registration - Child Info\n";
	cout << "********************************\n";
	cout << "\nNumber of children attending Yoobee: ";
	cin >> childAmount; // Prompt the user to input the number of children they have

	// Loop up to the number of children they have and prompt the user to enter information for each child
	for (int i = 0; i < childAmount; i++)
	{
		cout << "\nChild " << i + 1 << "\n";
		cout << "Child's full name: ";
		getline(cin >> ws, child.childName); 
		cout << "Child's classroom number: ";
		cin >> child.childClass;
		cout << "Emergency Contact Caregiver's Full Name: ";
		getline(cin >> ws, child.emergencyContactName);
		cout << "Emergency Contact Number: ";
		getline(cin >> ws, child.emergencyContactNum);
		cout << "\n";
		childData.push_back(child); // Push all the child data into a vector so each child can be added to the file
	}
	system("pause");

	// Account details
	while (true) // Loop through this screen until the password and confirm password matches
	{
		system("CLS");
		cout << "***********************************\n";
		cout << "Parent Registration - Account Info\n";
		cout << "***********************************\n";
		cout << "\nUsername: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;

		string confirmPassword;
		cout << "Confirm Password: ";
		cin >> confirmPassword;
		if (password == confirmPassword) // Only register the user if there password and confirm password matches
		{
			cout << "Successfully signed up as a parent!\n\n"; // Notify the user they've successfully signed up
			
			writeFile << "*," << "\n"; // Write an asterisk and "\n" character intially to seperate parent data from each other
			// Write the rest of the data into the file, using "*" and "," as delimiters
			writeFile << userName << "*" << password << "," << fullName << "," << gender << "," << dob << "," << email << "," << contactNum << ",";
			
			// Loop through the size of childData and add everything from the vector into the file, seperating lines with commas
			for (unsigned int i = 0; i < size(childData); i++) 
			{
				// contactNum at the end of each child is so it's easier for us to find and use this value later
				writeFile << "\n" << childData[i].childName << "," << childData[i].childClass << "," << childData[i].emergencyContactName <<
					"," << childData[i].emergencyContactNum << "," << contactNum << ",";
			}
			writeFile << "\n"; // End with a "new line" character so the next parent registered can be added onto a new line
			login.savedUser = "," + userName; // Save the username so it is remembered by the program while the user is logged in
			writeFile.close(); // Close the file when finished in the loop
			system("pause");
			displayParentScreen(); // Go to the parent screen once signed in
			break; // Break out of the loop when the user signs out
		}
		else // Run this statment if confirm password and password do not match
		{
			cout << "Confirm Password is not the same as Password, please re-enter account info\n\n";
			system("pause");
		}
	}
	writeFile.close(); // Close the file here if it has not been closed already
}

// Initialise the values for the Parent class
Parent::Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	userName = _userName;
}

// Default constructor for Parent
Parent::Parent()
{
	gender = 0;
	childAmount = 0;
}

// Initialise the values for the Child struct
Parent::Child::Child(std::string _childName, int _childClass, std::string _emergencyContactName, 
	std::string _emergencyContactNum)
{
	childName = _childName;
	childClass = _childClass;
	emergencyContactName = _emergencyContactName;
	emergencyContactNum = _emergencyContactNum;
}

// Default constructor for Child in Parent
Parent::Child::Child()
{
	childClass = 0;
}