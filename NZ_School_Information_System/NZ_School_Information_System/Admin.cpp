#include <iostream>
#include <fstream>
#include "Admin.h"
using namespace std;

void Admin::displayAdminScreen()
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
        viewClassRecords(); // TODO: Complete table for display the class records
        break;
    case 2:
        viewParentRecords(); // TODO: Complete table for display the parent records
        break;
    case 3:
        generateReportsScreen();
        break;
    case 4:
        if (!login.userLogout())
        {
            displayAdminScreen();
        }
        break;
    default:
        cout << "Invalid option, please try again\n\n";
        system("pause");
        displayAdminScreen();
    }
}

void Admin::viewClassRecords()
{
    system("CLS");
    ifstream readData;
    string line;
    cout << "*************\n";
    cout << "Class Records\n";
    cout << "*************\n";

    cout << "\nEnter a room number: ";
    cin >> classroom;
    readData.open("Classes/room_"+ to_string(classroom) + ".txt");
    cout << "\nStudent Records for Room " << classroom << ": \n";
   /* while (getline(readData, line))
    {
        cout << line;
    }*/
    cout << "\nID    Full Name    Gender    Maths    Science    Writing    Reading    Other    Learning  Progress";
    cout << "\n--------------------------------------------------------------------------------------------------";
    cout << "\n1     Stephen      Male      50       70         81         79         100      Progressing";
    cout << "\n      Prosser\n\n";
    system("pause");
    displayAdminScreen();
}

void Admin::viewParentRecords()
{
    system("CLS");
    ifstream readData;
    cout << "*************\n";
    cout << "Parent Records\n";
    cout << "*************\n";

    cout << "Full Name    Gender    DOB           Email                    Contact       Children   Children Classroom    Emergency";
    cout << "\n                                                              Number        Names      Number(s)             Contact";
    cout << "\n-----------------------------------------------------------------------------------------------------------------------";
    cout << "\nDavid        Male      21/05/89      example@example.co.nz    021457615     Stacy      5                     Liam Anthony";
    cout << "\nProsser                                                                     Morgan                           0214597134\n\n";
    system("pause");
    displayAdminScreen();
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
        cout << "Invalid option, please try again\n\n";
        system("pause");
        generateReportsScreen();
    }
}

void Admin::initialiseAccount()
{
    // Write the intial login details for the admin to a file
    ofstream writeFile;
    writeFile.open("Sign_Up_And_Login_Details/admin_login.txt");
    writeFile << userName << password;
    writeFile.close();
}

Admin::Admin()
{
    // Initialise admin login details
    userName = "admin";
    password = "admin";
}
