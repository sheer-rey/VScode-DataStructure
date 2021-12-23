#include <iostream>
#include "sequential_stack.hpp"
using namespace std;
using namespace libofsheerrey;

int main()
{
    Stack<int> stack_int{1, 2, 3, 4, 5, 6};
    Stack<int> stack_int2 = stack_int;
    int element;
    cout << stack_int << stack_int2 << endl;
    stack_int.Push(66);
    stack_int2.Pop(element);
    cout << stack_int << stack_int2 << endl;
    cout << element << endl;
    stack_int.ShrinktoFit();
    stack_int2.Clear();
    cout << stack_int << stack_int2 << endl;
    return 0;
}