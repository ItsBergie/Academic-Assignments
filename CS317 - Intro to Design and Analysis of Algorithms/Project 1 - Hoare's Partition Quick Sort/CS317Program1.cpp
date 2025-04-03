/*
Author: Eli Berg
Email: erb0023@uah.edu
Due Date: 3/27/25
Course Section: CS317-01
OS: Windows 11
Compiler: GCC
IDE: Visual Studio

Description:
This program reads a list of words from an input file, sorts them using the QuickSort algorithm,
and writes the sorted words to an output file. The program also measures the sorting time, asks the user for
words-per-line formatting, and re-sorts an already sorted list to measure performance differences.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip> 

using namespace std;

// Function prototypes
void swap(string& a, string& b);  // Swap two strings
string toLower(const string& str);  // Convert string to lowercase for case-insensitive comparison
int partition(string arr[], int low, int high);  // Partition function for QuickSort
void quickSort(string arr[], int low, int high);  // Recursive QuickSort function

// Swap function (pass by reference)
void swap(string& a, string& b)
{
    string temp = a;
    a = b;
    b = temp;
}

// Convert string to lowercase
string toLower(const string& str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Hoare's Partition function for QuickSort
int partition(string arr[], int low, int high)
{
    string pivot = arr[low];  // Choose first element as pivot
    int i = low - 1;
    int j = high + 1;

    while (true)
    {
        // Move i forward until a word >= pivot is found
        do
        {
            i++;
        } while (toLower(arr[i]) < toLower(pivot));

        // Move j backward until a word <= pivot is found
        do
        {
            j--;
        } while (toLower(arr[j]) > toLower(pivot));

        if (i >= j)  // If indices cross, return partition index
            return j;

        swap(arr[i], arr[j]);  // Swap elements to place them in correct partition
    }
}

// QuickSort function
void quickSort(string arr[], int low, int high)
{
    if (low < high)
    {
        int part = partition(arr, low, high);  // Partition the array
        quickSort(arr, low, part);  // Sort left half
        quickSort(arr, part + 1, high);  // Sort right half
    }
}

int main() {
    // Display welcome message
    cout << "Welcome to the sorting words program.\n";

    // Allocate memory dynamically for storing words
    int maxSize = 100000;
    string* words = new string[maxSize];
    int count = 0;  // Counter for number of words read

    // Prompt user for input and output filenames
    string inputFile, outputFile;
    cout << "Please enter the name of your input data file: ";
    cin >> inputFile;
    cout << "Please enter the name of the output data file: ";
    cin >> outputFile;

    // Open input file
    ifstream infile(inputFile);
    if (!infile)
    {
        cerr << "Error opening input file!\n";
        delete[] words;
        return 1;
    }

    // Read words from file
    while (count < maxSize && infile >> words[count])
    {
        count++;
    }
    infile.close();

    // Handle empty file scenario
    if (count == 0)  
    {
        cerr << "No words found in the input file!\n";
        delete[] words;
        return 1;
    }

    // Display number of words found
    cout << count << " words were found in the file: " << inputFile << ".\n";

    // Ask user for words per line
    int wordsPerLine;
    cout << "How many words per line should be printed? ";
    cin >> wordsPerLine;

    // Sort words using QuickSort and measure time
    auto start1 = chrono::high_resolution_clock::now();
    quickSort(words, 0, count - 1);
    auto end1 = chrono::high_resolution_clock::now();

    // Convert time to microseconds
    auto elapsed1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "The initial Quicksort took " << fixed << setprecision(0) << elapsed1 << " microseconds\n";

    // Write sorted words to output file
    ofstream outfile(outputFile);
    if (!outfile)
    {
        cerr << "Error opening output file!\n";
        delete[] words;
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        outfile << words[i] << " ";
        if ((i + 1) % wordsPerLine == 0)
        {
            outfile << "\n";
        }
    }
    outfile.close();
    cout << "Results printed to " << outputFile << "\n";

    // Re-sort the already sorted list
    cout << "Re-sorting the already sorted list\n";
    auto start2 = chrono::high_resolution_clock::now();
    quickSort(words, 0, count - 1);
    auto end2 = chrono::high_resolution_clock::now();

    // Convert re-sorting time to microseconds
    auto elapsed2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "The already sorted list took " << fixed << setprecision(0) << elapsed2 << " microseconds\n";

    // Calculate percentage increase with floating-point precision
    double percentageIncrease = ((elapsed2 - elapsed1) / elapsed1) * 100;
    cout << "An increase of about " << fixed << setprecision(0) << percentageIncrease << "%\n";

    // Free allocated memory
    delete[] words;

    // End program message
    cout << "End program.\n";

    return 0;
}
