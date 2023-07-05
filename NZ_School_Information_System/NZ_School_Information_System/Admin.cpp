#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Library to control how output is displayed (setw, etc)
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
    switch (choice) // Depending on the key pressed, run the designated function by switching on "choice"
    {
    case 1:
        displayClassRecords();
        break;
    case 2:
        displayParentRecords();
        break;
    case 3:
        generateReportsScreen(); 
        break;
    case 4:
        if (!login.userLogout()) // Get the value of userLogout and if false, don't logout and re-display the admin screen
        {
            displayAdminScreen();
        }
        break;
    default: // Manage invalid inputs if a case match is not found with "default"
        inputFail();
        system("pause");
        displayAdminScreen();
    }
}

// Display all the student records from a selected class
void Admin::displayClassRecords()
{
    system("CLS");
    ifstream readFile; // Define a file variable for looking in a class
    // Variables to store data from the class file, a line to look in the file and path to set the directory
    string line, id, path, studentName, gender, matMarks, sciMarks, readMarks, writeMarks, otherMarks, learningProgress;
    int totalMarks = 0;

    cout << "*************\n";
    cout << "Class Records\n";
    cout << "*************\n";

    // Prompt the user to enter a room number and display all of the data from that room in a table format
    cout << "\nEnter a room number: ";
    cin >> classroom;

    // Assign path to the classroom number entered and open that classroom file
    path = "Classes/room_" + to_string(classroom) + ".txt"; 
    readFile.open(path);

    const char* fullGender = gender.c_str(); // Store gender as a full word of a pointer of type const char*

    // Get the line and check if it's equal to just an asterisk or if the file doesn't exist
    // and notify the user accordingly.
    getline(readFile, line);
    if (!readFile.is_open() || line == "*")
    {
        cout << "\nNo records available for this classroom yet.\n";
        system("pause");
        displayAdminScreen();
        return; // Return an empty value to end the function
    }
    // Close and reopen the file to start from the beginning
    readFile.close();
    readFile.open(path);

    cout << "\nShowing Student Records for Room " << classroom << ": \n"; // Notify the user of which records they're viewing

    // Get data for the student records from the teacher source file as to not repeat code
    teacher.getRecordData(readFile, line);

    cout << "\n\n";
    system("pause");
    readFile.close(); // Close the file once finished
    displayAdminScreen(); // Go back to the admin screen once finished
}

