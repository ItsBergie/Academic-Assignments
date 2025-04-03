// Overnight.cpp : This file contains Overnight CPP
// Class demonstration for program 1A
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#include "Overnight.h"
#include <iostream>
using namespace std;

//Default constructor
Overnight::Overnight()
{
    name = "Undefinded";
    address = "Somewhere";
    costPerOunce = 0.00f;
    numOunces = 6;
    extraPerOunce = 0.0f;
    cout << "Welcome to Totally Not Amazon Shipping Service, Overnight package by Eli Berg!\n";
}

//Paramerterized constructor
Overnight::Overnight(string title, string addr, int ounces, float cost, float extraCost)
{
    name = title;
    address = addr;
    SetCostPerOz(cost);
    SetNumOz(ounces);
    SetExtraPerOz(extraCost);
    cout << "Welcome to Totally Not Amazon Shipping Service, Overnight package for " << title << ", by Eli Berg!\n";
}

//Destructor
Overnight::~Overnight()
{
    cout << "Thanks for maybe using our service. Goodbye!\n";
}

string Overnight::GetNameAndAddress()
{
    return name + " " + address;
}

void Overnight::SetName(string title)
{
    name = title;
}

void Overnight::SetAddress(string addr)
{
    address = addr;
}

void Overnight::SetCostPerOz(float cost)
{
    // Add error checking if necessary
   
    costPerOunce = abs(cost);
}

float Overnight::GetCostPerOz()
{
    return costPerOunce;
}

int Overnight::GetNumOz()
{
    return numOunces;
}

void Overnight::SetNumOz(int ounces)
{
    // Make sure it is at least 6
    numOunces = max(6, ounces);
}

float Overnight::GetExtraPerOz()
{
    return extraPerOunce;
}

void Overnight::SetExtraPerOz(float extraCost)
{
    extraPerOunce = extraCost;
}

float Overnight::CalculateTotalCost()
{
    return (numOunces * extraPerOunce) * costPerOunce;
}

void Overnight::PrintInfo()
{
    cout << "Ship to: " << name << "\n";
    cout << "Shipping Address: " << address << "\n";
    cout << "Method: Overnight\n";
    cout << "Package weight: " << GetNumOz() << " oz\n";
    cout << "Total Cost: $" << CalculateTotalCost() << "\n";
}

