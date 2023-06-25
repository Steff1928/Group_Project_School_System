#include <iostream>
#include <filesystem>
#include <fstream>
#include "Admin.h"
#include "Parent.h"
#include "Teacher.h"
#include "Main.h"

using namespace std;

// Initilise user and login objects to use there source files
Admin adminUser;
Parent parentUser;
Teacher teacherUser;
Login login; // Define the Login variable here to use the same instance in every source file

// Initialise classrooms
int classroom[5];

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
        // For invalid input, display an error message and prompt the user to try again
        cout << "Invalid option, please try again\n\n"; 
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
        cout << "Invalid option, please try again\n\n";
        system("pause");
    }
}

int main()
{
    // Create folder directories to store all the login/registration data, and list of classes
    filesystem::create_directory("Sign_Up_And_Login_Details");
    filesystem::create_directory("Classes");

    adminUser.initialiseAccount(); // Initialise login details for the admin user upon start-up

    while (true)
    {
        displayIntroScreen(); // Display program intro screen on start-up
    }
}