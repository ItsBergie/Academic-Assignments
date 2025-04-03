/*
Filename: BergLab5.s
 Author:   Eli Berg
 Email:    erb0023@uah.edu
           CS413-02 2025

 Purpose:  Simulates the operation of a Keurig-style coffee machine in C++ using the Lab Raspberry pi.

 History:
    Date       Purpose of change
    ----       -----------------
   1-April-2025  Student created, edited, and completed conversion of code from ARM Assembly to C++

 Use these commands compile, build, and run this program
    c++ BergLab5.cpp -o Lab5Berg
    ./Lab5Berg
*/

#include <iostream>
#include <limits>

using namespace std;

// Function to display the main menu options for the coffee machine
void displayMenu() 
{
    cout << "\nInsert K-cup and press B to begin making coffee." << endl;
    cout << "Press T to turn off the machine." << endl;
    cout << "Press H or h to display secret menu." << endl;
}

// Function to display cup size selection
void displayCupSizes() 
{
    cout << "Select cup size: " << endl;
    cout << "1. Small (6 oz)" << endl;
    cout << "2. Medium (8 oz)" << endl;
    cout << "3. Large (10 oz)" << endl;
}

/*
Function: brewCoffee
Purpose: Handles the coffee brewing process, checks water level, updates inventory.
Parameters:
    - waterLevel: Reference to available water in the reservoir (in ounces).
    - smallCount, mediumCount, largeCount: References to counters for brewed cups.
Returns:
    - true: If the brewing process continues successfully.
    - false: If the water level is too low after brewing.
*/
bool brewCoffee(int &waterLevel, int &smallCount, int &mediumCount, int &largeCount) 
{
    int cupSize = 0;
    displayCupSizes();
    cin >> cupSize;

    // Input validation for cup size selection
    if (cin.fail() || cupSize < 1 || cupSize > 3) 
    {
        cout << "Invalid input. Please enter a valid option." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    // Determine the amount of water needed based on the selected cup size
    int waterNeeded = (cupSize == 1) ? 6 : (cupSize == 2) ? 8 : 10;
    
    // Check if there is enough water to brew the selected cup size
    if (waterLevel < waterNeeded) 
    {
        cout << "Not enough water. Select a smaller cup size or refill the reservoir." << endl;
        return true;
    }

    // Deduct used water and update the corresponding cup count
    waterLevel -= waterNeeded;
    if (cupSize == 1) smallCount++;
    if (cupSize == 2) mediumCount++;
    if (cupSize == 3) largeCount++;

    cout << "Brewing complete. Enjoy your coffee!" << endl;

    // If water level drops below the minimum requirement, notify the user
    if (waterLevel < 6) 
    {
        cout << "Water too low. Please refill the reservoir." << endl;
        return false;
    }

    return true;
}

/*
Function: showInventory
Purpose: Displays the current inventory of water and the number of brewed cups.
Parameters:
    - waterLevel: Current amount of water in the reservoir.
    - smallCount, mediumCount, largeCount: Number of each cup size brewed.
*/
void showInventory(int waterLevel, int smallCount, int mediumCount, int largeCount) 
{
    cout << "Water left: " << waterLevel << " oz" << endl;
    cout << "Small cups: " << smallCount << ", Medium cups: " << mediumCount << ", Large cups: " << largeCount << endl;
}


int main() 
{
    // Initialize water reservoir and cup counters
    int waterLevel = 48;
    int smallCount = 0, mediumCount = 0, largeCount = 0;
    char choice;

    cout << "Welcome to the Coffee Maker" << endl;
    
    // Main loop: Runs while the water level is sufficient
    while (true && waterLevel > 6) 
    {
        displayMenu();
        cin >> choice;

        if (choice == 'B' || choice == 'b') 
        {
            brewCoffee(waterLevel, smallCount, mediumCount, largeCount);
        } 
        else if (choice == 'T' || choice == 't') 
        {
            cout << "Turning off the coffee machine. Goodbye!" << endl;
            break;
        } 
        else if (choice == 'H' || choice == 'h') 
        {
            showInventory(waterLevel, smallCount, mediumCount, largeCount);
        } 
        else 
        {
            cout << "Invalid input. Please enter a valid option." << endl;
        }
    }
    return 0;
}
