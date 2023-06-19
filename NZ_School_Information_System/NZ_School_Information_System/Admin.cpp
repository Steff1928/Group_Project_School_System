#include <iostream>
#include <fstream>
#include "Admin.h"
using namespace std;

void Admin::viewClassRecords()
{
   
}

void Admin::viewParentRecords()
{
    
}

void Admin::initialiseAccount()
{
    // Write the intial login details for the admin to a file
    ofstream writeData;
    writeData.open("Sign_Up_And_Login_Details/admin_login.txt");
    writeData << userName << "," << password;
    writeData.close();

}

Admin::Admin()
{
    // Initialise admin login details
    userName = "admin";
    password = "admin";
}
