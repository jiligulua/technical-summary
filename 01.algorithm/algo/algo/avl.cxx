
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
//	// nodeΪ�������������ʧ��Ľ��
//	Tree parent = nullptr, son;
//	// ��ȡʧ����ĸ��ڵ�
//	parent = node->parent;
//	// ��ȡʧ���������
//	son = node->lchild;
//	// ����son����Һ��ӵĸ�ָ��
//	if (son->rchild != nullptr) son->rchild->parent = node;
//
//	// ʧ��������ӱ��Ϊson���Һ���
//	node->lchild = son->rchild;
//
//	// ʧ�����son���Һ���
//	son->rchild = node;
//
//	// ����son�ĸ��ڵ�Ϊԭʧ���ĸ����
//	son->parent = parent;
//
//
//
//
//}