#include <iostream>
#include <fstream>
#include <ctime> // Allows manipulation of date and time info
#include "Login.h"
#include "Teacher.h"
#include "Admin.h"

using namespace std;

/// <summary>
/// If there are no username/password matches in any file, minus an attempt and if the user has no attempts left,
/// lock them out of their account for 10 seconds
/// </summary>
/// <param name="loginAgain"> - Boolean to determine whether a prompt should be given to the user to login again </param>
void Login::manageLoginAttempts(bool& loginAgain)
{
	loginAttempts--; // Decrement login attempts

	if (loginAttempts <= 0 && start == 0) // If the user has no login attempts left and start is at its default, start the timer
	{
		start = clock();
		beginTimer = true;
	}
	// If the user has more than 3 login attempts left, notify the user to try again, else notify them they have been locked out
	if (loginAttempts > 0) 
	{
		cout << "\nInvalid username or password\n\n";
	}
	else
	{
		cout << "\nToo many failed attempts, you have been locked out for " << seconds << " seconds.\n";
	}
	loginAgain = true; // Set loginAgain to true to prompt the user accordingly
}

/// <summary>
/// Searches for a match for login and username in a selected file
/// </summary>
/// <param name="readFile">- The file the program should look for a match in</param>
/// <param name="lineInFile">- A string to get each line in the file</param>
/// <param name="entry">- The users attempt to login combining both username and password</param>
/// <returns>A boolean value depending if the user was successful or not to login in the current file</returns>
bool Login::getMatchInFile(std::ifstream& readFile, std::string& lineInFile, std::string entry)
{
	// If there is a match in the current file, login as that user
	while (getline(readFile, lineInFile, ','))
	{
		// Remove any \n or * characters so they are not read by the compiler when checking for valid matches
		lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '\n'), lineInFile.end());
		lineInFile.erase(remove(lineInFile.begin(), lineInFile.end(), '*'), lineInFile.end());
		if (lineInFile == entry)
		{
			cout << "\nSuccessfully logged in!\n\n";
			loginAttempts = 3; // Set login attempts back to 3 so the user isn't punished for logging in correctly
			savedUser = userName; // Set the logged in username to a variable to save that data from the user
			system("pause");
			return true;
		}
	}
	return false;
}

// Manage login data to take users to their required screen and manage invalid attempts
void Login::userLogin()
{
	char confirmAnswer; // Confimration variable
	// Variables for opening the teacher, parent and admin login/registration files
	ifstream readTeacher;
	ifstream readAdmin;
	ifstream readParent;

	// Objects
	Teacher teacherLogin;
	Admin adminLogin;
	Parent parentLogin;
	string line;

	// Loop through the login function until a match is found in a file
	do
	{	
		system("CLS");
		// Set confirmAnswer back to no by default so the loop does not run again after the user is finished in 
		// their screen
		confirmAnswer = 'n'; // Set confirmAnswer to no by default
		cout << "************\n";
		cout << "Yoobee Login\n";
		cout << "************\n";
		// Open each of the files to read data from
		readTeacher.open("Sign_Up_And_Login_Details/teacher_registration.txt");
		readAdmin.open("Sign_Up_And_Login_Details/admin_login.txt");
		readParent.open("Sign_Up_And_Login_Details/parent_registration.txt");

		// Prompt the user to enter their username and password
		cout << "\nUsername: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;
		string entry = userName + password; // Concatenate the two strings into a single string to be compared against
		bool loginAgain = false; // Check to see if the user should be prompted to login again (false by default) 

		// Start a timer if the user has no login attempts left
		if (beginTimer)
		{
			seconds = 10.0f - static_cast<time_t>((clock() - start) / 1000);
		}

		if (seconds <= 0) // Reset timer when seconds goes below 0 and unlock the users account by setting important values back to their defaults
		{
			start = 0;
			seconds = 10.0f;
			beginTimer = false;
			loginAttempts = 3;
		}

		bool filesAreOpen = readTeacher.is_open() && readAdmin.is_open() && readParent.is_open(); // Boolean to check if each login/registration file is open
		bool endOfFiles = readTeacher.eof() && readAdmin.eof() && readParent.eof(); // Boolean to check if each login/registration file is at the end of its contents

		// Read through each registration/login file for each user to search for a match
		while (filesAreOpen) // Ensure the loop can only run if each file is open
		{
			// Ensure the program only checks the files if they are not at the end of their contents and login attempts is greater than 0
			if (!endOfFiles && loginAttempts > 0) 
			{
				if (getMatchInFile(readTeacher, line, entry)) // Check to see if the user is logging in as a teacher
				{
					// Display the designated user screen if a match in a file is confirmed
					// Once the user is finished in their account, close the file and break out of the loop
					teacherLogin.displayTeacherScreen(); 
					readTeacher.close();
					break;
				}
				if (getMatchInFile(readAdmin, line, entry)) // Check to see if the user is logging in as an admin
				{
					adminLogin.displayAdminScreen();
					readAdmin.close();
					break;
				}
				userName = "," + userName; // Add a comma onto username so the parent name is read properly (since it's intitially delimited with "*,")
				if (getMatchInFile(readParent, line, entry)) // Check to see if the user is logging in as a parent
				{
					parentLogin.displayParentScreen();
					readParent.close();
					break;
				}
				endOfFiles = true; // Set endOfFiles to true since the program should have now finished reading through each file
			}
			// If there are no matches in any file, run the manageLoginAttempts function to control the users login attempts
			else 
			{
				filesAreOpen = false; // Set filesAreOpen to false to signify they should be closed
				manageLoginAttempts(loginAgain);
				break;
			}
		}
		// If the user did not login correctly, ask if they want to login again.
		// If not, send them back to the main menu
		if (loginAgain)
		{
			cout << "Attempt to login again? (y/n): ";
			cin >> confirmAnswer;
			// Close every file since the program has finished with them for now
			readTeacher.close();
			readAdmin.close();
			readParent.close();
		}
	} while (confirmAnswer == 'y'); // If the user says no, end the loop
	cout << "\n";
}

/// <summary>
/// Display a screen with information telling the user they've successfully logged out
/// </summary>
/// <returns>A bool that return true of false depending of if the user confirms that they logged out</returns>
bool Login::userLogout()
{
	char confirmAnswer;
	cout << "Are you sure you want to logout? (y/n): ";
	cin >> confirmAnswer;
	if (confirmAnswer == 'y') // Only log the user out if their answer is yes
	{
		system("CLS");
		cout << "					             ***********\n";
		cout << "					             LOGGING OUT\n";
		cout << "					             ***********\n";
		cout << "\n					     Returning to the Main Menu\n\n";
		system("pause");
		return true; // Return the value of true to be evaluated against
	}
	return false; // If the user entered no, return false since the user did not logout
}