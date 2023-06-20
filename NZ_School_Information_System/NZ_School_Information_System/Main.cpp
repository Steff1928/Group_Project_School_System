#include <iostream>
#include <filesystem>
#include <fstream>
#include "Admin.h"
#include "Parent.h"
#include "Teacher.h"
#include "Login.h"

using namespace std;

// Initilise user and login objects (temporary)
Admin adminUser;
Parent parentUser;
Teacher teacherUser;
Login login;

// Initialise classrooms
int classroom[5];

void upcomingEvents()
{
    system("CLS");
    cout << "********************\n";
    cout << "Yoobee School Events\n";
    cout << "********************\n\n";

    cout << "dd/mm/yyyy: [Event details and additional info]\n";
    cout << "dd/mm/yyyy: [Event details and additional info]\n";
    cout << "dd/mm/yyyy: [Event details and additional info]\n\n";

    system("pause");
}

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

void displayRegistrationScreen();

// Display the initial introduction screen, welcoming the user with a list of options
void displayIntroScreen()
{
    system("CLS");
    cout << "*******************************\n";
    cout << "Welcome to Yoobee School System\n";
    cout << "*******************************\n";
    cout << "\nContact Info\n";
    cout << "--------------------------------\n";
    cout << "Phone Number: 0800 665 544\n";
    cout << "Email: yoobee@yoobeecolleges.com\n";
    cout << "--------------------------------\n";
    cout << "\n1. Upcoming/Current Events\n";
    cout << "2. Term Dates\n";
    cout << "3. Login\n";
    cout << "4. Registration\n";
    cout << "5. Exit\n";
    int userChoice = 0;

    cout << "\nEnter corresponding number for selection: ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:
        upcomingEvents();
        break;
    case 2:
        termDates();
        break;
    case 3:
        login.userLogin();
        break;
    case 4:
        displayRegistrationScreen();
        break;
    }
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
            // TODO: Complete rest of introduction screen
            displayIntroScreen();
            break;
        default:
            cout << "Invalid option, please try again\n\n";
            system("pause");
        }
    }
}
    }
}

int main()
{
    // Create a directory to store all the login/registration data, and list of classes
    filesystem::create_directory("Sign_Up_And_Login_Details");
    filesystem::create_directory("Classes");

    adminUser.initialiseAccount(); // Initialise login details for the admin user

    while (true)
    {
        displayIntroScreen(); // Display introduction screen on start-up
    }
}