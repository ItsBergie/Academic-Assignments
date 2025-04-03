// BSTree.h - Binary Search Tree Header
// For program 4 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "ItemType.h"
#pragma once

struct TreeNode
{
	ItemType info;
	TreeNode* left;
	TreeNode* right;
};

class BSTree
{
private:
	TreeNode* root;
	TreeNode* pointer; //Used only by Iterator and GetNext()
	int count;
	int maxCapacity = 500;
	
	//These are all the helper recurive function for their respective public functions
	TreeNode* FindMin(TreeNode* node); // find min between children
	bool PutItemHelper(TreeNode*& node, ItemType item);
	ItemType GetItemHelper(TreeNode* tree, ItemType& item, bool& found);
	void DeleteHelper(TreeNode*& tree, ItemType item);
	void DeleteNode(TreeNode*& tree);
	void GetPredecessor(TreeNode* tree, ItemType& data);
	void MakeEmptyHelp(TreeNode* root);
	void PrintInOrderPrivate(TreeNode* Ptr);
	void Print2DHorizontal(TreeNode* root, int space);
	void PrintToCSV(TreeNode* node, ofstream& outFile);
	
public:
	BSTree();
	BSTree(const BSTree& tree);
	void operator=(const BSTree& original);
	~BSTree();

	bool PutItem(ItemType item);
	ItemType GetItem(ItemType item, bool& found);
	bool DeleteItem(ItemType item);
	void ResetTree();
	void MakeEmpty();
	void PrintTree();
	ItemType GetNext();
	int GetCount();
	void PrintTreeForm();
	void CopyTree(const TreeNode* copy, TreeNode*& OG);

	//Added another public function to print to CSV file (only way I could output the list with all elements)
	void PrintToCSV();
};

