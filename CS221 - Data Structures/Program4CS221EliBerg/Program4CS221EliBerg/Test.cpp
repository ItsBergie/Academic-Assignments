#include "BSTree.h"
#include "ItemType.h"
#include <iostream>
using namespace std;

int main2() {
    BSTree tree;

    ItemType item1("John", "100", "200");
    ItemType item2("Jane", "101", "201");
    ItemType item3("Eli", "102", "202");
    ItemType item4("Tyrone", "103", "203");
    tree.PutItem(item1);
    tree.PutItem(item2);
    tree.PutItem(item3);
    tree.PutItem(item4);


    BSTree copy(tree);
    cout << endl;
    tree.PrintTree();
    cout << endl;
    copy.PrintTree();

    BSTree copy2 = tree;
    

    copy2.DeleteItem(item1);
    tree.PrintTree();
    cout << endl;
    copy.PrintTree();
    cout << endl;
    copy2.PrintTree();
    return 0;
    }