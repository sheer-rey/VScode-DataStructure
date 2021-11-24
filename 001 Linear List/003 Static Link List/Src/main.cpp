#include <iostream>
#include "static_link_list.h"
using namespace std;
using namespace staticlinklist;

int main()
{
    StaticLinkList list({1, 2, 3, 4, 5, 6, 7}, 10);
    cout << "-----------------------Init-----------------------\n"
         << list;
    // Add
    cout << "-----------------------Add-----------------------\n";
    cout << list.InsertElement(3, 1) << list.InsertElement(10, 1);
    cout << list.InsertElement(8, 1) << endl;
    cout << list;
    // Delete
    cout << "-----------------------Delete-----------------------\n";
    ElementType element;
    cout << list.DeleteElement(0) << list.DeleteElement(8, element) << element;
    cout << list;
    // query
    cout << "-----------------------Query-----------------------\n";
    cout << list.GetElement(3, element) << element << endl;
    for (auto i : list.GetLocation(1))
        cout << i << ' ';
    // Modify
    cout << "-----------------------Modify-----------------------\n";
    cout << list.ReplaceElement(1, 8) << list;
    // Clear
    cout << "-----------------------Clear-----------------------\n";
    list.ClearList();
    cout << list;
    return 0;
}