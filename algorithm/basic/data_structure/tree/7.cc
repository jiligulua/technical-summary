#include <iostream>
#include <exception>
#include "tree.h"

using namespace std;


unsigned GetIndexAtInOrder(int *in, unsigned len, int root) {
  for (unsigned index = 0; index < len; ++index) {
    if (*(in+index) == root)
	  return index;
  }
  throw std::invalid_argument("Invalid input");
}

BinaryTreeNode * Rebuild(int *pre, int *in, unsigned len) {
  if (pre == nullptr || in == nullptr || len == 0) return nullptr;
  
  if (len == 1) {
    BinaryTreeNode *p = new BinaryTreeNode;
	p->value = *pre;
	p->left = nullptr;
	p->right = nullptr;
	return p;
  }

  BinaryTreeNode *root = new BinaryTreeNode;
  root->value = *pre;
  unsigned index = GetIndexAtInOrder(in, len, *pre);
  if (index == 0)
    root->right= Rebuild(pre+1, in+1, len-1);
  else if (index == len-1)
    root->left = Rebuild(pre+1, in, len-1);
  else {
    root->left = Rebuild(pre+1, in, index);
	root->right = Rebuild(pre+index+1, in+index+1, len-1-index);
  }

  return root;
}


int main() {
  int pre[] = {1, 2, 4, 7, 3, 5, 6, 8};
  int in[] = {4, 7, 2, 1, 5, 3, 8, 6};

  BinaryTreeNode * root = Rebuild(pre, in, 8);
  PostOrderTraverse(root);

  return 1;  
}
