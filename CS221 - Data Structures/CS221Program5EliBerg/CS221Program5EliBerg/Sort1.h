// Sort1.h - Bubble Sort Class
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "sort.h"
#include <iostream>
#pragma once

class Sort1 : public Sort
{

public:
    Sort1();
    ~Sort1();

    void Sorted(int array[], int len);
    void Print(int array[], int len);
};

