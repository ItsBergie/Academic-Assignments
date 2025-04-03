// ItemType.cpp - ItemType Implementation
// For program 4 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "ItemType.h"
#include <string>
#include <iostream>
using namespace std;

ItemType::ItemType()
{
    name = "Jenny";
    address = "nowhere";
    number = "2568675309";
}

ItemType::ItemType(string name, string address, string number)
{
    this->name = name;
    this->address = address;
    this->number = number;
}

ItemType::~ItemType()
{
}

bool ItemType::operator<(ItemType& other)
{
    return name < other.name;
}

bool ItemType::operator>(ItemType& other)
{
    return name > other.name;
}

bool ItemType::operator==(ItemType& other)
{
    return name == other.name;
}

string ItemType::GetData() 
{
    return name;
}

string ItemType::GetData(string& addressRef, string& numberRef)
{
    addressRef = address;
    numberRef = number;
    return name;
}

void ItemType::SetData(string name, string address, string number)
{
    this->name = name;
    this->address = address;
    this->number = number;
}

void ItemType::PrintInfo() 
{
    cout << name << "," << address << "," << number;
}