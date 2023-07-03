#include <iostream>
#include <filesystem>
#include <fstream>
#include "Admin.h"
#include "Teacher.h"
#include "Main.h"

using namespace std;

// Initilise user and login objects to use there source files
Admin adminUser;
Parent parentUser;
Teacher teacherUser;

Login login; // Define the Login variable here to use the same instance in every source file
Parent parent;

/// <summary>
/// Takes in the first letter of the user's gender and returns the full word
/// </summary>
/// <param name="gender">- Gets the gender of the user</param>
/// <returns>A string displaying the complete word</returns>
std::string displayGender(const char gender)
{
    switch (gender)
    {
    case 'm':
        return "Male";
    case 'f':
        return "Female";
    case 'o':
        return "Other";
    default:
        return "N/A"; // Return an "N/A" value if an error occured
    }
}

/// <summary>
/// Take in the students total marks and return a string stating their overal learning progress
/// </summary>
/// <param name="totalMarks">- Gets the student's total marks from each subject added up</param>
/// <returns>A string with the complete word for the students learning progress</returns>
std::string displayOverallProgress(const int totalMarks)
{
    if (totalMarks <= 250)
    {
        return "Needs Help";
    }
    else if (totalMarks > 251 && totalMarks < 375)
    {
        return "Progressing";
    }
    else if (totalMarks >= 375)
    {
        return "Achieved";
    }
    return "N/A"; // Return an "N/A" value if an error occured
}

/// <summary>
/// Take in the students marks and return a string stating their overal learning progress
/// </summary>
/// <param name="marks">- Gets the students marks for a subject</param>
/// <returns>A string with the first character(s) of their learning progress </returns>
std::string displayMarkingProgress(const int marks)
{
    if (marks <= 50)
    {
        return "NH";
    }
    else if (marks > 51 && marks < 75)
    {
        return "P";
    }
    else if (marks >= 75)
    {
        return "A";
    }
    return "N/A"; // Return an "N/A" value if an error occured
}

// Display the upcoming/current event details on a seperate screen
void eventDetails()
{
    // The "system("CLS")" function is used to clear the console at the start of every method
    // We can use this to seperate output into designated screens
    system("CLS"); 

    cout << "********************\n";
    cout << "Yoobee School Events\n";
    cout << "********************\n\n";

    cout << "01/06/2023: National Open Day for Yoobee Campuses around New Zealand.\n";
    cout << "12/06/2023: Pride Month Event for week of 12/06 to 16/06.\n";
    cout << "08/05/2023: Term 2 has started.\n\n";
    
    // Pause the console before continuing so the screen isn't cleared immediately before the user sees the ouput
    system("pause"); 
}

// Display the term dates on a seperate screen
void termDates()
{
    system("CLS");
    cout << "*****************\n";
    cout << "Yoobee Term Dates\n";
    cout << "*****************\n\n";

    cout << "Term 1: 27/02 - 21/04/2023\n";
    cout << "Term 2: 08/05 - 30/06/2023\n";
    cout << "Term 3: 24/07 - 15/09/2023\n";
    cout << "Term 4: 02/10 - 24/11/2023\n\n";

    system("pause");
}

// Display the initial introduction screen, welcoming the user with a list of options
void displayIntroScreen()
{
    system("CLS");
    // Declare a choice variable for everytime the program takes input from the user to select an option in a menu
    // This allows the program to peform an action based on their input
    int choice; 
    cout << "*******************************\n";
    cout << "Welcome to Yoobee School System\n";
    cout << "*******************************\n";
    cout << "\nContact Info\n";
    cout << "--------------------------------\n";
    cout << "Phone Number: 0800-665-544\n";
    cout << "Email: yoobee@yoobeecolleges.com\n";
    cout << "--------------------------------\n";
    cout << "\n1. Upcoming/Current Events\n";
    cout << "2. Term Dates\n";
    cout << "3. Login\n";
    cout << "4. Registration\n";
    cout << "5. Exit\n";

    cout << "\nEnter corresponding number for selection: ";
    cin >> choice;
    // To peform an action, we use switch statements to run different code blocks depending on the user's choice
    switch (choice)
    {
    case 1:
        eventDetails(); // Run the eventDetails function when the user enters 1
        break;
    case 2:
        termDates(); // Run the termDates function when the user enters 2
        break;
    case 3:
        login.userLogin(); // Run the userLogin function when the user enters 3
        break;
    case 4:
        displayRegistrationScreen(); // Display the registration screen when the user enters 4
        break;
    case 5:
        cout << "Exiting Program... Goodbye!\n"; // Exit the program when the user enters 5
        exit(0);
    default:
        // For invalid input, manage errors with inputFail() and display a message to prompt the user to try again
        inputFail();
        system("pause");
        displayIntroScreen();
    }
}

// Display options on a seperate screen for signing up as different users
void displayRegistrationScreen()
{
    system("CLS");
    int choice;
    cout << "***************************\n";
    cout << "Yoobee Registration Options\n";
    cout << "***************************\n";

    cout << "\n1. Sign Up as Parent"
        << "\n2. Sign Up as Teacher"
        << "\n3. Back\n"; // Implement a "back" option to allow users to go back a screen for better exploration of the application
    cout << "\nEnter corresponding number for selection: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        parentUser.parentSignUp(); // Run the function to sign up as a parent
        break;
    case 2:
        teacherUser.teacherSignUp(); // Run the function to sign up as a teacher
        break;
    case 3:
        displayIntroScreen(); // Display the previous screen if the user inputted 3
        break;
    default:
        inputFail();
        system("pause");
        displayRegistrationScreen();
    }
}

// If the users input throws an error in any menu, run this function to clear it and continue
void inputFail()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "ERROR: Invalid input, please only enter numbers.\n\n";
    }
    else
    {
        cout << "Invalid option, please try again\n\n";
    }
}

int main()
{
    // Create folder directories to store all the login/registration data, and list of classes
    filesystem::create_directory("Sign_Up_And_Login_Details");
    filesystem::create_directory("Classes");

    adminUser.initialiseAccount(); // Initialise login details for the admin user upon start-up

    // Initialise parent and teacher registration files upon start up (make sure they exist)
    ofstream parentFile("Sign_Up_And_Login_Details/parent_registration.txt", ios_base::app);
    ofstream teacherFile("Sign_Up_And_Login_Details/teacher_registration.txt", ios_base::app);
    parentFile.close();
    parentFile.close();

    while (true)
    {
        displayIntroScreen(); // Display program intro screen on start-up
    }
}