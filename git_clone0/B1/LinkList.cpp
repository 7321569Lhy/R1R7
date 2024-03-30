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
}//建立一个带头节点的空链表
int ListEmpty(LinkList L) {
	if (L->next == NULL)
		return true;
	else
		return false;
}//判断链表是否为空
void ListRevise(LinkList& L, int n, int e) {
	LinkList p;
	p = L;
	int j = 0;
	while (p && j < n) {
		p = p->next;
		j++;
	}
	p->data = e;
}//修改第n个节点的数据为e
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
}//在第n个节点之后插入数据为e的节点
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
}//删除链表中第n个节点
int ListLength(LinkList L) {
	LinkList p = L->next;//头节点不算在链表长度中
	int count = 0;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}//计算链表长度
void ClearList(LinkList& L) {
	LinkList p;
	while (L->next) {
		p = L->next;
		L->next = p->next;
		free(p);
	}
}//清空链表
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
}//获取链表中第n个节点的数据
void GetList(LinkList& L) {
	LinkList p = L;
	while (p->next) {
		p = p->next;
		printf("%d\n", p->data);
	}
}//打印出链表中所有数据
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
