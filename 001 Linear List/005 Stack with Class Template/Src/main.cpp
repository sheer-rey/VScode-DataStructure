#include <iostream>
#include "sequential_stack.hpp"
#include "linked_stack.hpp"
using namespace std;
using namespace libofsheerrey;

int main()
{
    {
        LinkedStack<int> stack_int{1, 2, 3, 4, 5, 6};
        LinkedStack<int> stack_int2;
        cout << stack_int << stack_int2 << endl;
        stack_int2 = stack_int;
        cout << stack_int << stack_int2 << endl;
        int element;
        stack_int.Push(66);
        stack_int2.Pop(element);
        cout << stack_int << stack_int2 << endl;
        cout << element << endl;
        stack_int.Clear();
        cout << stack_int << stack_int2 << endl;
    }
    cout << "exit" << endl;
    return 0;
}