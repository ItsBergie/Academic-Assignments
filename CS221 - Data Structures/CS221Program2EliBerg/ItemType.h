// ItemType.h - ItemType Header
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include <string>
using namespace std;
#pragma once

enum ComparisonResult
{
	EQUAL, LESS, GREATER
};

class ItemType
{
private:
	string description;
	long long int VIN;

public:
	ItemType();
	
	ItemType(string desc, long long int vin);
	
	~ItemType();

	
	ComparisonResult Compare(ItemType* other);
	long long GetData(string& desc);
	void PrintInfo();
};

