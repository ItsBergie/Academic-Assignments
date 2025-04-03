// Overnight.h : This file contains Overnight Class declaration
// Class demonstration for program 1A
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include <string>
using namespace std;

class Overnight 
{
private:
    string name;
    string address;
    float costPerOunce;
    int numOunces;
    float extraPerOunce;

public:
    Overnight(); // Default constructor
    Overnight(string title, string addr, int ounces, float cost, float extraCost); // Parameterized constructor, title = name
    ~Overnight(); // Destructor

    string GetNameAndAddress();
    void SetName(string title);
    void SetAddress(string addr);
    void SetCostPerOz(float cost);
    float GetCostPerOz();
    int GetNumOz();
    void SetNumOz(int ounces);
    float GetExtraPerOz();
    void SetExtraPerOz(float extraCost);
    float CalculateTotalCost();
    void PrintInfo();
};


