// TwoDay.cpp : This file contains TwoDay CPP File
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#include "TwoDay.h"
#include <iostream>
using namespace std;

//Default constructor
TwoDay::TwoDay() : Package()
{
    flatTwoDayFee = defaultTwoDayFee;

    cout << "Welcome to Totally Not Amazon Shipping Service, Two Day package by Eli berg!\n";
}

//Paramerterized constructor
TwoDay::TwoDay(string title, string addr, int ounces, float cost, float twoDayFee)
{
    flatTwoDayFee = twoDayFee;
    cout << "Welcome to Totally Not Amazon Shipping Service, Two Day package for " << title << ", by Eli Berg!\n";
}

//Destructor
TwoDay::~TwoDay()
{
    cout << "Thanks for maybe using our service. Goodbye!\n";
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
    return Package::CalculateTotalCost() + flatTwoDayFee;
}

void TwoDay::PrintInfo()
{
    Package::PrintInfo("Two Day", flatTwoDayFee);
}