#pragma once
#include "Login.h"
// Declare a variable of type Login to create an instance which can be used over every source file
// This will be used to save and load data from different classes when necessary
extern Login login; 
// Declare the displayRegistrationScreen function for better accessibility in the main file
// (We don't have to keep moving functions around)
void displayRegistrationScreen(); 