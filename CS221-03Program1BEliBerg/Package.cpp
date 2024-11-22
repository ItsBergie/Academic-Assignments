// Package.cpp : This file contains Package CPP
// Class demonstration for program 1B
// Author: Eli Berg – This is my own work!
// email: erb0023@uah.edu
// For: CS221-03, Spring 2024 Mrs. Delugach
// Using compiler MSVS 2022

#include "Package.h"
#include <iostream>
using namespace std;

Package::Package()
{
	name = defaultName;
	address = defaultAddress;
	costPerOunce = defaultCostPerOunce;
	numOunces = defaultNumOunces;
	cout << "Welcome to Totally Not Amazon Shipping Service, Basic Package by Eli Berg!\n";
}

Package::Package(string title, string addr, int ounces, float cost)
{
	name = title;
	address = addr;
	SetCostPerOz(cost);
	SetNumOz(ounces);
	cout << "Welcome to Totally Not Amazon Shipping Service, Basic Package for " << name << "by Eli Berg!\n";
}

Package::~Package() 
{
	cout << "Ain't no way you getting a package now!\n";
}

void Package::GetNameAndAddress(string& title, string& addr)
{
	title = GetName();
	addr = GetAddress();
}

void Package::SetName(string title)
{
	name = title;
}

void Package::SetAddress(string addr)
{
	address = addr;
}

void Package::SetCostPerOz(float cost)
{
	if (cost < 0) 
	{
		costPerOunce = abs(cost);
	}
	else if (cost == 0)
	{
		costPerOunce = defaultCostPerOunce;
	}
	else
	{
		costPerOunce = cost;
	}
}

float Package::GetCostPerOz()
{
	return costPerOunce;
}

int Package::GetNumOz()
{
	return numOunces;
}

void Package::SetNumOz(int ounces)
{
	// Make sure it is at least 5
	numOunces = (ounces < defaultNumOunces) ? defaultNumOunces : ounces;
}

float Package::CalculateTotalCost()
{
	return numOunces * costPerOunce;
}

void Package::PrintInfo(string method, float extra)
{
	cout << "Ship to: " << name << "\n";
	cout << "Shipping Address: " << address << "\n";
	cout << "Method: " << method << "\n";
	cout << "Package weight: " << numOunces << " oz\n";
	cout << "Total Cost: $" << CalculateTotalCost() + extra << "\n";
}

string Package::GetName()
{
	return name;
}

string Package::GetAddress()
{
	return address;
}