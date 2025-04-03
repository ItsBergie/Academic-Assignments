// InventroyManager.h - InventoryManager header
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "Node.h"
#include "ItemType.h"
#pragma once

class InventoryManager
{
private:
	Node* head;
	Node* curPos;
	int maxNumItems;
	int length;

public:
	InventoryManager();
	
	InventoryManager(int maxItems);

	~InventoryManager();

	bool PutItem(ItemType* newItem);
	ItemType* GetItem(ItemType* itemToFind, bool& found);
	bool DeleteItem(ItemType* itemToDelete);
	void ResetList();
	bool IsFull();
	void MakeEmpty();
	void PrintList();
	Node* GetNext();
	int GetLength();
};


