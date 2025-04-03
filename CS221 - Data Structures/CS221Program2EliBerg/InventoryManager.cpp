// InventoryManager.cpp - InventoryManager implementation
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "InventoryManager.h"
#include <iostream>
#include <iomanip>

using namespace std;

InventoryManager::InventoryManager()
{
}

InventoryManager::InventoryManager(int maxItems)
{
	head = NULL;
	curPos = NULL;
	maxNumItems = maxItems;
	length = 0;
	cout << "Eli Berg's Vehicle Inventory Manager" << endl;
}

InventoryManager::~InventoryManager()
{
	MakeEmpty();
}

bool InventoryManager::PutItem(ItemType* newItem)
{
	if (IsFull())
	{
		return false;
	}


	bool found;
	ItemType* existingItem = GetItem(newItem, found);
	string desc;
	

	if (!found)
	{
		Node* newNode = new Node(*newItem);
		newNode->SetNext(head);
		head = newNode;
		length++;

		cout << "Added: ";
		newItem->PrintInfo();
		cout << "; New Node: " << newItem << endl << endl;
		return true;
	}
	else
	{
		cout << endl << newItem->GetData(desc) << ": Already Present\n" << endl;;
		
		return false;
	}	
}

ItemType* InventoryManager::GetItem(ItemType* itemToFind, bool& found)
{
	Node* current = head;
	cout << "Searching...";
	while (current != nullptr)
	{
		ItemType currentItem = current->GetItem();
		

		if (currentItem.Compare(itemToFind) == EQUAL)
		{
			found = true;
			cout << "; \nFound: ";
			currentItem.PrintInfo();
			cout << " ";
			return new ItemType(currentItem); 
		}

		currentItem.PrintInfo();
		cout << "; ";
		current = current->Next();
	}

	found = false;
	cout << "\nnot found" << endl;
	return NULL;
}

bool InventoryManager::DeleteItem(ItemType* itemToDelete)
{
	Node* current = head;
	Node* previous = NULL;

	while (current != NULL) 
	{
		if (current->GetItem().Compare(itemToDelete) == EQUAL) 
		{
			cout << "Deleted: ";
			itemToDelete->PrintInfo();
			cout << "; Deleted Address: " << current << endl;

			if (previous == NULL) 
			{
				head = current->Next();
			}
			else {
				previous->SetNext(current->Next());
			}

			delete current;
			length--;
			return true;
		}

		previous = current;
		current = current->Next();
	}

	return false;
}
void InventoryManager::ResetList()
{
	curPos = head;
}

bool InventoryManager::IsFull()
{
	return (length == maxNumItems);
}

void InventoryManager::MakeEmpty()
{
	while (head != NULL) 
	{
		Node* temp = head;
		head = head->Next();
		delete temp;
	}
	
	cout << "\nEnd of List, List is Empty" << endl;
	curPos = NULL;
	length = 0;
}

void InventoryManager::PrintList()
{
	Node* current = head;


	while (current != NULL) 
	{

		current->GetItem().PrintInfo();
		cout << setw(25) <<  "at " << current << endl;
		current = current->Next();
	}
}

Node* InventoryManager::GetNext()
{
	Node* current = curPos;

	if (curPos != NULL) 
	{
		curPos = curPos->Next();
	}

	return current;
}

int InventoryManager::GetLength() 
{
	return length;
}
