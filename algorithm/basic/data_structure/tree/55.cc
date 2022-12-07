#include <iostream>
#include "tree.h"

unsigned GetBinaryTreeDepth(BinaryTreeNode *pNode) {
  if (pNode == nullptr)
    return 0;

  int depLeft = 1 + GetBinaryTreeDepth(pNode->left);
  int depRight = 1 + GetBinaryTreeDepth(pNode->right);
  
  return depLeft > depRight ? depLeft : depRight;
}

bool IsBalanceBinaryTree(BinaryTreeNode *pNode) {
  if (pNode == nullptr)
    return true;

  int left_depth = GetBinaryTreeDepth(pNode->left);
  int right_depth = GetBinaryTreeDepth(pNode->right);

  int gap = left_depth - right_depth;
  if (gap < -1 || 1 < gap)
    return false;

  return IsBalanceBinaryTree(pNode->left) && IsBalanceBinaryTree(pNode->right);
}

int main() {
  BinaryTreeNode *root;
  CreateTree(&root);
  
//  InOrderTraverse(root);
  
//  std::cout << "The binary tree depth is " << GetBinaryTreeDepth(root) << std::endl;
  std::cout << "Is balance binary tree ? " << (IsBalanceBinaryTree(root) ? "Y" : "N") << std::endl;
  return 1;
}

