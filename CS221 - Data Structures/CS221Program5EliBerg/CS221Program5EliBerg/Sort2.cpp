// Sort2.cpp - Merge Sort Implementation
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022
#include "Sort2.h"
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

Sort2::Sort2()
{
    cout << "Eli Berg, CS221, Sort2: Merge Sort, Programming Assignment 5" << endl;
}

Sort2::~Sort2()
{
}

/* Merge Sort works by recursively dividing the input array into smaller subarrays 
and sorting those subarrays then merging them back together */
void Sort2::Sorted(int array[], int len)
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

    mergeSort(array, 0, len - 1);
}


void Sort2::merge(int array[], int left, int mid, int right)
{
    // Calculates Size of left and right subarrays and creates indexs for all left, right, and merged arrays
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
    int indexOfSubArrayOne = 0;
    int indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Create temporary arrays to store the left and right subarrays
    int* leftArray = new int[subArrayOne];
    int* rightArray = new int[subArrayTwo];

    if (showWork) //RED = seperated array; YELLOW = Sorted Merged Arrays
    {
        for (int i = left; i <= mid; i++)
        {
            cout << RED << array[i] << " " << RESET;
        }

        for (int j = mid + 1; j <= right; j++)
        {
            cout << RED << array[j] << " " << RESET;
        }
        cout << endl;
    }

    // Copy elements from the original array to the left subarray
    for (int i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = array[left + i];
    }

    // Copy elements from the original array to the right subarray
    for (int j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = array[mid + 1 + j];
    }


    // Merge the left and right subarrays into the original array
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        /* Compare the elements at the current indices of both subarrays 
        and merge them into the merged array in sorted order */ 
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) 
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else 
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;

        if (showWork) //YELLOW = Sorted Merged Arrays
        {
            cout << YELLOW << array[indexOfMergedArray - 1] << " " << RESET;
        }
    }

    // Copy any remaining elements from the left subarray
    while (indexOfSubArrayOne < subArrayOne) 
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;

        if (showWork) //YELLOW = Sorted Merged Arrays
        {
            cout << YELLOW << array[indexOfMergedArray - 1] << " " << RESET;
        }
    }

    // Copy any remaining elements from the right subarray
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        
        if (showWork) //YELLOW = Sorted Merged Arrays
        {
            cout << YELLOW << array[indexOfMergedArray - 1] << " " << RESET;
        }
    }

    if (showWork)
    {
        cout << endl;
        cout << "Merged arrays: ";
        for (int i = left; i <= right; i++) 
        {
            cout << array[i] << " ";
        }
        cout << endl << endl;
    }

    // Free the dynamically allocated memory from temp arrays
    delete[] leftArray;
    delete[] rightArray;
}

void Sort2::mergeSort(int array[], int const begin, int const end) 
{
    //base case
    if (begin >= end)
        return;
    
    int mid = begin + (end - begin) / 2;

    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void Sort2::Print(int array[], int len) 
{
    cout << "Completed Merge Sort: ";
    for (int i = 0; i < len; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
