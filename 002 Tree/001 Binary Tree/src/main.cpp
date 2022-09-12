#include <iostream>
#include <string>
#include <vector>

#include "binary_tree.h"

using namespace std;
using namespace libofsheerrey;

int main() {
  vector<string> expanded_preorder{"3",    "9",    "null", "null", "20",  "15",
                                   "null", "null", "7",    "null", "null"};

  vector<int> preorder{3, 9, 20, 15, 7};
  vector<int> inorder{9, 3, 15, 20, 7};
  vector<int> postorder{9, 15, 7, 20, 3};

  BinaryTree tree1(expanded_preorder);
  BinaryTree tree2(inorder, preorder, BinaryTree::cPreorder);
  BinaryTree tree3(inorder, postorder, BinaryTree::cPostorder);
  BinaryTree tree4(tree1);

  vector<int> s = tree1.GetPreorderSequence();
  for (auto x : s) { cout << x << '\t'; }
  cout << endl;

  s = tree2.GetInorderSequence();
  for (auto x : s) { cout << x << '\t'; }
  cout << endl;

  s = tree3.GetPostorderSequence();
  for (auto x : s) { cout << x << '\t'; }
  cout << endl;

  s = tree4.GetLayerorderSequence();
  for (auto x : s) { cout << x << '\t'; }
  cout << endl;

  return 0;
}