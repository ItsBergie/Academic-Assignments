// Sort1.cpp - Bubble Sort Implementation
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "Sort1.h"
#include <iomanip>
using namespace std;

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"

Sort1::Sort1() 
{
	cout << "Eli Berg, CS221, Sort1: Bubble Sort, Programming Assignment 5" << endl;
}

Sort1::~Sort1() 
{
}

/* Bubble sort works by repeatedly swapping the adjacent elements if they are in the wrong order */
void Sort1::Sorted(int array[], int len) 
{
    if (showWork)
    {
        cout << "Original Array:";
        for (int index = 0; index < len; index++)
        {
            cout << " " << array[index];
        }
        cout << endl;
    }

    int index = 0;
    int startIndex = 0;
    bool swapped;

    // Iterate through the array
    for (int index = 0; index < len - 1; index++)
    {
        swapped = false;

        if (showWork)
        {
            cout << "Pass " << index + 1 << ":" << endl;
        }

        for (int startIndex = 0; startIndex < len - index - 1; startIndex++)
        {
            // If the current element is greater than the next element, swap them
            if (array[startIndex] > array[startIndex + 1])
            {
                swap(array[startIndex], array[startIndex + 1]);
                swapped = true;

                if (showWork)
                {
                    // Print the array with color-coded swapped elements (Red elements = swapped)
                    for (int i = 0; i < len; ++i)
                    {
                        if (i == startIndex || i == startIndex + 1)
                        {
                            cout << RED << setw(3) << array[i] << RESET; // Adjust width as needed
                        }
                        else
                        {
                            cout << setw(3) << array[i]; // Adjust width as needed
                        }
                    }
                    cout << endl;
                }
            }
        }


        // If no elements were swapped in this pass, the array is already sorted
        if (swapped == false)
        {
            break;
        }
    }
}

void Sort1::Print(int array[], int len) 
{
    cout << "Bubble Sort:";
    int index;
    for (int index = 0; index < len; index++) 
    {
        cout << " " << array[index];
    }
    cout << endl;
}