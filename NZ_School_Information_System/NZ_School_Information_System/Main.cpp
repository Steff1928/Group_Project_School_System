#include <iostream>
#include <filesystem>
#include <fstream>
#include "Admin.h"
#include "Parent.h"
#include "Teacher.h"
#include "Login.h"

using namespace std;

// Initilise user and login objects
Admin adminUser;
Parent parentUser;
Teacher teacherUser;
Login login;

// Display the initial introduction screen, welcoming the user with a list of options
void displayIntroScreen()
{
    system("CLS");
    cout << "*******************************\n";
    cout << "Welcome to Yoobee School System\n";
    cout << "*******************************\n";

    // LIAM: Put all the code for displaying a certain menu (admin, parent, intro screens, etc) into a function
    // and run in it the main function.
    // This will make it easier to use the main function as a backdoor for accessing certain menu's when doing 
    // later testing :)
    system("pause");
}

void displayRegistrationScreen()
{
    while (true)
    {
        system("CLS");
        int choice;
        cout << "***************************\n";
        cout << "Yoobee Registration Options\n";
        cout << "***************************\n";

        cout << "\n1. Sign Up as Parent"
            << "\n2. Sign Up as Teacher"
            << "\n3. Back\n";

        cout << "\nEnter corresponding number for selection: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // TODO: Parent registration
            break;
        case 2:
            teacherUser.teacherSignUp();
            break;
        case 3:
            // TODO: Complete introduction screen
            displayIntroScreen();
        }
    }
}

int main()
{
    // Create a directory to store all the login/registration data, and list of classes
    filesystem::create_directory("Sign_Up_And_Login_Details");
    filesystem::create_directory("Classes");

    adminUser.initialiseAccount(); // Initialise login details

    while (true)
    {
        //displayIntroScreen(); // Display introduction screen on start-up
        login.userLogin();
    }
}