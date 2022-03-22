
typedef struct AVLNode* Tree;
typedef int ElemType;

struct AVLNode {
	ElemType val;
	Tree parent;
	Tree lchild;
	Tree rchild;
	int depth;

	AVLNode(int val = 0) {
		this->val = val;
		parent = nullptr;
		lchild = rchild = nullptr;
		depth = 0;
	}
};


//Tree LL_rotate(Tree node)
//{
//	// node为离操作结点最近的失衡的结点
//	Tree parent = nullptr, son;
//	// 获取失衡结点的父节点
//	parent = node->parent;
//	// 获取失衡结点的左孩子
//	son = node->lchild;
//	// 设置son结点右孩子的父指针
//	if (son->rchild != nullptr) son->rchild->parent = node;
//
//	// 失衡结点的左孩子变更为son的右孩子
//	node->lchild = son->rchild;
//
//	// 失衡点变成son的右孩子
//	son->rchild = node;
//
//	// 设置son的父节点为原失衡点的父结点
//	son->parent = parent;
//
//
//
//
//}