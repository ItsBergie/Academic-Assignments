// CS221Program5.cpp - Driver For Sorts and Timing
// For program 5 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022#include "Sort.h"
#include "Sort1.h"
#include "Sort2.h"
#include "Sort3.h"
#include <chrono>
using namespace std;
using namespace chrono;

void SortItOut(Sort& sorter, int Array[], int len); //Teacher Sorting Function
void SortTimer(); //Function to Time Sorts
void sortsSorted(); //Function to Test Sorts

int main() 
{
    //Function To Test Sorts
    sortsSorted();

    // Times each sort through large array of random numbers
    SortTimer();

    return 0;
}

void SortItOut(Sort& sorter, int Array[], int len)
{
    sorter.SetShowWork(true); // or false, as I choose during testing
    sorter.Sorted(Array, len);
    sorter.Print(Array, len);
}

void SortTimer()
{
    cout << "Instantiate New Classes to Test Times (Each Array has 1000 Elements and Ranges from Numbers 0-10000):" << endl;
    const int len = 1000; // Size of the array to be sorted
    int Array4[len]; // Array to be sorted
    int Array5[len]; // Array to be sorted
    int Array6[len]; // Array to be sorted

    // Initialize the array with random values
    for (int i = 0; i < len; ++i)
    {
        // Random numbers between 0 and 10000
        Array4[i] = rand() % 10000;
        Array5[i] = rand() % 10000;
        Array6[i] = rand() % 10000;
    }

    // Create Sort1 object
    Sort1 bubble;
    
    // Create Sort2 object
    Sort2 merge;

    // Create Sort3 object
    Sort3 quick;

    cout << endl << "Timing Sorts:" << endl;

    // Sort and print using Sort1, and measure execution time
    auto start1 = high_resolution_clock::now();
    bubble.Sorted(Array4, len);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Bubble Sort Time: " << duration1.count() << " microseconds" << endl;
    quick.Print(Array4, len);
    cout << endl;
   
    // Sort and print using Sort2, and measure execution time
    auto start2 = high_resolution_clock::now();
    merge.Sorted(Array5, len);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Merge Sort Time: " << duration2.count() << " microseconds" << endl;
    quick.Print(Array5, len);
    cout << endl;

    // Sort and print using Sort3, and measure execution time
    auto start3 = high_resolution_clock::now();
    quick.Sorted(Array6, len);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "Quick Sort Time: " << duration3.count() << " microseconds" << endl;
    quick.Print(Array6, len);
    cout << endl;
}

void sortsSorted()
{
    cout << "Testing Each Sort Now (Restart Program to Test New Arrays):" << endl;


    const int len = 15; // Size of the array to be sorted
    int Array[len]; // Array to be sorted
    int Array2[len]; // Array to be sorted
    int Array3[len]; // Array to be sorted

    // Initialize the array with random values
    for (int i = 0; i < len; ++i)
    {
        // Random numbers between 0 and 100
        Array[i] = rand() % 100;
        Array2[i] = rand() % 100;
        Array3[i] = rand() % 100;
    }

    // Create Sort1 object
    Sort1 sorter1;
    // Sort and print using Sort1
    SortItOut(sorter1, Array, len);

    cout << endl;

    // Create Sort2 object
    Sort2 sorter2;

    // Sort and print using Sort2
    SortItOut(sorter2, Array2, len);

    cout << endl;

    // Create Sort3 object
    Sort3 sorter3;

    // Sort and print using Sort3
    SortItOut(sorter3, Array3, len);

    cout << endl;
}