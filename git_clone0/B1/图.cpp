#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define INFINITY INT_MAX //用来表示“∞”
#define MAX_VERTEX_NUM 100
typedef enum{DG,DN,UDG,UDN}Graphkind;
typedef struct {
	char vexs[MAX_VERTEX_NUM];//顶点信息
	char arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//弧信息,其实就是邻接矩阵中各元素的值：0或1或∞
	int vexnum, arcnum;//顶点数和弧数
	Graphkind kind;//图的种类标志
}MGraph;//邻接矩阵法表示图



//添加一行注释用作git测试

//邻接表法表示图
typedef struct ArcNode {//弧信息
	int adjvex;//弧指向的下一节点下标
	struct ArcNode* next;//指向下一条弧
	//此处可再定义权值成员
}ArcNode;
typedef struct VNode {//顶点信息
	char data;
	ArcNode* first;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
//总体而言，邻接表法是数组与链表结合的方法，VNode的数组一方面负责存储数据，一方面靠数组下标为节点编号，还有弧指针指向与节点关联的其他节点
//表现形式为单个数组元素后接单个或多个链表成员

//十字链表法，仅能用来存储有向图
typedef struct VexNode1 {//弧的定义
	int tailvex;//弧尾节点编号
	int headvex;//弧头节点编号
	struct VexNode1* hlink;//指向弧头相同的下一条弧
	struct VexNode1* tlink;//指向弧尾相同的下一条弧
}VexNode1,*VexPointer1;
typedef struct Node1{//顶点的定义
	char data;
	VexNode1* firstin;//该顶点作为弧头的第一条弧
	VexNode1* firstout;//该顶点作为弧尾的第一条弧
}Node1,NodeList1[MAX_VERTEX_NUM];

//邻接多重表法，仅能用来存储无向图
typedef struct VexNode2 {//边的定义
	int i, j;//边连接的两个顶点
	struct VexNode2* iLink;//依附于i的下一条边
	struct VexNode2* jLink;//依附于j的下一条边
}VexNode2,*VexPointer2;
typedef struct Node2 {//顶点的定义
	char data;
	VexPointer2 firstedge;//与该顶点相连的第一条边
}Node2,NodeList2[MAX_VERTEX_NUM];

//图的广度优先遍历
bool visited[MAX_VERTEX_NUM];//访问标记数组
/* void BFSTraverse(Graph G) {
	for (int i = 0; i < G.vexnum; i++) {
		visited[i] = 0;
	}
	InitQueue(Q);//初始化辅助队列
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
	} FirstNeighbor(G,v)用于提供图G中与顶点v相关联的第一个顶点，NextNeighbor(G,v,w)用于提供图G中除w外与v相关联的第一个顶点，没有则返回-1
}*/

//图的深度优先遍历，需使用递归
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

//求图G中由顶点u到其他顶点的最短路径，解决不带权图问题
/* void BFS_MIN_Distance(Graph G, int u) {
	int d[MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM];
	for (int i = 0; i < G.vexnum; i++) {
		d[i] = INFINITY;//初始化路径长度,表示由u到i的距离
		path[i] = -1;//表示最短路径中i的前驱顶点
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

