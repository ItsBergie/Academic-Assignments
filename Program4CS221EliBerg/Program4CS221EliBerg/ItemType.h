// ItemType.h - ItemType header
// For program 4 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#pragma once
#include <string>
using namespace std;

class ItemType
{
private:
	string name;
	string address;
	string number;

public:
	ItemType();
	ItemType(string name, string address, string number);
	~ItemType();

	bool operator < (ItemType& other);
	bool operator > (ItemType& other);
	bool operator == (ItemType& other);

	string GetData();
	string GetData(string& address, string& number);
	void SetData(string name, string address, string number);
	void PrintInfo();
};