#include <iostream>
#include <filesystem>
#include <fstream>
#include "Admin.h"
#include "Parent.h"
#include "Teacher.h"

using namespace std;

// Display the initial introduction screen, welcoming the user with a list of options
void displayIntroScreen()
{
    cout << "*******************************\n";
    cout << "Welcome to Yoobee School System\n";
    cout << "*******************************\n";

    // LIAM: Put all the code for displaying a certain menu (admin, parent, intro screens, etc) into a function
    // and run in it the main function.
    // This will make it easier to use the main function as a backdoor for accessing certain menu's when doing 
    // later testing :)
}

int main()
{
    // Initilise user objects (admin, teacher, parent)
    Admin adminUser;
    Parent parentUser;
    Teacher teacherUser;

    // Create a directory to store all the login/registration data, and list of classes
    filesystem::create_directory("Sign_Up_And_Login_Details"); 
    filesystem::create_directory("Classes"); 

    adminUser.initialiseAccount(); // Initialise login details upon start-up

    displayIntroScreen(); // Display introduction screen
}