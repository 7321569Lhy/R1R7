#include<stdio.h>
#include<stdlib.h>

//顺序表查找实现（借助哨兵）
typedef struct {
	char* elem;//基地址
	int TableLen;//表的长度
}SSTable;//表中元素最小下标为1
int Search_Seq(SSTable ST, char key) {
	ST.elem[0] = key;//设置哨兵
	int i;
	for (i = ST.TableLen; ST.elem[i] != key; i--);
	return i;
}

//折半查找,应用条件为查找表必须按一定顺序排列，此处按升序排列编写
int Binary_Search(SSTable ST, char key) {
	int low = 0;
	int high = ST.TableLen - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (ST.elem[mid] == key) return mid;
		else if (ST.elem[mid] > key) {
			high = mid - 1;
		}
		else if (ST.elem[mid] < key) {
			low = mid + 1;
		}
	}
	return -1;
}

typedef struct BSTNode {
	int key;
	struct BSTNode* rchild, * lchild;
}BSTNode,*BSTree;//二叉排序树，左子树<根节点<右子树，使用中序遍历可得到递增序列
BSTNode* BST_Search(BSTree T, int key) {
	while (T && key != T->key) {
		if (key < T->key)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}
//在二叉排序树中插入节点
int BST_Insert(BSTree& T, int k) {
	if (T == NULL) {
		T = (BSTNode*)malloc(sizeof(BSTNode));
		T->key = k;
		T->lchild = T->rchild = NULL;
		return 1;
	}
	else if (k == T->key)//不能插入新的重复节点
		return 0;
	else if (k < T->key) {
		return BST_Insert(T->lchild, k);
	}
	else {
		return BST_Insert(T->rchild, k);
	}
}
//根据给定数组构建二叉排序树
void Creat_BST(BSTree& T, int str[],int n) {
	T = NULL;
	int i = 0;
	while (i < n) {
		BST_Insert(T, str[i]);
		i++;
	}
}
//对二叉树的节点进行删除
int BST_Delete(BSTree& T, int key) {
	if (!T) return 0;//空树无法删除
	else if (T->key == key)
		return Delete(T);
	else if (T->key > key)
		return BST_Delete(T->lchild, key);
	else
		return BST_Delete(T->rchild, key);
}

bool Delete(BSTree& p) {
	BSTree q, s;
	if (!p->rchild) {//p为叶子节点或只有左子树
		q = p;
		p = p->lchild;
		free(q);
	}
	else if (!p->lchild) {//p为叶子节点或只有右子树
		q = p;
		p = p->rchild;
		free(q);
	}
	else {//p既有左子树又有右子树
		q = p;
		s = p->lchild;
		while (s->rchild) {
			q = s;//q指向s的双亲
			s = s->rchild;
		}
		p->key = s->key;
		if (q != p) {//进入while循环
			q->rchild = s->lchild;
		}
		else //未进入while循环
			q->lchild = s->lchild;
		free(s);
	}
	return true;
}


typedef struct AVLNode {
	int key;
	int balance;//平衡因子，只能为1或0或-1
	struct AVLNode* lchild, * rchild;
}AVLNode,*AVLTree;  //平衡二叉树结点

