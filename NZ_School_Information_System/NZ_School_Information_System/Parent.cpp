#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Parent.h"
#include "Main.h"
using namespace std;

/// <summary>
/// Get the data in the parent_registration.txt file, read it and display it to the console when necessary
/// </summary>
/// <param name="line"> - Holds the data for the current line in the file</param>
/// <param name="lineNum"> - Tells the program which line to read out</param>
void Parent::checkLineInFile(std::string& line, int lineNum)
{
	ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Opens a file in read mode 
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
	ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt");
	string line;

	checkLineInFile(line, 2); // Run the function to get the value of "fullName" in the file to display it later

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
	switch (choice) 
	{
	case 1:
		viewChildReport(); // TODO: Add data from file to the child report
		displayParentScreen();
		break;
	case 2:
		viewNotices(); // TODO: Add notices
		displayParentScreen();
		break;
	case 3:
		if (!login.userLogout()) // Get the value of userLogout and if false, don't logout and re-display the parent screen
		{
			displayParentScreen();
		}
		break;
	default:
		cout << "Invalid option, please try again\n\n";
		system("pause");
		displayParentScreen();
	}
}

void Parent::readParent(std::string& line, std::string& classNum, std::string& childName)
{
	ifstream readParentFile("Sign_Up_And_Login_Details/parent_registration.txt");
	while (getline(readParentFile, line, '*'))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		if (line == login.savedUser)
		{
			for (int i = 0; i < 7; i++)
			{
				line.erase(remove(line.begin(), line.end(), '\n'), line.end());
				getline(readParentFile, line, ',');
			}
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			getline(readParentFile, classNum, ',');
			childName = line;
			readParentFile.close();
			break;
		}
	}
}

// Allow the parent user to view the data for each of there children
void Parent::viewChildReport()
{
	system("CLS");
	string classNum, line, childName, gender, mathMarks, scienceMarks, readingMarks, writingMarks, otherMarks;

	cout << "************\n";
	cout << "Child Record\n";
	cout << "************\n";
	readParent(line, classNum, childName);
	cout << "\nChild Name: " << childName << "\n";
	ifstream readClassFile("Classes/room_" + classNum + ".txt");
	while (getline(readClassFile, line, ','))
	{
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		if (line == childName)
		{
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			getline(readClassFile, gender, ',');
			getline(readClassFile, mathMarks, ',');
			getline(readClassFile, scienceMarks, ',');
			getline(readClassFile, readingMarks, ',');
			getline(readClassFile, writingMarks, ',');
			getline(readClassFile, otherMarks, ',');
			break;
		}
	}
	readClassFile.close();
	const char* fullGender = gender.c_str();
	cout << "Gender: " << displayGender(*fullGender) << "\n\n";
	cout << "Marks\n";
	cout << "------------------\n";
	cout << "Maths: " << "  " << mathMarks << "\n";
	cout << "Science: " << scienceMarks << "\n";
	cout << "Reading: " << readingMarks << "\n";
	cout << "Writing: " << writingMarks << "\n";
	cout << "Other: " << "  "<< otherMarks << "\n\n";
	//readParentFile.close();
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
	string userInput;

	system("CLS");
	ofstream writeFile("Sign_Up_And_Login_Details/parent_registration.txt", ios_base::app);

	// Initial personal details
	cout << "*******************\n";
	cout << "Parent Registration\n";
	cout << "*******************\n";
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
	cout << "\n\n";

	system("pause");
	system("CLS");

	// Child registration and info
	cout << "********************************\n";
	cout << "Parent Registration - Child Info\n";
	cout << "********************************\n";
	cout << "\nNumber of children attending Yoobee: ";
	cin >> childAmount; // Prompt the user to input the number of children they have

	// Loop up to till the number of children they have and prompt the user to enter information for each child
	for (int i = 0; i < childAmount; i++)
	{
		cout << "\nChild " << i + 1 << "\n";
		cout << "Child's full name: ";
		getline(cin >> ws, child.childName); // Use getline to allow the user to enter a string with spaces (doesn't seperate strings)
		cout << "Child's classroom number: ";
		cin >> child.childClass;
		cout << "Emergency Contact Caregiver's Full Name: ";
		getline(cin >> ws, child.emergencyContactName);
		cout << "Emergency Contact Number: ";
		cin >> child.emergencyContactNum;
		cout << "\n";
		childData.push_back({ child.childName,child.childClass,child.emergencyContactName,child.emergencyContactNum });
	}
	system("pause");

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
			cout << "Successfully signed up as a parent!\n\n";
			
			// Replace "cout" with the filename in write mode to write data to the file.
			// Here we write each of the data seperated by commas (and an asterisk between username and password)
			// to use them as delimeters and seperate the data into individual lines
			writeFile << userName << "*" << password << "," << fullName << "," << gender << "," << dob << "," << email << "," << contactNum << ",";
			// Loop through the child data and add everything from the vector into the file
			for (int i = 0; i < size(childData); i++) 
			{
				writeFile << "\n" << childData[i].childName << "," << childData[i].childClass << "," << childData[i].emergencyContactName <<
					"," << childData[i].emergencyContactNum << ",";
			}
			writeFile << "\n" << "*" << "\n";
			login.savedUser = userName; // Save the username so it is remembered by the program while the user is logged in
			writeFile.close();
			system("pause");
			displayParentScreen(); // Go to the parent screen once signed in
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
Parent::Parent(std::string _fullName, char _gender, std::string _dob, std::string _email, std::string _contactNum, std::string _userName)
{
	fullName = _fullName;
	gender = _gender;
	dob = _dob;
	email = _email;
	contactNum = _contactNum;
	userName = _userName;
}

Parent::Parent()
{

}

Parent::Child::Child(std::string _childName, int _childClass, std::string _emergencyContactName, 
	std::string _emergencyContactNum)
{
	childName = _childName;
	childClass = _childClass;
	emergencyContactName = _emergencyContactName;
	emergencyContactNum = _emergencyContactNum;
}

Parent::Child::Child()
{

}
