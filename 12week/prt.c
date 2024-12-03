#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
    int data;
    struct _node* next;
} Node;

typedef struct _graph {
    int numOfV;
    Node** list;
    char* name;
    int* inDegree;
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
    }
    return pos + 1;
}
int isEmpty(Queue* pq) { return pq->front == pq->rear; }
int isFull(Queue* pq) { return nextPos(pq, pq->rear) == pq->front; }
void queueInit(Queue* pq, int size) {
    pq->arr = (int*)malloc(sizeof(int) * (size+1));
    pq->rear = 0;
    pq->front = 0;
    pq->size = size+1;
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
    return data;
}
Node* listInit(Node* head) {
    head = NULL;
    return head;
}
Node* listInsert(Node* head, int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->next = NULL;

    newnode->next = head;
    head = newnode;
    return head;
}
void graphInit(Graph* pg, int numOfV) {
    pg->list = (Node**)malloc(sizeof(Node*) * numOfV);
    pg->name = (char*)malloc(sizeof(char)*numOfV);
    pg->inDegree = (int*)malloc(sizeof(int)*numOfV);
    pg->numOfV = numOfV;

    for (int i = 0; i < pg->numOfV; i++) {
        pg->list[i] = listInit(pg->list[i]);
        pg->inDegree[i] = 0;
    }
}
int getIdx(Graph* pg, char name){
    for(int i=0;i<pg->numOfV;i++){
        if(pg->name[i]==name){
            return i;
        }
    }
    return -1;
}
void addEdge(Graph* pg, char from, char to) {
    int fromIdx = getIdx(pg,from);
    int toIdx = getIdx(pg, to);

    pg->list[fromIdx] = listInsert(pg->list[fromIdx],toIdx);
    pg->inDegree[toIdx]++;
}
void topologicalSort(Graph* pg){
    Queue q;
    queueInit(&q, pg->numOfV);
    int* result = (int*)malloc(sizeof(int)*pg->numOfV);
    int resultIdx = 0;
    for(int i=0;i<pg->numOfV;i++){
        if(pg->inDegree[i]==0){
            enqueue(&q,i);
        }
    }
    while(!isEmpty(&q)){
        int current = dequeue(&q);
        result[resultIdx++] = current;

        Node* tmp = pg->list[current];
        while(tmp != NULL){
            pg->inDegree[tmp->data]--;
            if(pg->inDegree[tmp->data]==0){
                enqueue(&q, tmp->data);
            }
            tmp = tmp->next;
        }
    }
    if(resultIdx != pg->numOfV){
        printf("0\n");
    }
    else{
        for(int i=0;i<resultIdx; i++){
            printf("%c ", pg->name[result[i]]);
        }
        printf("\n");
    }
    free(result);
}
void graphFree(Graph* pg){
    for(int i=0;i<pg->numOfV;i++){
        free(pg->list[i]);
    }
    free(pg->inDegree);
    free(pg->name);
    free(pg->list);
}
int main() {
    Graph graph;
    int N, M;
    char from, to;
    
    scanf("%d", &N);
    graphInit(&graph,N);
    for(int i=0;i<N;i++){
        scanf(" %c", &graph.name[i]);
    }
    scanf("%d",&M);
    for(int i =0;i<M;i++){
        scanf(" %c %c", &from,&to);
        addEdge(&graph,from,to);
    }

    topologicalSort(&graph);
    graphFree(&graph);

    return 0;
}

/*
3
A B C
3
A B
C A
C B

C A B

4
A B C D
6
A B
C A
C B
A D
B D
D C

0

8
A B C D E F G H
11
A B
C B
A D
C D
B D
D E
E F
E H
E G
F G
H G

A C B D E H F G
*/