#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define OK 1;
#define ERROR 0;
typedef int SqBiTree[100];//二叉树的顺序存储表示，0号位置储存根结点
int static i = 0;

//二叉树的链式存储表示
typedef struct BiTNode {
	char data;
	BiTNode* lchild, * rchild;//左右孩子指针
}BiTNode,*BiTree;

//双亲链表
typedef struct BPTNode {
	int data;
	struct BPTNode* parent;//双亲指针
	char LRTag;//左右孩子标志域
}BPTNode;//结点结构
typedef struct BPTree {
	BPTNode nodes[100];
	int num_node;
	int root;
}BPTree;//树结构

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
}//建立二叉树

//最简单的Visit函数
bool PrintElement(char e) {
	printf("%c",e);
	return 1;
}//即输出每个结点对应数据

int PreOrderTraverse(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit)) return 1;
		return 0;
	}
	else return 1;//此时已全部遍历
}//先序遍历(递归)

int InOrderTraverse1(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (InOrderTraverse1(T->lchild, Visit))
			if (Visit(T->data))
				if (InOrderTraverse1(T->rchild, Visit)) return OK;
		return ERROR;
	}
	else return OK;
}//中序遍历

int PostOrderTraverse(BiTree T, bool (*Visit)(char e)) {
	if (T) {
		if (PostOrderTraverse(T->lchild, Visit))
			if (PostOrderTraverse(T->rchild, Visit))
				if (Visit(T->data)) return OK;
		return ERROR;
	}
	else return OK;
}

//层次遍历（需借助队列）：
typedef struct QNode {
	BiTree data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;//队头指针
	QueuePtr rear; //队尾指针
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
}//队尾插入元素，入队
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
}//队头删除元素，出队！
bool QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear) return true;
	else return false;
}//判断队列是否为空
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

//以下为非递归中序遍历二叉树方法（需借助栈）：
typedef struct SNode {
	BiTree data;
	struct SNode* next;
}SNode,* LinkStack;
void InitStack(LinkStack& S) {
	S = (LinkStack)malloc(sizeof(SNode));
	S->next = NULL;
}//初始化栈
void Push(LinkStack& S, BiTree e) {
	LinkStack p = (LinkStack)malloc(sizeof(SNode));
	e=p->data;
	p->next = S->next;
	S->next = p;
}//入栈操作
void Pop(LinkStack& S, BiTree& e) {
	LinkStack q = (LinkStack)malloc(sizeof(SNode));
	q = S->next;
	e = q->data;
	S->next = q->next;
	free(q);
}//出栈操作
bool StackEmpty(LinkStack S) {
	if (S->next == NULL)return 1;
	else return 0;
}//判断栈是否为空
BiTree GetTop(LinkStack S, BiTree& e) {
	if (S->next == NULL)return 0;
	else {
		e = S->next->data;
		return e;
	}
}//取栈顶元素
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
}//非递归中序遍历,借助数组完成模拟栈操作，用栈无法存储BiTree指针

void CountLeaf(BiTree T, int& count) {
	if (T) {
		if ((!T->lchild) && (!T->rchild)) {
			count++;
		}
		CountLeaf(T->lchild, count);
		CountLeaf(T->rchild, count);
	}
}//递归求叶子节点数

int Depth(BiTree T) {
	int depthval;
	if (!T)depthval=0;
	else {
		int depthleft=Depth(T->lchild);
		int depthright=Depth(T->rchild);
		depthval = (depthleft > depthright ? depthleft : depthright) + 1;
	}
	return depthval;
}//递归求树的深度

BiTNode* GetTreeNode(char item, BiTree lptr, BiTree rptr) {
	BiTree T;
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		exit(1);
	T->data = item;
	T->lchild = lptr;
	T->rchild = rptr;
	return T;
}//复制节点操作，是复制二叉树的关键
BiTNode* CopyTree(BiTree T) {
	BiTree newlptr, newrptr;
	if (!T) return NULL;
	if (T->lchild)
		 newlptr = CopyTree(T->lchild);
	else newlptr = NULL;//复制左子树
	if (T->rchild)
		 newrptr = CopyTree(T->rchild);
	else newrptr = NULL;//复制右子树
	BiTree newT = GetTreeNode(T->data, newlptr, newrptr);
	return newT;
}//调用复制节点方法，递归完成复制二叉树

//由先缀式建树、根据已知先序中序序列建树、层次遍历?

typedef enum{Link,Thread}PointerThr;
//Link==0表示指针，Thread==1表示线索
typedef struct BiThrNode {
	char data;
	BiThrNode* lchild, *rchild;
	PointerThr LTag, RTag;
}BiThrNode,*BiThrTree;//线索链表的描述

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
void InOrderThreading2(BiThrTree& Thrt, BiThrTree T) { //Thr为头节点
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
		if (!Visit(p->data)) printf("错误！");
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild; Visit(p->data);
		}
		p = p->rchild;
	}
}//对于给定线索二叉树进行中序遍历

//双亲表示法（顺序表）
typedef struct {
	char data;
	int parent;//双亲位置域
}PTnode;
typedef struct {
	PTnode nodes[100];
	int n;//节点个数
}PTree;

//孩子表示法
struct CTNode {
	int child; //孩子在数组中的位置
	struct CTNode* next;//下一个孩子
};
typedef struct {
	char data;
	struct CTNode* firstChild;
}CTBox;
typedef struct {
	CTBox nodes[100];
	int n, r;//节点数和根的位置
}CTree;

//孩子——兄弟表示法
typedef struct CSNode{
	char data;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;

/*树的先根遍历，具体方法要视树的存储方式而定
void PreOrder(TreeNode* R) {
	if (R != NULL) {
	visit(R);
	while (R还有子树T)
		PreOrder(T);
    }
  后根遍历将while和visit互换位置即可 */


//并查集,由双亲表示法表示
#define SIZE 100
int UFSets[SIZE];
//初始化并查集
void Initial(int S[]) {
	for (int i=0; i < SIZE; i++) {
		S[i] = -1;
	}
}
//“查”操作，x为待查找元素的下标，S[x]为其父亲下标
int Find1(int S[], int x) {
	while (S[x] >= 0)
		x = S[x];
	return x;
}
//Find的优化算法，通过“压缩路径”减少时间复杂度
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

//“并”操作，令root2成为root1的子树
void Union1(int S[], int root1, int root2) {
	if (root1 == root2)
		return;//合并的两个根必须不同
	else {
		S[root2] = root1;
	}
}
//Union的优化算法，确保小树成为大树的子树，从而避免合并后的树高度增加，有利于控制时间复杂度
//但此时树的根节点不能仅为-1，应该为-n（n为总节点数）,保持负号是为了方便查找
void Union2(int S[], int root1, int root2) {
	if (root1 == root2)
		return;
	else if (S[root1] > S[root2]) {//root1的节点数较少
		S[root2] += S[root1];//更新合并后的root2树的总节点数
		S[root1] = root2;
	}
	else if (S[root1] < S[root2]) {//root2的节点数较少
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