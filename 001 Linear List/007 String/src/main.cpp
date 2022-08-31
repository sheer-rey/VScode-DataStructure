#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "kmp.h"

using namespace std;

int main() {
  cout << libofsheerrey::Search("aabaaabaaac", "aabaaac") << endl;
  return 0;
}