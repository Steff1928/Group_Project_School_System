#include <iostream>
#include <fstream>
#include "Admin.h"
using namespace std;

void Admin::displayAdminScreen()
{
    while (true)
    {
        system("CLS");
        int choice;
        cout << "******************************************\n";
        cout << "Yoobee Portal - Logged in as administrator\n";
        cout << "******************************************\n";
        cout << "\n1. View Class Records\n"
            << "2. View Parent Records\n"
            << "3. Generate Reports\n"
            << "4. Logout\n";
        cout << "\nEnter corresponding number for selection: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("pause");
            viewClassRecords();
            break;
        case 2:
            system("pause");
            viewParentRecords();
            break;
        case 3:
            generateReportsScreen();
            break;
        case 4:
            // TODO: Make logout function
            exit(0);
            break;
        default:
            cout << "Please enter valid options only, try again\n\n";
            system("pause");
        }
    }
}

void Admin::viewClassRecords()
{
   
}

void Admin::viewParentRecords()
{
    
}

void Admin::generateReportsScreen()
{
    int choice;
    system("CLS");

    cout << "**********************\n";
    cout << "Student Report Options\n";
    cout << "**********************\n";
    
    cout << "\n1. View report of Progressing Students\n"
        << "2. View report of Students who Need Help\n"
        << "3. Back\n";
    cout << "\nEnter corresponding number for selection: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        // TODO: Progressing students report (perhaps extract in a function)
        break;
    case 2:
        // TODO: Students needing help report (perhaps extract in a function)
        break;
    case 3:
        displayAdminScreen();
        break;
    default:
        cout << "Please enter valid options only, try again\n\n";
        system("pause");
    }
}

void Admin::initialiseAccount()
{
    // Write the intial login details for the admin to a file
    ofstream writeFile;
    writeFile.open("Sign_Up_And_Login_Details/admin_login.txt");
    writeFile << userName << "," << password;
    writeFile.close();
}

Admin::Admin()
{
    // Initialise admin login details
    userName = "admin";
    password = "admin";
}
