#include <iostream>
#include "new_handler_support.h"


using std::cout;
using std::endl;
using std::cin;


void OutOfMemory() {
  cout << "Out of Memory" << endl;
}

typedef struct BiNode : public NewHandlerSupport<BiNode> {
  char data;
  BiNode *lChild;
  BiNode *rChild;
}BiNode, *BiTree;

void PreOrderTraverse(BiTree t) {
  if (t == nullptr)
    return;

  cout << t->data << " ";
  PreOrderTraverse(t->lChild);
  PreOrderTraverse(t->rChild);
}

void InOrderTraverse(BiTree t) {
  if (t == nullptr)
    return;

  InOrderTraverse(t->lChild);
  cout << t->data << " ";
  InOrderTraverse(t->rChild);
}

void PostOrderTraverse(BiTree t) {
  if (t == nullptr) 
    return;

  PostOrderTraverse(t->lChild);
  PostOrderTraverse(t->rChild);
  cout << t->data << " ";
}

void CreateTree(BiTree *t) {
  char c;
  if (cin >> c) {
    if (c == '#') {
	  *t = nullptr;
	} else {
      *t = new BiNode;
//	  (*t)->set_new_handler(OutOfMemory);
      (*t)->data = c;
      CreateTree(&(*t)->lChild);	  
      CreateTree(&(*t)->rChild);	  
	}
  }
}


int main() {
 BiTree t = nullptr;
 CreateTree(&t);
 cout << "PreOrder: ";
 PreOrderTraverse(t);
 cout << endl;

 cout << "InOrder: ";
 InOrderTraverse(t);
 cout << endl;

 cout << "PostOrder: ";
 PostOrderTraverse(t);
 cout << endl;
}
