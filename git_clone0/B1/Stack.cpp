#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define OVERFLOW 0
#define STACKINCREMENT 10
#define STACK_INIT_SIZE 100
typedef struct {
	int* base;//基地址
	int* top;//栈顶地址
	int stacksize;//栈容量
} SqStack;
void InitStack(SqStack& S) {
	S.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}//创建一个指定容量的空栈
void PushStack(SqStack& S, int e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (int*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(int));
		if (!S.base)exit(0);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
}//数据入栈
void PopStack(SqStack& S,int &e) {
	if (S.top == S.base)exit(0);
	else {
		e = *(S.top - 1);
		S.top--;
	}
}//出栈，记录前一位数据