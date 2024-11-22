// TwoDay.cpp : This file contains TwoDay CPP File
// Class demonstration for program 1A
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#include "TwoDay.h"
#include <iostream>
using namespace std;

//Default constructor
TwoDay::TwoDay()
{
    name = "Undefinded";
    address = "Somewhere";
    costPerOunce = 0.00f;
    numOunces = 6;
    flatTwoDayFee = 0.0f;

	cout << "Welcome to Totally Not Amazon Shipping Service, Two Day package by Eli berg!\n";
}

//Paramerterized constructor
TwoDay::TwoDay(string title, string addr, int ounces, float cost, float twoDayFee)
{
    name = title;
    address = addr;
    SetCostPerOz(cost);
    SetNumOz(ounces);
    SetTwoDayFee(twoDayFee);
	cout << "Welcome to Totally Not Amazon Shipping Service, Two Day package for " << title << ", by Eli Berg!\n";
}

//Destructor
TwoDay::~TwoDay()
{
	cout << "Thanks for maybe using our service. Goodbye!\n";
}

string TwoDay::GetNameAndAddress()
{
    return name + " " + address;
}

void TwoDay::SetName(string title)
{
    name = title;
}

void TwoDay::SetAddress(string addr) 
{
    address = addr;
}

void TwoDay::SetCostPerOz(float cost) 
{
    // Add error checking if necessary
    costPerOunce = abs(cost);
}

float TwoDay::GetCostPerOz()
{
    return costPerOunce;
}

int TwoDay::GetNumOz() 
{
    return numOunces;
}

void TwoDay::SetNumOz(int ounces) 
{
    // Make sure it is at least 6
    numOunces = max(6, ounces);
}

float TwoDay::GetTwoDayFee() 
{
    return flatTwoDayFee;
}

void TwoDay::SetTwoDayFee(float fee) 
{
    flatTwoDayFee = fee;
}

float TwoDay::CalculateTotalCost() 
{
    return numOunces * costPerOunce + flatTwoDayFee;
}

void TwoDay::PrintInfo() 
{
    cout << "Ship to: " << name << "\n";
    cout << "Shipping Address: " << address << "\n";
    cout << "Method: TwoDay\n";
    cout << "Package weight: " << GetNumOz() << " oz\n";
    cout << "Total Cost: $" << CalculateTotalCost() << "\n";
}