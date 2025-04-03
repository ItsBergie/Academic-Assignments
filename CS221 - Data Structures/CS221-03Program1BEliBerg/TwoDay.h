// TwoDay.h : This file contains TwoDay Class declaration
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include "Package.h"
#include <string>
using namespace std;

class TwoDay : public Package
{
private:
    float flatTwoDayFee;
    const float defaultTwoDayFee = 9.00;

public:
    TwoDay(); // Default constructor
    TwoDay(string title, string addr, int ounces, float cost, float twodayfee); //Parameterized constructor, title = name
    ~TwoDay(); //Destructor

    float GetTwoDayFee();
    void SetTwoDayFee(float fee);
    float CalculateTotalCost();
    void PrintInfo();
};

