// ItemType.cpp - ItemType implementation
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "ItemType.h"
#include <iostream>
using namespace std;

ItemType::ItemType()
{
	description = "Undefined Car";
	VIN = 0;
}

ItemType::ItemType(string desc, long long int vin)
{
	description = desc;
	VIN = vin;
}

ItemType::~ItemType() 
{
	//destructor
};

ComparisonResult ItemType::Compare(ItemType* other)
{
	if (VIN == other->VIN)
	{
		return EQUAL;
	}
	else if (VIN < other->VIN)
	{
		return LESS;
	}
	else
	{
		return GREATER;
	}
}

long long int ItemType::GetData(string& desc)
{
	return VIN;
}

void ItemType::PrintInfo()
{
	cout << VIN << ", " << description;
}