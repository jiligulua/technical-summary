#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <stack>
#include <queue>
#include "common.h"

using std::string;
using std::vector;
using std::array;
using std::cout;
using std::endl;
using std::stack;
using std::queue;

struct BinaryTreeNode {
  int value;
  BinaryTreeNode* left;
  BinaryTreeNode* right;
};

// 27: 二叉树的镜像
void BinaryMirror(BinaryTreeNode* root) {
  if (nullptr == root)
	return;

  if (root->left == nullptr && root->right == nullptr)
	return;

  BinaryTreeNode* ptemp = root->left;
  root->left = root->right;
  root->right = ptemp;

  if (root->left != nullptr) 
	BinaryMirror(root->left);

  if (root->right != nullptr)
	BinaryMirror(root->right);
}

void BinaryMirrorLoop(BinaryTreeNode* root) {
  stack<BinaryTreeNode*> s;
  s.push(root);

  while (!s.empty()) {
    auto cur = s.top();
	s.pop();

	if (cur == nullptr)
	  continue;

	if (cur->left == nullptr && cur->right == nullptr)
	  continue;

	auto temp = cur->left;
	cur->left = cur->right;
	cur->right = temp;

	s.push(cur->left);
	s.push(cur->right);
  }
}

// 28:对称的二叉树
bool IsSymmetrical(BinaryTreeNode* left, BinaryTreeNode* right); 
bool IsSymmetrical(BinaryTreeNode* root) {
  return IsSymmetrical(root, root);
}

bool IsSymmetrical(BinaryTreeNode* left, BinaryTreeNode* right) {
  if (left == nullptr && right == nullptr)
	return true;

  if (left == nullptr || right == nullptr)
	return false;

  return IsSymmetrical(left->left, right->right) && 
		 IsSymmetrical(left->right, right->left);
} 

bool IsSymmetricalByLoop(BinaryTreeNode* root) {
  if (root == nullptr)
    return true;

  stack<BinaryTreeNode*> s1;
  stack<BinaryTreeNode*> s2;
  s1.push(root);
  s2.push(root);

  while (!s1.empty() && !s2.empty()) {
    auto root1 = s1.top();
	auto root2 = s2.top();
	s1.pop();
	s2.pop();
	if (root1->left == root2->right &&
		root1->right == root2->left) {
	  s1.push(root1->right);
	  s1.push(root1->left);
	  s2.push(root2->left);
	  s2.push(root2->right);
	} else {
	  return false;
	}
  }

  return true;
}

// 29.顺时针打印矩阵
// 38.字符串的排列
void Permutation(char* pStr, char* pBegin);
void Permutation(char* pStr) {
  if (nullptr == pStr) 
	return;

  Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin) {
  if (*pBegin == '\0') {
    printf("%s\n", pStr);
  } else {
    for (char* pCh = pBegin; *pCh != '\0'; ++pCh) {
	  char temp = *pCh;
	  *pCh = *pBegin;
	  *pBegin = temp;

	  Permutation(pStr, pBegin+1);

	  // 恢复原来的序列，为下个字符的顺序做好准备
	  temp = *pCh;
	  *pCh = *pBegin;
	  *pBegin = temp;
	}
  }
}

int main() {
  vector<int> ivec {1,2,3,6,76,43,23,12,4};
  std::make_heap(ivec.begin(), ivec.end(), [](int l, int r) { return l < r;});

  Print(ivec);
  cout << endl;
  std::pop_heap(ivec.begin(), ivec.end());
  ivec.pop_back();
  Print(ivec);
  cout << endl;

  char pcz[] = "abcd";
  Permutation(pcz);
}
