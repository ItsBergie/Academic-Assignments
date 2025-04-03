// Sort3.h - Quick Sort Class
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "sort.h"
#include <iostream>
#pragma once

class Sort3 : public Sort
{
private:
    void quickSort(int array[], int start, int end);
    int partition(int array[], int low, int high);

public:
    Sort3();
    ~Sort3();

    void Sorted(int array[], int len);
    void Print(int array[], int len);
};
