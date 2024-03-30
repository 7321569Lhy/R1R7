#include<stdio.h>
#include <malloc.h>
#include<ctype.h>
#define MAX_VALUE 1000;
typedef struct LNode {
	int data;
	struct LNode* next;
} LNode, * LinkList;
void InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
}//����һ����ͷ�ڵ�Ŀ�����
int ListEmpty(LinkList L) {
	if (L->next == NULL)
		return true;
	else
		return false;
}//�ж������Ƿ�Ϊ��
void ListRevise(LinkList& L, int n, int e) {
	LinkList p;
	p = L;
	int j = 0;
	while (p && j < n) {
		p = p->next;
		j++;
	}
	p->data = e;
}//�޸ĵ�n���ڵ������Ϊe
void ListInsert(LinkList& L, int n, int e) {
	LinkList p;
	p = L;
	int j = 0;
	while (p && j < n-1) {
		p = p->next;
		j++;
	}
	LinkList s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
}//�ڵ�n���ڵ�֮���������Ϊe�Ľڵ�
void ListDelete(LinkList& L, int n,int& e) {
	LinkList p;
	p = L;
	int j = 0;
	while (p && j < n - 1) {
		p = p->next;
		j++;
	}
	LinkList q;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
}//ɾ�������е�n���ڵ�
int ListLength(LinkList L) {
	LinkList p = L->next;//ͷ�ڵ㲻������������
	int count = 0;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}//����������
void ClearList(LinkList& L) {
	LinkList p;
	while (L->next) {
		p = L->next;
		L->next = p->next;
		free(p);
	}
}//�������
int GetList_Data(LinkList& L, int n) {
	LinkList p = L;
	int e;
	int j = 0;
	while (p && j < n) {
		p = p->next;
		j++;
	}
	e = p->data;
	return e;
}//��ȡ�����е�n���ڵ������
void GetList(LinkList& L) {
	LinkList p = L;
	while (p->next) {
		p = p->next;
		printf("%d\n", p->data);
	}
}//��ӡ����������������
int main() {
	LinkList L;
	InitList(L);
	/*bool a = ListEmpty;
	printf("%d\n", a);*/
	ListInsert(L, 1, 65);
	ListInsert(L, 2, 87);
	GetList(L);
	ListRevise(L, 2, 95);
	ListInsert(L, 3, 100);
	int e=GetList_Data(L, 3);
	printf("%d\n", e);
	GetList(L);
	int E;
	ListDelete(L, 1,E);
	printf("%d", E);
	GetList(L);
	ClearList(L);
	bool b = ListEmpty(L);
	printf("%d\n", b);
}//
