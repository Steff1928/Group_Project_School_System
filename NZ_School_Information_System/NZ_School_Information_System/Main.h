#pragma once
#include "Login.h"
#include "Parent.h"

// Declare a variable of type Login to create an instance which can be used over every source file
// This will be used to save and load data from different classes when necessary
extern Login login; 

// Declare functions to convert certain values to strings when called
// This allows these functions to be used anywhere globally

std::string displayGender(const char gender); 
std::string displayOverallProgress(const int totalMarks);
std::string displayMarkingProgress(const int marks);

// Declare the displayRegistrationScreen function for better accessibility in the main file
// (We don't have to keep moving functions around)
void displayRegistrationScreen(); 
void inputFail(); // Declare a function which manages invalid inputs