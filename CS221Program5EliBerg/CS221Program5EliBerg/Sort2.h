// Sort2.h - Merge Sort Class
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "sort.h"
#include <iostream>
#pragma once

class Sort2 : public Sort
{
private:
    void merge(int array[], int left, int mid, int right);
    void mergeSort(int array[], int begin, int end);

public:
    Sort2();
    ~Sort2();

    void Sorted(int array[], int len);
    void Print(int array[], int len);
};
