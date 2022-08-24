#include <iostream>
#include "linked_queue.hpp"

using libofsheerrey::Queue;
using std::cin, std::cout, std::endl;

int main() {
  Queue<int> my_queue_1;
  Queue<int> my_queue_2(10, 10);
  Queue<int> my_queue_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Queue<int> my_queue_4(my_queue_2);
  Queue<int> my_queue_5(std::move(my_queue_2));
  my_queue_1 = my_queue_3;
  my_queue_2 = std::move(my_queue_4);
  my_queue_3.Push(10);
  my_queue_3.Push(11);
  my_queue_3.Push(12);

  int i;
  my_queue_3.Front(i);
  cout << my_queue_3.Front() << '\t' << i << endl;
  my_queue_3.Back(i);
  cout << my_queue_3.Back() << '\t' << i << endl;
  my_queue_3.Pop(i);
  cout << my_queue_3.Front() << '\t' << i << endl;
  cout << my_queue_3.QueueSize() << endl;
  while (my_queue_3.QueueSize()) {
    my_queue_3.Pop(i);
    cout << i << '\t';
  }
  cout << endl;
  my_queue_3.Pop();

  my_queue_1.Push(10);
  my_queue_1.Push(11);
  my_queue_1.Push(12);

  return 0;
}