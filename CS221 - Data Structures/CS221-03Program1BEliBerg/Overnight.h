// Overnight.h : This file contains Overnight Class declaration
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include "Package.h"
#include <string>
using namespace std;

class Overnight : public Package
{
private:

    float extraPerOunce;
    float defaultExtraPerOunce = 1.20;

public:
    Overnight(); // Default constructor
    Overnight(string title, string addr, int ounces, float cost, float extraCost); // Parameterized constructor, title = name
    ~Overnight(); // Destructor

    float GetExtraPerOz();
    void SetExtraPerOz(float extraCost);
    float CalculateTotalCost();
    void PrintInfo();
};