// Display all of the records for parents who are registered in the system
void Admin::displayParentRecords()
{
    system("CLS");
    ifstream readFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Open the parent file
    string line, parentName, gender, dob, email, contactNum; // Variables to store data from the parent file and a line to look in the file
    string childName, childClassroomNum, emergencyContactName, emergencyContactNum; // Variables to store child data from the file
    const char* fullGender = gender.c_str(); // Store gender as a full word of a pointer of const char*

    cout << "**************\n";
    cout << "Parent Records\n";
    cout << "**************\n";

    getline(readFile, line, ','); // Get the first line to avoid a singular asterisk

    while (readFile.is_open()) 
    {
        getline(readFile, line, ','); // Get the next line to skip the username and password of the parent
        
        line.erase(remove(line.begin(), line.end(), '*'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());

        // Get the following information from the file and store it in variables accordingly
        getline(readFile, parentName, ',');
        getline(readFile, gender, ',');
        getline(readFile, dob, ',');
        getline(readFile, email, ',');
        getline(readFile, contactNum, ',');

        if (line != "") // If the line is not initially empty, display the parent and child data
        {
            cout << "\nFull Name          Gender          DOB           Email                         Contact Number";
            cout << "\n---------------------------------------------------------------------------------------------";

            // Display parent data in table format using setw()
            cout << "\n" << left << setw(19) << parentName << setw(16) << displayGender(*fullGender) << setw(14) << dob << setw(30) 
                << email << contactNum << "\n";
            // Display the child data for the parent
            cout << "\nCHILD DATA:\n";

            while (childName != "*") // As long as childName is not equal to a standalone asterisk, keep display child data
            {
                getline(readFile, childName, ','); // Get the name of the child
                childName.erase(remove(childName.begin(), childName.end(), '\n'), childName.end());

                if (childName == "*" || childName == "") // Break out of the loop if childname is empty or an asterisk
                {
                    break;
                }

                // Get the following child data from the file, store it in variables accordingly, and display it
                getline(readFile, childClassroomNum, ',');
                getline(readFile, emergencyContactName, ',');
                getline(readFile, emergencyContactNum, ',');
                
                cout << "\nName: " << childName
                    << "\nClassroom Number: " << childClassroomNum
                    << "\nEmergency Contact Name: " << emergencyContactName
                    << "\nEmergency Contact Number: " << emergencyContactNum << "\n";
                
                getline(readFile, line); // Get the next line to skip the parent's contact number
            }
            cout << "\n";
            childName = ""; // Reset the value of childName back to empty for the next parent
        }
        if (readFile.eof()) // Close the file once its at the end of its contents
        {
            readFile.close();
            cout << "\n";
        }
    }
    if (line == "") // If the line comes up empty in the parent file, notify the user 
    {
        cout << "No parent records to show.\n";
    }
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
    switch (choice) // Depending on the key pressed, run the designated function by switching on "choice"
    {
    case 1:
        // Generates a report of student who are in the progressing state
        system("CLS");
        generateAndDisplayReports(251, 375, "Progressing ");
        break;
    case 2:
        // Generates a report of students who need help
        generateAndDisplayReports(0, 250, "Needing Help");
        break;
    case 3:
        displayAdminScreen(); // Take the user back to the initial admin screen 
        break;
    default: // Manage invalid inputs if a case match is not found with "default"
        inputFail();
        system("pause");
        generateReportsScreen();
    }
}

/// <summary>
/// Display reports of students of either students who are progressing or need help
/// </summary>
/// <param name="min">- The minimum value the program evaluates to decide on a report type</param>
/// <param name="max">- The maximum value the program evaluates to decide on a report type</param>
/// <param name="reportType">- The type type of report displayed as a string</param>
void Admin::generateAndDisplayReports(const int min, const int max, const string reportType)
{
    system("CLS");
    ifstream classFile; // Define a file variable to look in the designated class file
    ifstream parentFile("Sign_Up_And_Login_Details/parent_registration.txt"); // Open the parent file
    ifstream teacherFile("Sign_Up_And_Login_Details/teacher_registration.txt"); // Open the teacher file
    // Variables to store data from the teacher file, the line to look through it and the path of the file
    string teacherLine, line, path, teacherName, classroomNum, parentContactNum;
    // Variables to store the learning progress for a student in each subject
    string studentName, matMarks, sciMarks, writeMarks, readMarks, otherMarks;
    int totalMarks = 0; // The total marks from each subject out of 500

    cout << "******************************           A = Achieved    P = Progressing    NH = Needs Help\n";
    cout << "Student Reports - " << reportType << "           --------------------------------------------------\n";
    cout << "******************************\n";

    // While not at the end of the teacher file, loop through every teacher to find their class and check to see if their class
    // is empty.
    while (!teacherFile.eof()) 
    {
        line = ""; // Reset the value of line to empty (if necessary)
        if (line != "\n*") 
        {
            for (int i = 0; i < 7; i++) // Loop through each value to get classroomNum
            {
                getline(teacherFile, classroomNum, ',');
            }
            path = "Classes/room_" + classroomNum + ".txt"; // Assign classroomNum value to path
            classFile.open(path); // Open classFile in path
            getline(classFile, line, ','); // Get the first line in the designated class file to check if it's empty
            if (line != "*") // If the line is not equal to a standalone asterisk, break, else keep looping through
            {
                break;
            }
            getline(teacherFile, line, ','); // Use getline here to skip to the next teacher
            classFile.close(); // Close classFile so it can be reopened in the next class
        }
    }
    // Close the files when the program has finished checking through them
    classFile.close();
    teacherFile.close();
    if (line == "") // If the line is empty, notify the user there were no reports to show
    {
        cout << "\nNo available reports to show from any class.\n";
        system("pause");
        generateReportsScreen();
        return;
    }

    cout << "\nClassroom    Full                Maths    Science    Writing    Reading    Other    Teacher           Parent's Contact";
    cout << "\nNumber       Name                                                                   Name              Number";
    cout << "\n----------------------------------------------------------------------------------------------------------------------";
    
    // While the teacher file is open, look through each teacher for their name and classroom number and get the student
    // data from that classroom, plus their parents phone number.
    teacherFile.open("Sign_Up_And_Login_Details/teacher_registration.txt");
    while (teacherFile.is_open()) 
    {
        // Skip the username and password and get the value of teacherName from the file
        getline(teacherFile, line, ',');
        getline(teacherFile, teacherName, ','); 

        // Check if the line is not equal to a delimiter (and a new line character) and get the classroom number for the teacher
        if (line != "\n*") 
        {
            for (int i = 0; i < 5; i++) // Loop through each value to get classroomNum
            {
                getline(teacherFile, classroomNum, ','); 
            }

            // Assign classroomNum to the path and open the class file in that path
            path = "Classes/room_" + classroomNum + ".txt"; 
            classFile.open(path);
        }
        while (classFile.is_open()) // While the class file is open, get the data for each student in the teachers class
        {
            line.erase(remove(line.begin(), line.end(), '*'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());

            // Get the following student data and store it in designated variables (using "line" to ignore redundant info)
            getline(classFile, line, ',');
            getline(classFile, studentName, ',');
            getline(classFile, line, ',');
            getline(classFile, matMarks, ',');
            getline(classFile, sciMarks, ',');
            getline(classFile, writeMarks, ',');
            getline(classFile, readMarks, ',');
            getline(classFile, otherMarks, ',');

            // Remove unimportant data from the progress variables
            matMarks.erase(remove(matMarks.begin(), matMarks.end(), 'M'), matMarks.end());
            matMarks.erase(remove(matMarks.begin(), matMarks.end(), ':'), matMarks.end());
            sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), 'S'), sciMarks.end());
            sciMarks.erase(remove(sciMarks.begin(), sciMarks.end(), ':'), sciMarks.end());
            writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), 'W'), writeMarks.end());
            writeMarks.erase(remove(writeMarks.begin(), writeMarks.end(), ':'), writeMarks.end());
            readMarks.erase(remove(readMarks.begin(), readMarks.end(), 'R'), readMarks.end());
            readMarks.erase(remove(readMarks.begin(), readMarks.end(), ':'), readMarks.end());
            otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), 'O'), otherMarks.end());
            otherMarks.erase(remove(otherMarks.begin(), otherMarks.end(), ':'), otherMarks.end());

            // Add up the marks from each subject and store it in totalMarks
            if (line != "*")
            {
                totalMarks = stoi(matMarks) + stoi(sciMarks) + stoi(writeMarks) + stoi(readMarks) + stoi(otherMarks);
            }
            // If it already has a value, reset parentContactNum to empty and reopen the parent file to find the correct
            // contact number.
            parentContactNum = "";
            parentFile.close();
            parentFile.open("Sign_Up_And_Login_Details/parent_registration.txt");

            // If the line in student is not equal to an asterisk, continue to the following
            if (line != "*")
            {
                // Depending on the max and min values, only output the student data depending on the report type
                if (totalMarks > min && totalMarks < max)
                {
                    while (getline(parentFile, line, ',')) // As long as the parent file exists, find a match for studentName in file
                    {
                        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                        // If studentName is found in the file, loop through to the parent's phone number and assign it to 
                        // parentContactNum
                        if (studentName == line) 
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                getline(parentFile, parentContactNum, ',');
                            }
                            break; // Break out of the loop when finished
                        }
                    }
                    if (parentContactNum == "") // If no value for parentContactNum could be found, set it to "N/A"
                    {
                        parentContactNum = "N/A";
                    }

                    // Display all of the data in a table like format using setw() to manage spacing
                    cout << "\n" << left << setw(13) << classroomNum << setw(20) << studentName << setw(9) << displayMarkingProgress(stoi(matMarks))
                        << setw(11) << displayMarkingProgress(stoi(sciMarks)) << setw(11) << displayMarkingProgress(stoi(writeMarks))
                        << setw(11) << displayMarkingProgress(stoi(readMarks)) << setw(9) << displayMarkingProgress(stoi(otherMarks))
                        << setw(18) << teacherName << parentContactNum;
                    cout << "\n----------------------------------------------------------------------------------------------------------------------";
                }
                getline(classFile, line); // Get the next line to avoid the learning observations in the file being outputted
            }
            else // If the line in the student file is an asterisk, get the next line in the teacher file and close the previous class file
            {
                getline(teacherFile, line, ',');
                classFile.close();
                break;
            }
        }
        if (teacherFile.eof()) // If the teacher file is at the end of its contents, close every file to stop outputting data
        {
            teacherFile.close();
            classFile.close();
            parentFile.close();
        }
    }
    cout << "\n\n";
    system("pause");
    generateReportsScreen(); // Go back to the generateReportsScreen once finished
}

// Intialise data for the admin account (this will run on start-up)
void Admin::initialiseAccount()
{
    // Write the intial login details for the admin account to a file
    ofstream writeFile;
    writeFile.open("Sign_Up_And_Login_Details/admin_login.txt");
    writeFile << userName << "*" << password;
    writeFile.close();
}

// Default constructor
Admin::Admin()
{
    classroom = 0;
}