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
        viewClassRecords();
        break;
    case 2:
        viewParentRecords();
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
        inputFail();
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
    int totalMarks = 0;

    cout << "*************\n";
    cout << "Class Records\n";
    cout << "*************\n";

    // Prompt the user to enter a room number and display all of the data from that room in a table format
    cout << "\nEnter a room number: ";
    cin >> classroom;

    path = "Classes/room_" + to_string(classroom) + ".txt";
    readFile.open(path);

    const char* fullGender = gender.c_str();

    // If the file exists, get the line and check if it's equal to just an asterisk or check if the file doesn't exist
    // and notify the user accordingly.
    getline(readFile, line, ',');
    if (!readFile.is_open() || line == "*")
    {
        cout << "\nNo records available for this classroom yet.\n";
        system("pause");
        displayAdminScreen();
        return;
    }
    // Close and reopen the file to start from the beginning
    readFile.close();
    readFile.open(path);

    cout << "\nStudent Records for Room " << classroom << ": \n";

    // Get data for the student records from the teacher source file as to not repeat code
    teacher.getRecordData(readFile, line);

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
    const char* fullGender = gender.c_str();
    int totalMarks = 0;

    cout << "**************\n";
    cout << "Parent Records\n";
    cout << "**************\n";

    getline(readFile, line, ',');

    while (readFile.is_open())
    {
        getline(readFile, line, ',');
        
        line.erase(remove(line.begin(), line.end(), '*'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());

        getline(readFile, parentName, ',');
        getline(readFile, gender, ',');
        getline(readFile, dob, ',');
        getline(readFile, email, ',');
        getline(readFile, contactNum, ',');

        if (line != "")
        {
            cout << "\nFull Name          Gender          DOB           Email                         Contact Number";
            cout << "\n---------------------------------------------------------------------------------------------";

            cout << "\n" << left << setw(19) << parentName << setw(16) << displayGender(*fullGender) << setw(14) << dob << setw(30) 
                << email << contactNum << "\n";
            cout << "\nCHILD DATA:\n";

            while (childName != "*")
            {
                getline(readFile, childName, ',');
                childName.erase(remove(childName.begin(), childName.end(), '\n'), childName.end());

                if (childName == "*" || childName == "")
                {
                    break;
                }

                getline(readFile, childClassroomNum, ',');
                getline(readFile, emergencyContactName, ',');
                getline(readFile, emergencyContactNum, ',');
                if (childName != "*")
                {
                    cout << "\nName: " << childName
                        << "\nClassroom Number: " << childClassroomNum
                        << "\nEmergency Contact Name: " << emergencyContactName
                        << "\nEmergency Contact Number: " << emergencyContactNum << "\n";
                }
                getline(readFile, line);
            }
            cout << "\n";
            childName = "";
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
        // Generates a report of student who are in the progressing state
        system("CLS");
        generateReports(251, 375, "Progressing ");
        break;
    case 2:
        // Generates a report of students who need help
        generateReports(0, 250, "Needing Help");
        break;
    case 3:
        displayAdminScreen(); // Take the user back to the initial admin screen 
        break;
    default:
        inputFail();
        system("pause");
        generateReportsScreen();
    }
}

/// <summary>
/// Display reports of students who need help
/// </summary>
/// <param name="min">- The minimum value the program evaluates to decide on a report type</param>
/// <param name="max">- The maximum value the program evaluates to decide on a report type</param>
/// <param name="reportType">- The type type of report displayed as a string</param>
void Admin::generateReports(const int min, const int max, const string reportType)
{
    system("CLS");

    ifstream classFile;
    ifstream parentFile("Sign_Up_And_Login_Details/parent_registration.txt");
    ifstream teacherFile("Sign_Up_And_Login_Details/teacher_registration.txt");
    string teacherLine, line, path, teacherName, classroomNum, parentContactNum;
    string studentName, matProgress, sciProgress, writeProgress, readProgress, otherProgress;
    int totalMarks = 0;

    cout << "******************************           A = Achieved    P = Progressing    NH = Needs Help\n";
    cout << "Student Reports - " << reportType << "           --------------------------------------------------\n";
    cout << "******************************\n";

    cout << "\nClassroom    Full              Maths    Science    Writing    Reading    Other    Teacher           Parent's Contact";
    cout << "\nNumber       Name                                                                 Name              Number";
    cout << "\n--------------------------------------------------------------------------------------------------------------------";
    
    // LIAM: Can't figure out how to do error checking if no reports can be generated, gonna come back to this
    while (teacherFile.is_open())
    {
        getline(teacherFile, line, ',');
        getline(teacherFile, teacherName, ',');

        if (line != "\n*")
        {
            for (int i = 0; i < 5; i++)
            {
                getline(teacherFile, classroomNum, ',');
            }

            path = "Classes/room_" + classroomNum + ".txt";

            classFile.open(path);
        }
        while (classFile.is_open())
        {
            line.erase(remove(line.begin(), line.end(), '*'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());

            getline(classFile, line, ',');
            getline(classFile, studentName, ',');
            getline(classFile, line, ',');
            getline(classFile, matProgress, ',');
            getline(classFile, sciProgress, ',');
            getline(classFile, writeProgress, ',');
            getline(classFile, readProgress, ',');
            getline(classFile, otherProgress, ',');

            matProgress.erase(remove(matProgress.begin(), matProgress.end(), 'M'), matProgress.end());
            matProgress.erase(remove(matProgress.begin(), matProgress.end(), ':'), matProgress.end());
            sciProgress.erase(remove(sciProgress.begin(), sciProgress.end(), 'S'), sciProgress.end());
            sciProgress.erase(remove(sciProgress.begin(), sciProgress.end(), ':'), sciProgress.end());
            writeProgress.erase(remove(writeProgress.begin(), writeProgress.end(), 'W'), writeProgress.end());
            writeProgress.erase(remove(writeProgress.begin(), writeProgress.end(), ':'), writeProgress.end());
            readProgress.erase(remove(readProgress.begin(), readProgress.end(), 'R'), readProgress.end());
            readProgress.erase(remove(readProgress.begin(), readProgress.end(), ':'), readProgress.end());
            otherProgress.erase(remove(otherProgress.begin(), otherProgress.end(), 'O'), otherProgress.end());
            otherProgress.erase(remove(otherProgress.begin(), otherProgress.end(), ':'), otherProgress.end());

            totalMarks = stoi(matProgress) + stoi(sciProgress) + stoi(writeProgress) + stoi(readProgress) + stoi(otherProgress);

            parentFile.close();
            parentFile.open("Sign_Up_And_Login_Details/parent_registration.txt");

            if (line != "*")
            {
                if (totalMarks > min && totalMarks < max)
                {
                    while (getline(parentFile, line, ','))
                    {
                        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                        if (studentName == line)
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                getline(parentFile, line, ',');
                            }
                            parentContactNum = line;
                            break;
                        }
                    }

                    cout << "\n" << left << setw(13) << classroomNum << setw(18) << studentName << setw(9) << displayMarkingProgress(stoi(matProgress))
                        << setw(11) << displayMarkingProgress(stoi(sciProgress)) << setw(11) << displayMarkingProgress(stoi(writeProgress))
                        << setw(11) << displayMarkingProgress(stoi(readProgress)) << setw(9) << displayMarkingProgress(stoi(otherProgress))
                        << setw(18) << teacherName << parentContactNum;
                    cout << "\n--------------------------------------------------------------------------------------------------------------------";
                }
                getline(classFile, line);
            }
            else
            {
                getline(teacherFile, line, ',');
                classFile.close();
                break;
            }
        }
        if (teacherFile.eof())
        {
            teacherFile.close();
            classFile.close();
            parentFile.close();
        }
    }
    cout << "\n\n";
    system("pause");
    generateReportsScreen();
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
    classroom = 0;
}