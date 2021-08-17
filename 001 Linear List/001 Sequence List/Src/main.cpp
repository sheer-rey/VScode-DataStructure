#include <iostream>
#include "SQList.h"
using namespace std;

int main()
{
    int iReturnValue, iElement, iLocation, iListLenth;

    /* List Initialization */
    sqList *L = new sqList;
    SQList_Init(L, 5);
    SQList_print_all(L);

    /* Is List Empty? */
    if (SQList_IfEmpty(L) == sqTRUE)
        cout << "List is empty!" << endl;

    /* Insert element into List */
    for (int i = 0; i < L->sqMaxSize; i++)
    {
        cout << "Please enter a number insert into List: ";
        cin >> iElement;
        cout << "Please enter the location where the number insert into: ";
        (cin >> iLocation).get();
        iReturnValue = SQList_InsertElement(L, iLocation, iElement);
        switch (iReturnValue)
        {
        case sqOK:
            cout << "List insert element OK!" << endl;
            break;
        case sqERROR:
            cout << strSQErrorMessage[sqERROR] << endl;
            break;
        case sqOVERFLOW:
            cout << strSQErrorMessage[sqOVERFLOW] << endl;
            break;
        }
        SQList_print(L);
    }

    /* Delete element from List */
    cout << "Please enter the location where the element is going to be deleted: ";
    (cin >> iLocation).get();
    iReturnValue = SQList_DeleteElement(L, iLocation, &iElement);
    switch (iReturnValue)
    {
    case sqOK:
        cout << "List delete element OK!" << endl;
        break;
    case sqERROR:
        cout << strSQErrorMessage[sqERROR] << endl;
        break;
    }
    SQList_print(L);

    /* Get lenth of List */
    if (SQList_GetLenth(L, &iListLenth) == sqOK)
        cout << "Current lenth of List is: " << iListLenth << endl;

    /* Get element of List */
    cout << "Please enter a location: ";
    (cin >> iLocation).get();
    iReturnValue = SQList_GetElement(L, iLocation, &iElement);
    switch (iReturnValue)
    {
    case sqOK:
        cout << "The element of List in location " << iLocation << " is: " << iElement << endl;
        break;
    case sqERROR:
        cout << strSQErrorMessage[sqERROR] << endl;
        break;
    }

    /* Locate elemrnt of List */
    cout << "Please enter the element to locate: ";
    (cin >> iElement).get();
    iReturnValue = SQList_LocateElement(L, &iLocation, iElement);
    switch (iReturnValue)
    {
    case sqOK:
        cout << "The element " << iElement << " is locatedd in " << iLocation << " of List." << endl;
        break;
    case sqFALSE:
        cout << "There's no element " << iElement << " in List." << endl;
        break;
    case sqCONFLICT:
        cout << strSQErrorMessage[sqCONFLICT] << "\nThe first element " << iElement << " is located in " << iLocation << " of List." << endl;
    }

    /* Clear List */
    if (SQList_Clear(L) == sqOK)
        cout << "List clear OK!" << endl;
    if (SQList_GetLenth(L, &iListLenth) == sqOK)
        cout << "Current lenth of List is: " << iListLenth << endl;

    /* Delete List */
    if (SQList_Delete(L) == sqOK)
    {
        delete L;
        cout << "List delete OK!" << endl;
    }
    return 0;
}