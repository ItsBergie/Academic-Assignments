// Package.h : This file contains Package Class declaration
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include <string>
using namespace std;

class Package
{
private:
    string name;
    string address;
    float costPerOunce;
    int numOunces;
    const string defaultName = "Undefined";
    const string defaultAddress = "Nowhere";
    const float defaultCostPerOunce = 0.45;
    const int defaultNumOunces = 5;

public:
    Package(); // Default constructor
    Package(string title , string addr, int ounces, float cost); // Parameterized constructor, title = name
    ~Package(); // Destructor


    void GetNameAndAddress(string& title, string& addr);
    void SetName(string title);
    void SetAddress(string addr);
    void SetCostPerOz(float cost);
    float GetCostPerOz();
    int GetNumOz();
    void SetNumOz(int ounces);
    float CalculateTotalCost();
    void PrintInfo(string method = "Package", float extra = 0.0);

protected:
    string GetName();
    string GetAddress();
};
