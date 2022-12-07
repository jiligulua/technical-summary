#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;
using std::string;

struct BinaryTreeNode {
  int value;
  BinaryTreeNode *left;
  BinaryTreeNode *right;
};

void PreOrderTraverse(BinaryTreeNode * root) {
  if (root == nullptr) return;

  cout << (root->value) << " ";
  PreOrderTraverse(root->left);
  PreOrderTraverse(root->right);
}

void InOrderTraverse(BinaryTreeNode * root) {
  if (root == nullptr) return;

  InOrderTraverse(root->left);
  cout << (root->value) << " ";
  InOrderTraverse(root->right);
}

void PostOrderTraverse(BinaryTreeNode * root) {
  if (root == nullptr) return;

  PostOrderTraverse(root->left);
  PostOrderTraverse(root->right);
  cout << (root->value) << " ";
}

void CreateTree(BinaryTreeNode** root) {
  string c;
  if (cin >> c) {
	if (c == "#" ) {
	  *root = nullptr;
	  return;
	}
    *root = new BinaryTreeNode();
	(*root)->value = std::stoi(c, nullptr, 10); 
	CreateTree(&(*root)->left);
	CreateTree(&(*root)->right);
  } 
}

BinaryTreeNode* CreateTree(void) {
  char c;
  if (cin >> c) {
    if (c == '#')
	  return nullptr;

	BinaryTreeNode *p = new BinaryTreeNode();
	p->value = c;
	p->left = CreateTree();
	p->right = CreateTree();
	return p;
  }
  return nullptr;
}

#endif
