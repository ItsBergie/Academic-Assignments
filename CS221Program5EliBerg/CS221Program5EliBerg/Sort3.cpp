// Sort3.cpp - Quick Sort Implementation
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "Sort3.h"
#include <iomanip>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"

Sort3::Sort3()
{
    cout << "Eli Berg, CS221, Sort3: Quick Sort, Programming Assignment 5" << endl;
}

Sort3::~Sort3()
{
}

/* Quick sort works by selecting pivot element(this uses the last element) and paritions the array around the pivot */
void Sort3::Sorted(int array[], int len)
{
    if (showWork)
    {
        cout << "Original Array:";
        for (int i = 0; i < len; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    quickSort(array, 0, len - 1);
}

void Sort3::Print(int array[], int len)
{
    cout << "Quick Sort: ";
    for (int i = 0; i < len; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int Sort3::partition(int array[], int low, int high)
{

    // First element as pivot
    int pivot = array[low];

    int end = high;
    for (int i = high; i > low; i--) 
    {
        if (array[i] > pivot)
            swap(array[i], array[end--]);
    }
    swap(array[low], array[end]);

    
    // pivot is at its sorted position return pivot element index (end)
    return end;
}

void Sort3::quickSort(int array[], int start, int end)
{

	// base case
    if (start < end)
    {
        // partitioning the array
        int part = partition(array, start, end);

        if (showWork)
        {
            cout << "Array after partitioning: ";
            for (int i = start; i <= end; i++) 
            {
                if (i == part) cout << RED; // Highlight the pivot element
                cout << setw(2) << array[i] << " ";
                if (i == part) cout << RESET; // Reset color after pivot element
            }
            cout << endl;
        }

        // Sorting the left part
        quickSort(array, start, part - 1);

        // Sorting the right part
        quickSort(array, part + 1, end);
    }
}