// main.cpp
#include "InventoryManager.h"
#include <iostream>
using namespace std;

int main() {
    // Create an InventoryManager with a maximum of n items
    InventoryManager* carList = new InventoryManager(4);

    // Create ItemType objects for testing
    ItemType* item1 = new ItemType("BA 1965 Mustang GT Fastback", 48383829922);
    ItemType* item2 = new ItemType("BB 1970 Camaro SS", 987654321);
    ItemType* item3 = new ItemType("BC 2022 Tesla Model 3", 555555555);
    ItemType* item4 = new ItemType("BA 1965 Mustang GT Fastback", 48383829922);

    // Test PutItem
    carList->PutItem(item1);  // Should add item1
    carList->PutItem(item2);  // Should add item2
    carList->PutItem(item3);  // Should add item3
    carList->PutItem(item4);

    // Test PrintList
    cout << "\nInventory List:" << endl;
    carList->PrintList();

    // Test DeleteItem
    cout << "\nDeleted Items:" << endl;
    carList->DeleteItem(item1);  
    carList->DeleteItem(item3);  

    // Test PrintList after deletion
    cout << "\nInventory List after deletion:" << endl;
    carList->PrintList();


    // Clean up memory
    delete carList;
    carList = nullptr;

    // Clean up
    delete carList;
    carList = NULL;

   
    return 0;
}
