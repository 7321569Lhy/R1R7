#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 100

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
void PopStack(SqStack& S, int& e) {
	if (S.top == S.base)exit(0);
	else {
		e = *(S.top - 1);
		S.top--;
	}
}//出栈，记录前一位数据

typedef struct ArcNode {//弧信息
	int adjvex;//弧指向的下一节点下标
	struct ArcNode* next;//指向下一条弧
	//此处可再定义权值成员
}ArcNode;
typedef struct VNode {//顶点信息
	char data;
	ArcNode* first;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}Graph;

//拓扑排序
/*bool TopologicalSort(Graph G) {
	SqStack S;
	InitStack(S);
	for (int i = 0; i < G.vexnum; i++) {
		if (indegree[i] == 0)
			PushStack(S, i);
	}
	int count = 0;
	while (!StackEmpty(S)) {
		PopStack(S, e);
		printf[count++] = e;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
			v = p->adjvex;
			--indegree[v];
			if (indegree[v])
				PushStack(S, v);
		}
	}
	if (count < G.vexnum) return false;
	else return true;
} */

//直接插入排序
void InsertSort(int A[], int n) {
	int i, j, temp;
	for (i = 1; i < n; i++) {
		if (A[i] < A[i - 1]) {
			temp = A[i];
			for (j = i - 1; j >= 0 && A[j] > temp; j--)
				A[j + 1] = A[j];
			A[j + 1] = temp;
		}
	}
}
void InsetSort2(int A[], int n) {//改良版
	int i, j, low, high,mid;
	for (i = 2; i <= n; i++) {
		A[0] = A[i];
		low = 1;
		high = i - 1;
		while (low <= high) {
			mid = (low + high) / 2;
			if (A[mid] > A[0]) high = mid - 1;
			else low = mid + 1;
		}
		for (j = i-1; j <= low; j--)
			A[j+1] = A[j];
		A[low] = A[0];
	}
}

//希尔排序
void ShellSort(int A[], int n) {
	int i, j,d;
	for (d = n / 2;d>= 1; d = d / 2) {
		for (i = d + 1; i <= n; i++) {
			if (A[i] < A[i - d]) {
				A[0] = A[i];
				for (j = i - d; j>0&&A[j]>A[0]; j = j - d)
					A[j+d] = A[j];
				A[j + d] = A[0];
			}
		}
	}
}

//冒泡排序
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void BubbleSort(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		bool flag = false;
		for (int j = n - 1; j > i; j--) {
			if (A[j - 1] > A[j]) {
				swap(A[j - 1], A[j]);
				flag = true;
			}
		}
		if (flag == false)
			return;
	}
}

//快速排序（使用递归）
int Partition(int A[], int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot)
			--high;
		A[low] = A[high];
		while (low < high && A[low] <= pivot)
			++low;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}
void QuickSort(int A[], int low, int high) {
	if (low < high) {
		int pivotpos = Partition(A, low, high);
		QuickSort(A, low, pivotpos - 1);
		QuickSort(A, pivotpos + 1, high);
	}
}

//简单选择排序
void SelectSort(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j] < A[min]) min = j;
		}
		if (min != i) swap(A[i], A[min]);
	}
}

//建立大根堆
void BuildMaxHeap(int A[], int len) {
	for (int i = len / 2; i > 0; i--)
		HeadAdjust(A, i, len);
}
//将以k为根的子树调整为大根堆
void HeadAdjust(int A[], int k, int len) {
	A[0] = A[k];
	for (int i = 2 * k; i <= len; i *= 2) {
		if (i < len && A[i] < A[i + 1])
			i++;
		if (A[0] >= A[i])
			break;
		else {
			A[k] = A[i];
			k = i;
		}
	}
	A[k] = A[0];
}
void HeapSort(int A[], int len) {
	BuildMaxHeap(A, len);
	for (int i = len; i > 1; i--) {
		swap(A[i], A[1]);
		HeadAdjust(A, 1, i - 1);
	}
}

//归并排序
int* B = (int*)malloc(20 * sizeof(int));//设置辅助数组
void Merge(int A[], int low, int mid, int high) {
	int i, j, k;
	for (i = low; i <= high; i++)
		B[i] = A[i];//将A中元素全部复制到B中
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (B[i] <= B[j])
			A[k] = B[i++];
		else
			A[k] = B[j++];
	}
	while (i <= mid)
		A[k++] = B[i++];
	while (j <= high)
		A[k++] = B[j++];
}
void MergeSort(int A[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(A, low, mid);
		MergeSort(A, mid + 1, high);
		Merge(A, low, mid, high);
	}
}