#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include "tree.h"

using std::queue;
using std::stack;
using std::cout;
using std::cin;
using std::endl;
using std::vector;



void PrintPath(const vector<int> v) {
  for (auto item : v)
    cout << item << " ";
  cout << endl;
}

void FindPath(BinaryTreeNode *root, int sum, int accumulate, vector<int> &s) {
  s.push_back(root->value);
  accumulate += root->value;
  
  if (root->left == nullptr && root->right == nullptr) { 
	  if (sum == accumulate)
	    PrintPath(s);
  }
  
  if (root->left != nullptr) 
    FindPath(root->left, sum, accumulate, s);

  if (root->right != nullptr) 
    FindPath(root->right, sum, accumulate, s);

  //accumulate -= root->value; // 这行代码不需要有，因为accumulate是值传递，每次的值有各自的stack保存，各不相同。
  s.pop_back();
}

int main() {
  BinaryTreeNode *root = nullptr;

  cout << "input sum: ";
  int sum;
  cin >> sum;
  cout << "Input Pre sequence: ";
  CreateTree(&root);
  //cout << "Pre: ";
  //PreOrderTraverse(root);
  //cout << endl;
  //cout << "In: ";
  //InOrderTraverse(root);
  //cout << endl;
  //cout << "Post: ";
  //PostOrderTraverse(root);
  //cout << endl;


  vector<int> v;
  if (root == nullptr)
	return 1;
  int accumulate = 0;
  cout << endl;


  FindPath(root, sum, accumulate, v);

  return 1;
}
