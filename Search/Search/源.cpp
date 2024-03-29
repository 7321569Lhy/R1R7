#include<stdio.h>
#include<stdlib.h>

//˳������ʵ�֣������ڱ���
typedef struct {
	char* elem;//����ַ
	int TableLen;//��ĳ���
}SSTable;//����Ԫ����С�±�Ϊ1
int Search_Seq(SSTable ST, char key) {
	ST.elem[0] = key;//�����ڱ�
	int i;
	for (i = ST.TableLen; ST.elem[i] != key; i--);
	return i;
}

//�۰����,Ӧ������Ϊ���ұ���밴һ��˳�����У��˴����������б�д
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
}BSTNode,*BSTree;//������������������<���ڵ�<��������ʹ����������ɵõ���������
BSTNode* BST_Search(BSTree T, int key) {
	while (T && key != T->key) {
		if (key < T->key)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}
//�ڶ����������в���ڵ�
int BST_Insert(BSTree& T, int k) {
	if (T == NULL) {
		T = (BSTNode*)malloc(sizeof(BSTNode));
		T->key = k;
		T->lchild = T->rchild = NULL;
		return 1;
	}
	else if (k == T->key)//���ܲ����µ��ظ��ڵ�
		return 0;
	else if (k < T->key) {
		return BST_Insert(T->lchild, k);
	}
	else {
		return BST_Insert(T->rchild, k);
	}
}
//���ݸ������鹹������������
void Creat_BST(BSTree& T, int str[],int n) {
	T = NULL;
	int i = 0;
	while (i < n) {
		BST_Insert(T, str[i]);
		i++;
	}
}
//�Զ������Ľڵ����ɾ��
int BST_Delete(BSTree& T, int key) {
	if (!T) return 0;//�����޷�ɾ��
	else if (T->key == key)
		return Delete(T);
	else if (T->key > key)
		return BST_Delete(T->lchild, key);
	else
		return BST_Delete(T->rchild, key);
}

bool Delete(BSTree& p) {
	BSTree q, s;
	if (!p->rchild) {//pΪҶ�ӽڵ��ֻ��������
		q = p;
		p = p->lchild;
		free(q);
	}
	else if (!p->lchild) {//pΪҶ�ӽڵ��ֻ��������
		q = p;
		p = p->rchild;
		free(q);
	}
	else {//p��������������������
		q = p;
		s = p->lchild;
		while (s->rchild) {
			q = s;//qָ��s��˫��
			s = s->rchild;
		}
		p->key = s->key;
		if (q != p) {//����whileѭ��
			q->rchild = s->lchild;
		}
		else //δ����whileѭ��
			q->lchild = s->lchild;
		free(s);
	}
	return true;
}


typedef struct AVLNode {
	int key;
	int balance;//ƽ�����ӣ�ֻ��Ϊ1��0��-1
	struct AVLNode* lchild, * rchild;
}AVLNode,*AVLTree;  //ƽ����������

