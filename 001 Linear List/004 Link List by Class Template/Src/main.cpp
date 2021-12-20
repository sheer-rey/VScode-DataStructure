#include <iostream>
#include "link_list.hpp"
using namespace std;
using namespace libofsheerrey;

int main()
{
    // test constructor
    LinkList<int> l1;
    LinkList<int> l2 = {1, 2, 3, 1, 5};
    LinkList<int> l3 = l2;

    // test operator=
    l1 = l2;

    // test operator<<
    cout << l1 << l2 << l3 << endl;

    // test Insert
    l1.Insert(6, 6);

    // test Delete
    int element;
    l2.Delete(4);
    l3.Delete(3, element);

    // output
    cout << l1 << l2 << l3 << endl;
    cout << element << endl;

    // test clear
    l1.Clear();

    // test GetElement
    l2.GetElement(3, element);

    // test GetLocation
    vector<unsigned> locations = l3.GetLocation(1);

    // output
    cout << l1 << l2 << l3 << endl;
    cout << element << endl;
    for (unsigned x : locations)
        cout << x << "\t";
    cout << endl;

    // test Replace
    l3.Replace(5, 0);
    cout << l3 << endl;

    // test IsEmpty
    cout << l2.IsEmpty() << endl;

    // test GetLenth
    cout << l3.GetLenth() << endl;

    return 0;
}