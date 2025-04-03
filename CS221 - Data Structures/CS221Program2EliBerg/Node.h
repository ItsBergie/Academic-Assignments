// Node.h - Node header
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#pragma once
#include "ItemType.h"

class Node
{
private:
	ItemType* item;
	Node* next;

public:
	Node();
	Node(ItemType newItem);
	~Node();

	void SetNext(Node* nextNode);
	ItemType GetItem();
	Node* Next();
};

