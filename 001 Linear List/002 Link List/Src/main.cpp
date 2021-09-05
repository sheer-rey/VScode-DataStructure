#include <iostream>
#include "LinkList.h"
using namespace std;

int main()
{
    int iReturnValue, iElement, iLocation, iListLenth;

    /* List Initialization */
    LinkList *L = new LinkList;
    LinkList_Init(L, 10);
    LinkList_print(L);

    /* Is List Empty? */
    if (LinkList_Empty(L) == llTRUE)
        cout << "List is empty!" << endl;
    else
        cout << "List is not empty!" << endl;

    /* Insert element into List (3 times) */
    for (int i = 0; i < 3; i++)
    {
        cout << "Please enter a number insert into List: ";
        cin >> iElement;
        cout << "Please enter the location where the number insert into: ";
        (cin >> iLocation).get();
        iReturnValue = LinkList_InsertElement(L, iLocation, iElement);
        switch (iReturnValue)
        {
        case llOK:
            cout << "List insert element OK!" << endl;
            break;
        case llERROR:
            cout << strSQErrorMessage[llERROR] << endl;
            break;
        }
        LinkList_print(L);
    }

    /* Delete element from List (3 times) */
    for (int i = 0; i < 3; i++)
    {
        cout << "Please enter the location where the element is going to be deleted: ";
        (cin >> iLocation).get();
        iReturnValue = LinkList_DeleteElement(L, iLocation, &iElement);
        switch (iReturnValue)
        {
        case llOK:
            cout << "List delete element OK!" << endl;
            break;
        case llERROR:
            cout << strSQErrorMessage[llERROR] << endl;
            break;
        }
        LinkList_print(L);
    }

    /* Get lenth of List */
    if (LinkList_GetLenth(L, &iListLenth) == llOK)
        cout << "Current lenth of List is: " << iListLenth << endl;

    /* Get element of List */
    cout << "Please enter a location: ";
    (cin >> iLocation).get();
    iReturnValue = LinkList_GetElement(L, iLocation, &iElement);
    switch (iReturnValue)
    {
    case llOK:
        cout << "The element of List in location " << iLocation << " is: " << iElement << endl;
        break;
    case llERROR:
        cout << strSQErrorMessage[llERROR] << endl;
        break;
    }

    /* Locate elemrnt of List */
    cout << "Please enter the element to locate: ";
    (cin >> iElement).get();
    iReturnValue = LinkList_LocateElement(L, &iLocation, iElement);
    switch (iReturnValue)
    {
    case llOK:
        cout << "The element " << iElement << " is locatedd in " << iLocation << " of List." << endl;
        break;
    case llFALSE:
        cout << "There's no element " << iElement << " in List." << endl;
        break;
    case llCONFLICT:
        cout << strSQErrorMessage[llCONFLICT] << "\nThe first element " << iElement << " is located in " << iLocation << " of List." << endl;
    }

    /* Clear List */
    if (LinkList_Clear(L) == llOK)
        cout << "List clear OK!" << endl;
    if (LinkList_Empty(L) == llTRUE)
        cout << "List is empty!" << endl;
    else
        cout << "List is not empty!" << endl;

    /* Delete List */
    if (LinkList_Delete(L) == llOK)
        cout << "List deleted OK!" << endl;
    return 0;
}