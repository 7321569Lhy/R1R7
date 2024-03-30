#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define CHUNKSIZE 80
typedef unsigned char Sstring[256];//����˳��洢��[0]λ��Ŵ���
typedef struct {
	char ch[CHUNKSIZE];
	int length;
}SString;
typedef struct {
	char* ch;
	int length;
}HString;//�ѷ���洢
typedef struct Chunk {//�ڵ�ṹ
	char ch[80];
	Chunk* next;
}Chunk;
typedef struct {//��������ṹ
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
		}//��λ�Աȣ�������������
		else {
			i = i - j + 2;
			j = 1;
		}//�ԱȲ���ȣ�����ָ����ƣ�ģʽ���ص����
	}
		if (j > L[0]) return i - L[0];
		else return 0;
}//��������posλ��ʼѰ����ģʽ��L��ȵ��ִ�λ�ã�ʵ��Ӧ�õ�������ģʽƥ��

//Ч�ʸ��ߵ�KMP�㷨
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
//����next[]�����ʵ��
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