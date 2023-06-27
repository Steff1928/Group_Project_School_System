#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Admin.h"
#include "Main.h"
using namespace std;

// Display restricted options for users logged in as an administrator
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

// Display all the student records from a selected class
void Admin::viewClassRecords()
{
    system("CLS");
    ifstream readFile;
    string line, id, path, studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, learningProgress;

    cout << "*************\n";
    cout << "Class Records\n";
    cout << "*************\n";

    // Prompt the user to enter a room number and display all of the data from that room in a table format
    cout << "\nEnter a room number: ";
    cin >> classroom;
    path = "Classes/room_" + to_string(classroom) + ".txt";
    readFile.open(path);
    const char* fullGender = gender.c_str();
    cout << "\nStudent Records for Room " << classroom << ": \n";

    cout << "\nID    Full Name                Gender    Maths    Science    Writing    Reading    Other    Learning Progress";
    cout << "\n-------------------------------------------------------------------------------------------------------------";

    while (readFile.is_open())
    {
        while (getline(readFile, line, ','))
        {
            line.erase(remove(line.begin(), line.end(), '*'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());

            getline(readFile, studentName, ',');
            getline(readFile, gender, ',');
            getline(readFile, matMarks, ',');
            getline(readFile, sciMarks, ',');
            getline(readFile, readMarks, ',');
            getline(readFile, writeMarks, ',');
            getline(readFile, otherMarks, ',');
            getline(readFile, learningProgress, ',');

            learningProgress.erase(remove(learningProgress.begin(), learningProgress.end(), ','), learningProgress.end());
            break;
        }
        if (line != "")
        {
            cout << "\n" << left << setw(6) << line << setw(25) << studentName << setw(10)
                << displayGender(*fullGender) << setw(9) << matMarks << setw(11) << sciMarks << setw(11)
                << readMarks << setw(11) << writeMarks << setw(9) << otherMarks << learningProgress;
            cout << "\n-------------------------------------------------------------------------------------------------------------";
        }
        if (readFile.eof())
        {
            readFile.close();
        }
    }
    cout << "\n\n";
    system("pause");
    displayAdminScreen(); // Go back to the admin screen once finished
}

// Display all of the records for parents who are registered in the system
void Admin::viewParentRecords()
{
    system("CLS");
    ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt");
    string line, parentName, gender, dob, email, contactNum;
    string childName, childClassroomNum, emergencyContactName, emergencyContactNum;
    int childAmount = 0;
    cout << "**************\n";
    cout << "Parent Records\n";
    cout << "**************\n";

    // TEMP: Structure for displaying student data in a table
    cout << "\nFull Name    Gender    DOB           Email                    Contact         Children    Children     Emergency";
    cout << "\n                                                              Number          Names       Classroom    Contact";
    cout << "\n                                                                                          Number(s)";
    cout << "\n-----------------------------------------------------------------------------------------------------------------";

    while (readFile.is_open())
    {
        while (getline(readFile, line))
        {
            getline(readFile, line);

            line.erase(remove(line.begin(), line.end(), '*'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());

            childAmount++;

            if (line == "")
            {
                break;
            }
        }

        while (getline(readFile, line, ','))
        {
            line.erase(remove(line.begin(), line.end(), '*'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());

            getline(readFile, parentName, ',');
            getline(readFile, gender, ',');
            getline(readFile, dob, ',');
            getline(readFile, email, ',');
            getline(readFile, contactNum, ',');
            for (int i = 0; i < childAmount; i++)
            {
                getline(readFile, childName, ',');
                getline(readFile, childClassroomNum, ',');
                getline(readFile, contactNum, ',');
            }
        }
    }
    
    
    /*cout << "\nDavid        Male      21/05/89      example@example.co.nz    02145761574     Stacy       5            Liam";
    cout << "\nProsser                                                                       Morgan                   Anthony";
    cout << "\n                                                                                                       0214597134\n";
    cout << "\n                                                                              John        3            Mark";
    cout << "\n                                                                              Doe                      Robinson";
    cout << "\n                                                                                                       0213871295\n";
    cout << "\n                                                                              Max         3            Jonathan";
    cout << "\n                                                                              Douglas                  Brown";
    cout << "\n                                                                                                       0278145936\n\n";*/
    system("pause");
    displayAdminScreen();
}

// Generate reports for students depending on their learning progress
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
        generateReportsScreen();
        break;
    case 2:
        // TODO: Students needing help report (perhaps extract in a function)
        generateReportsScreen();
        break;
    case 3:
        displayAdminScreen(); // Take the user back to the initial admin screen 
        break;
    default:
        cout << "Invalid option, please try again\n\n";
        system("pause");
        generateReportsScreen();
    }
}

// Display reports of students who need help
void Admin::generateProgressionReports()
{
    ifstream readFile("Sign_Up_And_Login_Details/teacher_registration.txt");
    cout << "*****************************\n";
    cout << "Student Reports - Progressing\n";
    cout << "*****************************\n";

    cout << "\nClassroom    Full    Maths    Science    Writing    Reading    Other    Teacher    Parent’s Contact";
    cout << "\nNumber       Name                                                       Name       Number";
    cout << "\n---------------------------------------------------------------------------------------------------";
}
// Display reports of students who are progressing
void Admin::generateHelpReports()
{

}

// Intialise data for the admin account (this will run on start-up)
void Admin::initialiseAccount()
{
    // Write the intial login details for the admin to a file
    ofstream writeFile;
    writeFile.open("Sign_Up_And_Login_Details/admin_login.txt");
    writeFile << userName << "*" << password;
    writeFile.close();
}

Admin::Admin()
{
    // Initialise admin login details
    userName = "admin";
    password = "admin";
}
