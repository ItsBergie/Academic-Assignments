// Sort.h - Sort Header Class
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#pragma once

class Sort
{
protected:
	bool showWork;

public:
	Sort();
	~Sort();

	void SetShowWork(bool showWork);
	bool GetShowWork();
	virtual void Sorted(int array[], int len) = 0; //implement in derived classes
	virtual void Print(int array[], int len) = 0; //implement in derived classes
};

