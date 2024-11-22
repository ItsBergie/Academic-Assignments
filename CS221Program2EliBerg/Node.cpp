// Node.h - Node header
// For program 2 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "Node.h"


Node::Node()
{
    item = NULL;
    next = NULL;
}

Node::Node(ItemType newItem)
{
	item = new ItemType(newItem);
    next = NULL;
    
}

Node::~Node()
{
	delete item;
}

void Node::SetNext(Node* nextNode) 
{
    next = nextNode;
}

ItemType Node::GetItem() 
{
    return *item;
}

Node* Node::Next() 
{
    return next;
}