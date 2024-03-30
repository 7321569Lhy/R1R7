#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define OK 1;
#define ERROR 0;
typedef int SqBiTree[100];//��������˳��洢��ʾ��0��λ�ô�������
int static i = 0;

//����������ʽ�洢��ʾ
typedef struct BiTNode {
	char data;
	BiTNode* lchild, * rchild;//���Һ���ָ��
}BiTNode,*BiTree;

//˫������
typedef struct BPTNode {
	int data;
	struct BPTNode* parent;//˫��ָ��
	char LRTag;//���Һ��ӱ�־��
}BPTNode;//���ṹ
typedef struct BPTree {
	BPTNode nodes[100];
	int num_node;
	int root;
}BPTree;//���ṹ

void CreatBiTree(BiTree& T) {
	char ch;
	scanf("%c", &ch);
	if (ch == ' ')T = NULL;
	else {
		if (!(T = (BiTree)malloc(sizeof(BiTNode))))exit(0);
		T->data = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}//����������

//��򵥵�Visit����
bool PrintElement(char e) {
	printf("%c",e);
	return 1;
}//�����ÿ������Ӧ����

int PreOrderTraverse(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit)) return 1;
		return 0;
	}
	else return 1;//��ʱ��ȫ������
}//�������(�ݹ�)

int InOrderTraverse1(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (InOrderTraverse1(T->lchild, Visit))
			if (Visit(T->data))
				if (InOrderTraverse1(T->rchild, Visit)) return OK;
		return ERROR;
	}
	else return OK;
}//�������

int PostOrderTraverse(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (PostOrderTraverse(T->lchild, Visit))
			if (PostOrderTraverse(T->rchild, Visit))
				if (Visit(T->data)) return OK;
		return ERROR;
	}
	else return OK;
}

//��α�������������У���
typedef struct QNode {
	BiTree data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;//��ͷָ��
	QueuePtr rear; //��βָ��
}LinkQueue;
void InitQueue(LinkQueue Q) {
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)exit(0);
	Q.front->next = NULL;
}
void EnQueue(LinkQueue Q, BiTree e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)exit(0);
	p->next = NULL;
	p->data = e;
	Q.rear->next = p;
	Q.rear = p;
}//��β����Ԫ�أ����
void DeQueue(LinkQueue Q, BiTree& e) {
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
bool QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear) return true;
	else return false;
}//�ж϶����Ƿ�Ϊ��
void LevelOrder(BiTree T) {
	LinkQueue Q;
	InitQueue(Q);
	BiTree p;
	EnQueue(Q, T);
	while (!QueueEmpty(Q)) {
		DeQueue(Q, p);
		printf("%c\n", p->data);
		if (p->lchild != NULL)
			EnQueue(Q, p->lchild);
		if (p->rchild != NULL)
			EnQueue(Q, p->rchild);
	}
}

//����Ϊ�ǵݹ�������������������������ջ����
typedef struct SNode {
	BiTree data;
	struct SNode* next;
}SNode,* LinkStack;
void InitStack(LinkStack& S) {
	S = (LinkStack)malloc(sizeof(SNode));
	S->next = NULL;
}//��ʼ��ջ
void Push(LinkStack& S, BiTree e) {
	LinkStack p = (LinkStack)malloc(sizeof(SNode));
	e=p->data;
	p->next = S->next;
	S->next = p;
}//��ջ����
void Pop(LinkStack& S, BiTree& e) {
	LinkStack q = (LinkStack)malloc(sizeof(SNode));
	q = S->next;
	e = q->data;
	S->next = q->next;
	free(q);
}//��ջ����
bool StackEmpty(LinkStack S) {
	if (S->next == NULL)return 1;
	else return 0;
}//�ж�ջ�Ƿ�Ϊ��
BiTree GetTop(LinkStack S, BiTree& e) {
	if (S->next == NULL)return 0;
	else {
		e = S->next->data;
		return e;
	}
}//ȡջ��Ԫ��
void Push0(BiTree S[], BiTree e) {
	S[i] = e;
	i++;
}
void Pop0(BiTree S[], BiTree& e) {
	e = S[--i];
	S[i] = NULL;
}
int InOrderTraverse2(BiTree T, bool(*Visit)(char e)) {
	BiTree S[100];
	BiTree p = T;
	BiTree q;
	while (p || S[0]) {
		if (p) { Push0(S, p); p = p->lchild; }
		else {
			Pop0(S, q);
			printf("%c", q->data);
			p = q->rchild;
		}
	}
	return OK;
}//�ǵݹ��������,�����������ģ��ջ��������ջ�޷��洢BiTreeָ��

void CountLeaf(BiTree T, int& count) {
	if (T) {
		if ((!T->lchild) && (!T->rchild)) {
			count++;
		}
		CountLeaf(T->lchild, count);
		CountLeaf(T->rchild, count);
	}
}//�ݹ���Ҷ�ӽڵ���

int Depth(BiTree T) {
	int depthval;
	if (!T)depthval=0;
	else {
		int depthleft=Depth(T->lchild);
		int depthright=Depth(T->rchild);
		depthval = (depthleft > depthright ? depthleft : depthright) + 1;
	}
	return depthval;
}//�ݹ����������

