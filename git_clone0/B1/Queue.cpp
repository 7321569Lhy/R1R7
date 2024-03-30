#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct QNode {
	int data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;//��ͷָ��
	QueuePtr rear; //��βָ��
}LinkQueue;
void InitQueue(LinkQueue Q) {
	Q.front = Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)exit(0);
	Q.front->next = NULL;
}
void EnQueue(LinkQueue Q, int e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)exit(0);
	p->next = NULL;
	p->data = e;
	Q.rear->next = p;
	Q.rear = p;
}//��β����Ԫ�أ����
void DeQueue(LinkQueue Q, int& e) {
	if (Q.front == Q.rear)exit(0);
	else {
		QueuePtr q = (QueuePtr)malloc(sizeof(QNode));
		q = Q.front->next;
		Q.front->next = q->next;
		e = q->data;
		if (Q.rear == q)Q.rear = Q.front;
		free(q);
	}
}//��ͷɾ��Ԫ�أ����ӣ