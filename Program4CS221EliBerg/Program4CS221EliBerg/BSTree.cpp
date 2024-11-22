// BSTree.cpp - Binary Search Tree Implementation
// For program 4 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "BSTree.h"
#include "ItemType.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


BSTree::BSTree()
{
	cout << "Eli Berg = Program 4 - Boo Boo Begone for Animals Vet" << endl;
	root = nullptr;
	pointer = nullptr;
	TreeNode* left = NULL;
	ItemType* info = NULL;
	TreeNode* right = NULL;
	count = 0;
	maxCapacity = 500;
}

BSTree::BSTree(const BSTree& original)
{
	CopyTree(original.root, root);
	count = original.count;
	maxCapacity = original.maxCapacity;
}

void BSTree::operator=(const BSTree& original)
{
	if (this != &original)
	{ // avoids assigning object to itself
		MakeEmpty(); //clear existing data

		// Copy data from orginal
		CopyTree(original.root, root);
		count = original.count;
		maxCapacity = original.maxCapacity;
	}
}

BSTree::~BSTree()
{
	MakeEmpty();
}

bool BSTree::PutItem(ItemType item)
{
	return PutItemHelper(root, item);
}

bool BSTree::PutItemHelper(TreeNode*& tree, ItemType item)
{
	if (tree == NULL) 
	{
		tree = new TreeNode;
		tree->info = item;
		tree->left = NULL;
		tree->right = NULL;
		count++;
		cout << "added " << item.GetData() << endl;
	}
	else if (item < tree->info) 
	{
		return PutItemHelper(tree->left, item);
	}
	else if (item > tree->info) 
	{
		return PutItemHelper(tree->right, item);
	}
	else 
	{
		cout << "Item already present." << endl;
		return false;
	}
}

ItemType BSTree::GetItem(ItemType item, bool& found)
{
	cout << "Searching..." << endl;
	return GetItemHelper(root, item, found);
}

ItemType BSTree::GetItemHelper(TreeNode* tree, ItemType& item, bool& found) 
{
	
	if (tree == nullptr) 
	{
		found = false;
		cout << "Not Found\n";
		item = ItemType();
	}
	else if (item < tree->info) 
	{
		cout << tree->info.GetData() << endl; //prints itmms to get to result
		return GetItemHelper(tree->left, item, found);
	}
	else if (item > tree->info) 
	{
		cout << tree->info.GetData() << endl; //prints itmms to get to result
		return GetItemHelper(tree->right, item, found);
	}
	else 
	{
		item = tree->info;
		found = true;
		cout << "found" << endl; // Print "found"
	}
	return item;
}

bool BSTree::DeleteItem(ItemType item)
{
	DeleteHelper(root, item);
	cout << "Deleted: " << item.GetData() << endl;
	count--;
	return true;
}

void BSTree::DeleteNode(TreeNode*& tree)
{
	ItemType data;
	TreeNode* tempPtr;

	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		GetPredecessor(tree->left, data);
		tree->info = data;
		DeleteHelper(tree->left, data);
	}
}

void BSTree::DeleteHelper(TreeNode*& tree, ItemType item)
{
	if (tree == nullptr)
	{
		// Item not found, do nothing
		return;
	}

	if (item < tree->info)
	{
		DeleteHelper(tree->left, item);
	}
	else if (item > tree->info)
	{
		DeleteHelper(tree->right, item);
	}
	else
	{
		DeleteNode(tree);
	}
}

void BSTree::GetPredecessor(TreeNode* tree, ItemType& data)
{
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	data = tree->info;
}

void BSTree::MakeEmpty()
{
	MakeEmptyHelp(root);
	root = nullptr;
	count = 0;
}

void BSTree::ResetTree()
{
	TreeNode* pointer = nullptr;
}

void BSTree::MakeEmptyHelp(TreeNode* root)
{
	if (root == nullptr)
	{
		return;
	}
	MakeEmptyHelp(root->left);
	MakeEmptyHelp(root->right);
	cout << "\nDelete node: " << root->info.GetData();
	delete root;
	
}

