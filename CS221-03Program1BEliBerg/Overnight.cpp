// Overnight.cpp : This file contains Overnight CPP
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#include "Overnight.h"
#include <iostream>
using namespace std;

//Default constructor
Overnight::Overnight() : Package()
{
    extraPerOunce = defaultExtraPerOunce;
    cout << "Welcome to Totally Not Amazon Shipping Service, Overnight package by Eli Berg!\n";
}

//Paramerterized constructor
Overnight::Overnight(string title, string addr, int ounces, float cost, float extraCost) 
{
    
    cout << "Welcome to Totally Not Amazon Shipping Service, Overnight package for " << title << ", by Eli Berg!\n";
}

//Destructor
Overnight::~Overnight()
{
    cout << "Thanks for maybe using our service. Goodbye!\n";
}

float Overnight::GetExtraPerOz()
{
    return extraPerOunce;
}

void Overnight::SetExtraPerOz(float extraCost)
{
    extraPerOunce = (extraCost < 0) ? abs(extraCost) : extraCost;
}

float Overnight::CalculateTotalCost()
{
    return Package::CalculateTotalCost() + (GetNumOz() * extraPerOunce);
}

void Overnight::PrintInfo()
{
    return Package::PrintInfo("Overnight", (GetNumOz() * extraPerOunce));
}

