#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
// #define MAX 6

typedef struct _graph {
    int numOfV;    // number of vertices
    int numOfE;    // number of edges
    int** matrix;  // vertices array
    int* visitInfo;
} Graph;

typedef struct _queue {
    int* arr;
    int rear;
    int front;
    int size;
} Queue;
int nextPos(Queue* pq, int pos) {
    if (pos + 1 == pq->size) {
        return 0;
    } else
        return pos + 1;
}
int isEmpty(Queue* pq) { return pq->rear == pq->front; }
int isFull(Queue* pq) { return nextPos(pq, pq->rear) == pq->front; }
void queueInit(Queue* pq, int size) {
    pq->arr = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        pq->arr[i] = 0;
    }
    pq->rear = 0;
    pq->front = 0;
    pq->size = size;
}
void enqueue(Queue* pq, int data) {
    if (isFull(pq)) return;

    pq->rear = nextPos(pq, pq->rear);
    pq->arr[pq->rear] = data;
}
int dequeue(Queue* pq) {
    if (isEmpty(pq)) return FALSE;

    pq->front = nextPos(pq, pq->front);
    int data = pq->arr[pq->front];
    pq->arr[pq->front] = 0;
    return data;
}
void graphInit(Graph* pg, int numOfV) {
    // 0번 인덱스 버려놓고 1번 인덱스부터 사용
    pg->matrix = (int**)malloc(sizeof(int*) * (numOfV + 1));
    pg->visitInfo = (int*)malloc(sizeof(int) * (numOfV + 1));
    pg->numOfV = numOfV;
    pg->numOfE = 0;

    for (int i = 1; i <= numOfV; i++) {
        pg->visitInfo[i] = FALSE;
        pg->matrix[i] = (int*)malloc(sizeof(int) * (numOfV + 1));
        for (int j = 1; j <= numOfV; j++) {
            pg->matrix[i][j] = FALSE;
        }
    }
}
// 간선 추가
void addEdge(Graph* pg, int from, int to) {
    pg->matrix[from][to] = TRUE;
    pg->matrix[to][from] = TRUE;
}
int visitVertex(Graph* pg, int visit) {
    if (pg->visitInfo[visit] == 0) {
        pg->visitInfo[visit] = 1;
        printf("%d\n", visit);
        return TRUE;
    }
    return FALSE;
}
void BFS(Graph* pg, int start) {
    Queue queue;
    int visitV = start;
    int nextV;

    queueInit(&queue, pg->numOfV);
    visitVertex(pg, visitV);
    enqueue(&queue, visitV);
    while (!isEmpty(&queue)) {
        visitV = dequeue(&queue);

        for (int i = 1; i <= pg->numOfV; i++) {
            if (pg->matrix[visitV][i] && !pg->visitInfo[i]) {
                visitVertex(pg, i);
                enqueue(&queue, i);
            }
        }
    }
}
void freeGraph(Graph* pg) {
    for (int i = 1; i <= pg->numOfV; i++) {
        free(pg->matrix[i]);
    }
    free(pg->matrix);
    free(pg->visitInfo);
}
int main() {
    Graph graph;
    int N, M, S;
    int from, to;
    scanf("%d %d %d", &N, &M, &S);
    graphInit(&graph, N);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &from, &to);
        addEdge(&graph, from, to);
    }
    BFS(&graph, S);
    freeGraph(&graph);
    return 0;
}
/*
6 9 1
3 5
1 3
4 1
2 3
3 4
6 4
3 6
1 2
2 5

8 12 4
1 2
2 4
4 7
3 6
6 1
7 6
7 8
1 3
2 7
1 4
2 5
7 5
*/