void BSTree::PrintTree()
{
	cout << "Print Tree: " << endl;
	PrintInOrderPrivate(root);
	cout << "\nTree Count: " << GetCount() << endl;
}

void BSTree::PrintInOrderPrivate(TreeNode* root)
{
	if (root == NULL)
	{
		cout << "The Tree is Empty\n";
		return;
	}
	else if (root->left != nullptr)
	{
		PrintInOrderPrivate(root->left);
	}

	root->info.PrintInfo();// Assuming GetData() returns a string
	cout << endl;

	if (root->right != nullptr)
	{
		PrintInOrderPrivate(root->right);
	}
}
	
ItemType BSTree::GetNext()
{
	ItemType result;
	// Start from the root
	if (pointer == nullptr)
	{
		pointer = FindMin(root); // Initialize pointer to the minimum element
	}
	else
	{
		// If there is a right subtree, go to the leftmost node of that subtree
		if (pointer->right != nullptr)
		{
			pointer = FindMin(pointer->right);
		}
		else
		{
			// If there is no right subtree, go up the tree until we find a node
			// where pointer is in the left subtree
			TreeNode* temp = root;
			TreeNode* successor = nullptr;
			while (temp != nullptr)
			{
				if (pointer->info < temp->info)
				{
					successor = temp;
					temp = temp->left;
				}
				else if (pointer->info > temp->info)
				{
					temp = temp->right;
				}
				else
				{
					break;
				}
			}
			
			pointer = successor;
		}
	}

	// If pointer is not null, return the data of pointer
	if (pointer != nullptr)
	{
		result = pointer->info;
	}
	else
	{
		// If pointer is null, return a default ItemType
		result =  ItemType(); // Assuming ItemType has a default constructor
	}

	return result; //variable created to hold return value
}

int BSTree::GetCount()
{
	return count;
}

void BSTree::PrintTreeForm() //prints tree horizontally - BST turned 90 degrees
{
	Print2DHorizontal(root, 0); 
}

void BSTree::CopyTree(const TreeNode* OG, TreeNode*& copy)
{
	if (OG == nullptr)
	{
		copy = nullptr;
	}
	else
	{
		copy = new TreeNode;
		copy->info = OG->info;
		CopyTree(OG->left, copy->left);
		CopyTree(OG->right, copy->right);
	}
}

TreeNode* BSTree::FindMin(TreeNode* node)
{
	if (node == nullptr)
	{
		node = nullptr;
	}
	else
	{
		node = node->left;
	}
	return node;
}

void BSTree::Print2DHorizontal(TreeNode* root, int space)
{
	// Base case
	if (root == nullptr)
		return;

	// Increase distance between levels
	space += 10;

	// Process right child first
	Print2DHorizontal(root->right, space);

	// Print current node after space
	cout << endl;
	for (int i = 10; i < space; i++)
	{
		cout << " ";
	}

	cout << root->info.GetData() << "\n";

	// Process left child
	Print2DHorizontal(root->left, space);
}

void BSTree::PrintToCSV(TreeNode* node, ofstream& outFile) 
{
	if (node == nullptr)
	{
		return;
	}

	// Recursively print left subtree
	PrintToCSV(node->left, outFile);

	// Print current node's data to CSV
	ItemType item = node->info;
	string name, address, phoneNumber;
	name = item.GetData();
	item.GetData(address, phoneNumber); // Extract address and phone number
	outFile << setw(30) << left << name << setw(30) << left << address << setw(15) << left << phoneNumber << endl;

	// Recursively print right subtree
	PrintToCSV(node->right, outFile);
}

void BSTree::PrintToCSV() 
{
	ofstream outFile("ClientsSorted.csv");

	if (!outFile) 
	{
		cerr << "Error: Unable to open file ClientsSorted.csv" << endl;
		return;
	}

	outFile << setw(30) << left << "Name:" << setw(30) << left << "Address:" << setw(15) << left << "Phone Number:" << endl;
	PrintToCSV(root, outFile);
	outFile.close();
}