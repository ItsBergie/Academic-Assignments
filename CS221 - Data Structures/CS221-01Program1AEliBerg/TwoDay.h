// TwoDay.h : This file contains TwoDay Class declaration
// Class demonstration for program 1A
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include <string>
using namespace std;

class TwoDay 
{
private:
    string name;
    string address;
    float costPerOunce;
    int numOunces;
    float flatTwoDayFee;

public:
    TwoDay(); // Default constructor
    TwoDay(string title, string addr, int ounces, float cost, float twodayfee); //Parameterized constructor, title = name
    ~TwoDay(); //Destructor
    
    string GetNameAndAddress() ;
    void SetName(string title);
    void SetAddress(string addy);
    void SetCostPerOz(float cost);
    float GetCostPerOz();
    int GetNumOz();
    void SetNumOz(int ounces);
    float GetTwoDayFee();
    void SetTwoDayFee(float fee);
    float CalculateTotalCost();
    void PrintInfo();
};

