#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW 0
#define ERROR 0

typedef struct {
	int* elem;
	int length;//实际长度
	int listsize;//已分配内存的长度
}SqList;
void InitList_Sq(SqList& L) {
	L.elem = (int*)sizeof(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
int ListLength(SqList L) {
	return L.length;
}
void PriorElem(SqList& L, int cur_e, int& pre_e) {
	if (cur_e <= 0 || L.length == 0 || cur_e > L.length)
		exit(ERROR);
	else {
		pre_e = L.elem[cur_e - 1];
	}
}
void ListInsert_Sq(SqList& L, int i, int e) {
	int *q = &(L.elem[i - 1]);
	int* p;
	for (p = (&L.elem[L.length - 1]); p >= q; p--) {
		*(p + 1) = *p;
		*q = e;
		L.length++;
	}
}
void ListDelete_Sq(SqList& L, int i, int& e) {
	int* p = &L.elem[i - 1];
	e = *p;
	int* q = L.elem + L.length - 1;
	for (p; p <= q; p++) {
		*p = *(p + 1);
		L.length--;
	}
}