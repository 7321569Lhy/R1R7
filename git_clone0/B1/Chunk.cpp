#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define CHUNKSIZE 80
typedef unsigned char Sstring[256];//定长顺序存储，[0]位存放串长
typedef struct {
	char ch[CHUNKSIZE];
	int length;
}SString;
typedef struct {
	char* ch;
	int length;
}HString;//堆分配存储
typedef struct Chunk {//节点结构
	char ch[80];
	Chunk* next;
}Chunk;
typedef struct {//串的链表结构
	Chunk* head, * tail;
	int curlen;
}LString;
int Index(Sstring S, Sstring L, int pos)
{
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= L[0]) {
		if (S[i] == L[j]) {
			++i;
			++j;
		}//按位对比，相等则继续后移
		else {
			i = i - j + 2;
			j = 1;
		}//对比不相等，主串指针后移，模式串回到起点
	}
		if (j > L[0]) return i - L[0];
		else return 0;
}//在主串第pos位开始寻找与模式串L相等的字串位置，实际应用的是朴素模式匹配

//效率更高的KMP算法
int Index_KMP(SString S, SString T, int next[]) {
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length) {
		if (j == 0 || S.ch[i] == T.ch[j]) {
			i++;
			j++;
		}
		else j = next[j];
	}
	if (j > T.length) return i-T.length;
	else return 0;
}
//计算next[]数组的实现
void get_next(SString T, int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T. length) {
		if (j == 0 || T.ch[i] == T.ch[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else j = next[j];
	}
}