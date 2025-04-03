// CS221Program4.cpp - Text-based Menu Implementation
// For program 4 assignment
//
// Author: Eli Berg, This is entirely my own work
// email: erb0023@uah.edu
// for CS221-03, Spring '24 Mrs. Delugach
// Compiler MSVS 2022

#include "BSTree.h"
#include "ItemType.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void readDataFromFile(BSTree& tree, string filename);
void addClient(BSTree& clientTree);
void deleteClient(BSTree& clientTree);
void retrieveClient(BSTree& clientTree);
void runMenu(BSTree& clientTree);

int main() //Use forward declaration and put other functions below
{
    BSTree clientList;

    readDataFromFile(clientList, "Clientlist.csv");

    runMenu(clientList);

    return 0;
}

void readDataFromFile(BSTree& tree, string filename)
{
    ifstream readFile("Clientlist.csv");

    if (!readFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(readFile, line)) 
    {
        if (!line.empty()) 
        {
            stringstream ss(line);
            string name, address, phoneNumber;

            // Extract individual fields
            getline(ss, name, ',');
            getline(ss, address, ',');
            getline(ss, phoneNumber, ',');

            // Create ItemType and insert into BST
            ItemType item(name, address, phoneNumber);
            tree.PutItem(item);
        }
    }

    readFile.close();
}

void addClient(BSTree& clientTree)
{
    string name, address, phoneNumber;
    cout << "Enter client name: ";
    getline(cin >> ws, name);
    cout << "Enter client address: ";
    getline(cin >> ws, address);
    cout << "Enter client phone number: ";
    getline(cin >> ws, phoneNumber);

    ItemType newItem(name, address, phoneNumber);
    bool added = clientTree.PutItem(newItem);
    if (added)
    {
        cout << "Client added successfully." << endl;
    }
    else
    {
        cout << "Failed to add client. Item already exist." << endl;
    }
}

void deleteClient(BSTree& clientTree)
{
    string name;
    cout << "Enter client name to delete: ";
    getline(cin >> ws, name);

    ItemType itemToRetrieve(name, "", ""); // Creating an ItemType with only the name for retrieval
    bool found = false;
    ItemType retrievedItem = clientTree.GetItem(itemToRetrieve, found);
    
    if (!found)
    {
        cout << "Client not found." << endl;
    }
    else
    {
        cout << "Client found -> ";
        clientTree.DeleteItem(itemToRetrieve);
    }
}

// Function to retrieve a client from the BSTree
void retrieveClient(BSTree& clientTree)
{
    string name;
    cout << "Enter client name to retrieve: ";
    getline(cin >> ws, name);

    ItemType itemToRetrieve(name, "", ""); // Creating an ItemType with only the name for retrieval
    bool found = false;
    ItemType retrievedItem = clientTree.GetItem(itemToRetrieve, found);
    if (found)
    {
        cout << "Client found: " << retrievedItem.GetData() << endl;
    }
    else
    {
        cout << "Client not found." << endl;
    }
}


void runMenu(BSTree& clientTree)
{
    int choice = 0;
    while (choice != 7)
    {
        choice = 0;
        while (!cin || (choice < 1 || choice > 7))
        {
            cout << endl << "Client Data Search System" << endl << endl;
            cout << "Choose One:" << endl;
            cout << "1. Add a client." << endl;
            cout << "2. Delete a client" << endl;
            cout << "3. Retrieve a client" << endl;
            cout << "4. Print the data storage tree" << endl;
            cout << "5. Print the data storage tree in tree form" << endl;
            cout << "6. Write sorted data to file" << endl;
            cout << "7. Exit Menu" << endl;

            cout << "Enter your choice: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            // Add a client
            addClient(clientTree);
            break;
        case 2:
            // Delete a client
            deleteClient(clientTree);
            break;
        case 3:
            // Retrieve a client
            retrieveClient(clientTree);
            break;
        case 4:
            //print tree
            clientTree.PrintTree();
            break;
        case 5:
            //print tree fform
            clientTree.PrintTreeForm();
            break;
        case 6:
            //print BST to csv file
            clientTree.PrintToCSV();
            break;
        case 7:
            cout << "Bye! Don’t let the door hit you..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
    }
}
