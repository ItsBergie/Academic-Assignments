// Sort.cpp - Base Sort Implementation
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "Sort.h"
using namespace std;

Sort::Sort() //no duties
{
	showWork = false;
}

Sort::~Sort() //no duties
{
}

void Sort::SetShowWork(bool show)
{
	showWork = show;
}

bool Sort::GetShowWork()
{
	return showWork;
}
 
void Sort::Sorted(int array[], int len) //implement in derived classes
{

}

void Sort::Print(int array[], int len) //implement in derived classes
{

}