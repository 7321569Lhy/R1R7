#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define INFINITY INT_MAX //������ʾ���ޡ�
#define MAX_VERTEX_NUM 100
typedef enum{DG,DN,UDG,UDN}Graphkind;
typedef struct {
	char vexs[MAX_VERTEX_NUM];//������Ϣ
	char arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//����Ϣ,��ʵ�����ڽӾ����и�Ԫ�ص�ֵ��0��1���
	int vexnum, arcnum;//�������ͻ���
	Graphkind kind;//ͼ�������־
}MGraph;//�ڽӾ��󷨱�ʾͼ



//���һ��ע������git����

//�ڽӱ���ʾͼ
typedef struct ArcNode {//����Ϣ
	int adjvex;//��ָ�����һ�ڵ��±�
	struct ArcNode* next;//ָ����һ����
	//�˴����ٶ���Ȩֵ��Ա
}ArcNode;
typedef struct VNode {//������Ϣ
	char data;
	ArcNode* first;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
//������ԣ��ڽӱ��������������ϵķ�����VNode������һ���渺��洢���ݣ�һ���濿�����±�Ϊ�ڵ��ţ����л�ָ��ָ����ڵ�����������ڵ�
//������ʽΪ��������Ԫ�غ�ӵ������������Ա

//ʮ�����������������洢����ͼ
typedef struct VexNode1 {//���Ķ���
	int tailvex;//��β�ڵ���
	int headvex;//��ͷ�ڵ���
	struct VexNode1* hlink;//ָ��ͷ��ͬ����һ����
	struct VexNode1* tlink;//ָ��β��ͬ����һ����
}VexNode1,*VexPointer1;
typedef struct Node1{//����Ķ���
	char data;
	VexNode1* firstin;//�ö�����Ϊ��ͷ�ĵ�һ����
	VexNode1* firstout;//�ö�����Ϊ��β�ĵ�һ����
}Node1,NodeList1[MAX_VERTEX_NUM];

//�ڽӶ��ر������������洢����ͼ
typedef struct VexNode2 {//�ߵĶ���
	int i, j;//�����ӵ���������
	struct VexNode2* iLink;//������i����һ����
	struct VexNode2* jLink;//������j����һ����
}VexNode2,*VexPointer2;
typedef struct Node2 {//����Ķ���
	char data;
	VexPointer2 firstedge;//��ö��������ĵ�һ����
}Node2,NodeList2[MAX_VERTEX_NUM];

//ͼ�Ĺ�����ȱ���
bool visited[MAX_VERTEX_NUM];//���ʱ������
/* void BFSTraverse(Graph G) {
	for (int i = 0; i < G.vexnum; i++) {
		visited[i] = 0;
	}
	InitQueue(Q);//��ʼ����������
	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i])
			BFS(G, i);
	}
}
void BFS(Graph G, int v) {
	visit(v);
	visited[v] = 1;
	EnQueue(Q, v);
	while (!QueueEmpty(Q)) {
		DeQueue(Q, v);
		for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
			if (!visited[w]) {
				visit(w);
				visited[w] = 1;
				EnQueue(Q, w);
			}
		}
	} FirstNeighbor(G,v)�����ṩͼG���붥��v������ĵ�һ�����㣬NextNeighbor(G,v,w)�����ṩͼG�г�w����v������ĵ�һ�����㣬û���򷵻�-1
}*/

//ͼ��������ȱ�������ʹ�õݹ�
/*void DFSTraverse(Graph G) {
	for (int i = 0; i < G.vexnum; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i])
			DFS(G, i);
	}
}
void DFS(Graph G, int v) {
	visit v;
	visited[v] = 1;
	for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
		if (!visited[w])
			DFS(G, w);
	}
}*/

//��ͼG���ɶ���u��������������·�����������Ȩͼ����
/* void BFS_MIN_Distance(Graph G, int u) {
	int d[MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM];
	for (int i = 0; i < G.vexnum; i++) {
		d[i] = INFINITY;//��ʼ��·������,��ʾ��u��i�ľ���
		path[i] = -1;//��ʾ���·����i��ǰ������
	}
	d[u] = 0;
	visited[u] = 1;
	EnQueue(Q, u);
	while (!QueueEmpty(Q)) {
		DeQueue(Q, u);
		for (int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
			if (!visited[w]) {
				d[w] += 1;
				path[w] = u;
				visited[w] = 1;
				EnQueue(Q, w);
			}
		}
	}
}*/