BiTNode* GetTreeNode(char item, BiTree lptr, BiTree rptr) {
	BiTree T;
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		exit(1);
	T->data = item;
	T->lchild = lptr;
	T->rchild = rptr;
	return T;
}//���ƽڵ�������Ǹ��ƶ������Ĺؼ�
BiTNode* CopyTree(BiTree T) {
	BiTree newlptr, newrptr;
	if (!T) return NULL;
	if (T->lchild)
		 newlptr = CopyTree(T->lchild);
	else newlptr = NULL;//����������
	if (T->rchild)
		 newrptr = CopyTree(T->rchild);
	else newrptr = NULL;//����������
	BiTree newT = GetTreeNode(T->data, newlptr, newrptr);
	return newT;
}//���ø��ƽڵ㷽�����ݹ���ɸ��ƶ�����

//����׺ʽ������������֪�����������н�������α���?

typedef enum{Link,Thread}PointerThr;
//Link==0��ʾָ�룬Thread==1��ʾ����
typedef struct BiThrNode {
	char data;
	BiThrNode* lchild, *rchild;
	PointerThr LTag, RTag;
}BiThrNode,*BiThrTree;//�������������

BiThrTree pre;

void InThreading(BiThrTree p) {
	if (p) {
		InThreading(p->lchild);
		if (!p->lchild) {
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}

void InOrderThreading1(BiThrTree T){}
void InOrderThreading2(BiThrTree& Thrt, BiThrTree T) { //ThrΪͷ�ڵ�
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(0);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		BiThrTree pre = Thrt;
		InThreading(T);
		pre->RTag = Thread;
		pre->rchild = Thrt;
		Thrt->rchild = pre;
	}
}

void InOrderTraverse_Thr(BiThrTree T, bool(*Visit)(char e)) {
	BiThrTree p = T->lchild;
	while (p != T) {
		while (p->LTag == Link)p = p->lchild;
		if (!Visit(p->data)) printf("����");
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild; Visit(p->data);
		}
		p = p->rchild;
	}
}//���ڸ������������������������

//˫�ױ�ʾ����˳���
typedef struct {
	char data;
	int parent;//˫��λ����
}PTnode;
typedef struct {
	PTnode nodes[100];
	int n;//�ڵ����
}PTree;

//���ӱ�ʾ��
struct CTNode {
	int child; //�����������е�λ��
	struct CTNode* next;//��һ������
};
typedef struct {
	char data;
	struct CTNode* firstChild;
}CTBox;
typedef struct {
	CTBox nodes[100];
	int n, r;//�ڵ����͸���λ��
}CTree;

//���ӡ����ֵܱ�ʾ��
typedef struct CSNode{
	char data;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;

/*�����ȸ����������巽��Ҫ�����Ĵ洢��ʽ����
void PreOrder(TreeNode* R) {
	if (R != NULL) {
	visit(R);
	while (R��������T)
		PreOrder(T);
    }
  ���������while��visit����λ�ü��� */


//���鼯,��˫�ױ�ʾ����ʾ
#define SIZE 100
int UFSets[SIZE];
//��ʼ�����鼯
void Initial(int S[]) {
	for (int i=0; i < SIZE; i++) {
		S[i] = -1;
	}
}
//���顱������xΪ������Ԫ�ص��±꣬S[x]Ϊ�丸���±�
int Find1(int S[], int x) {
	while (S[x] >= 0)
		x = S[x];
	return x;
}
//Find���Ż��㷨��ͨ����ѹ��·��������ʱ�临�Ӷ�
int Find2(int S[], int x) {
	int root = x;
	while (S[root] >= 0)
		root = S[root];
	while (x != root) {
		int t = S[x];
		S[x] = root;
		x = t;
	}
	return root;
}

//��������������root2��Ϊroot1������
void Union1(int S[], int root1, int root2) {
	if (root1 == root2)
		return;//�ϲ������������벻ͬ
	else {
		S[root2] = root1;
	}
}
//Union���Ż��㷨��ȷ��С����Ϊ�������������Ӷ�����ϲ�������߶����ӣ������ڿ���ʱ�临�Ӷ�
//����ʱ���ĸ��ڵ㲻�ܽ�Ϊ-1��Ӧ��Ϊ-n��nΪ�ܽڵ�����,���ָ�����Ϊ�˷������
void Union2(int S[], int root1, int root2) {
	if (root1 == root2)
		return;
	else if (S[root1] > S[root2]) {//root1�Ľڵ�������
		S[root2] += S[root1];//���ºϲ����root2�����ܽڵ���
		S[root1] = root2;
	}
	else if (S[root1] < S[root2]) {//root2�Ľڵ�������
		S[root1] += S[root2];
		S[root2] = root1;
	}
}

 
int main() {
	BiTree T;
	CreatBiTree(T);
	int count;
	CountLeaf(T, count);
	printf("%d\n", count);
	InOrderTraverse2(T,PrintElement);
}