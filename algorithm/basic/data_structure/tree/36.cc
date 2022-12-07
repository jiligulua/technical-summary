#include <iostream>
#include "tree.h"

using std::cout;
using std::cin;
using std::endl;

BinaryTreeNode *pre = nullptr;

void Convert(BinaryTreeNode* pNode) {
  if (pNode == nullptr)
    return;

  Convert(pNode->left);
  pNode->left = pre;

  if (pre!=nullptr) 
    pre->right = pNode;

  pre = pNode;
  Convert(pNode->right);
}

int main() {

  BinaryTreeNode *root;
  CreateTree(&root);
  
  cout << "In Order: ";
  InOrderTraverse(root);
  cout << endl;

  Convert(root);

  while (pre->left != nullptr)
    pre = pre->left;

  while (pre != nullptr) {
    cout << pre->value << " " << endl;
    pre = pre->right;
  }

  cout << endl;

  return 1;
}
