#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
// #define MAX 1000

typedef struct _node {
    int data;
    // int weight;
    struct _node* next;
} Node;

typedef struct _graph {
    int numOfV;   // number of vertices
    int numOfE;   // number of edges, 필요한가...
    Node** list;  // vertices array
    int* visitInfo;
} Graph;

typedef struct _stack {
    int top;
    int* arr;
} Stack;

int isEmpty(Stack* pstack) { return pstack->top == -1; }
void stackInit(Stack* pstack, int n) {
    pstack->arr = (int*)malloc(sizeof(int) * n);
    pstack->top = -1;
}
void push(Stack* pstack, int n) {
    pstack->top++;
    pstack->arr[pstack->top] = n;
}
int pop(Stack* pstack) {
    int idx = pstack->top;
    pstack->top--;
    return pstack->arr[idx];
}
Node* listInit(Node* head) {
    head = NULL;
    return head;
}
Node* listInsert(Node* head, int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    Node* cur = head;
    newnode->data = data;
    // newnode->weight = weight;
    newnode->next = NULL;

    // 빈 리스트
    if (head == NULL) {
        head = newnode;
        return head;
    }
    // head의 값보다 newnode의 값이 더 작은 경우
    if (data < head->data) {
        newnode->next = head;
        head = newnode;
        return head;
    }
    // 중간에 삽입 해야 하는 경우
    while (cur->next != NULL && cur->next->data < data) {
        cur = cur->next;
    }
    newnode->next = cur->next;
    cur->next = newnode;
    return head;
}
// 그래프 초기화
void graphInit(Graph* pg, int numOfV) {
    // 0번 인덱스 버려놓고 1번 인덱스부터 사용
    pg->list = (Node**)malloc(sizeof(Node*) * (numOfV + 1));
    pg->visitInfo = (int*)malloc(sizeof(int) * (numOfV + 1));
    pg->numOfV = numOfV;
    pg->numOfE = 0;

    for (int i = 1; i <= numOfV; i++) {
        pg->list[i] = listInit(pg->list[i]);
    }
    for (int i = 1; i <= numOfV; i++) {
        pg->visitInfo[i] = 0;
    }
}
// 간선 추가
void addEdge(Graph* pg, int from, int to) {
    if (from == to) {
        pg->list[from] = listInsert(pg->list[from], to);
        return;
    }
    pg->list[from] = listInsert(pg->list[from], to);
    pg->list[to] = listInsert(pg->list[to], from);
}
int visitVertex(Graph* pg, int visit) {
    if (pg->visitInfo[visit] == 0) {
        pg->visitInfo[visit] = 1;
        printf("%d\n", visit);
        return TRUE;
    }
    return FALSE;
}
void DFS(Graph* pg, int start) {
    Stack stack;
    int visitV = start;
    int nextV;

    stackInit(&stack, pg->numOfV);
    visitVertex(pg, visitV);
    push(&stack, visitV);

    while (!isEmpty(&stack)) {
        visitV = pop(&stack);

        Node* cur = pg->list[visitV];
        while (cur != NULL) {
            nextV = cur->data;
            if (visitVertex(pg, nextV)) {
                push(&stack, visitV);
                push(&stack, nextV);
                break;
            }
            cur = cur->next;
        }
    }
}
void freeGraph(Graph* pg) {
    for (int i = 1; i <= pg->numOfV; i++) {
        Node* cur = pg->list[i];
        while (cur != NULL) {
            Node* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(pg->list);
    free(pg->visitInfo);
}

int main() {
    Graph graph;
    int N, M, S;
    int from, to;

    scanf("%d %d %d", &N, &M, &S);
    // 정점 생성
    graphInit(&graph, N);

    // 간선 생성
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &from, &to);
        addEdge(&graph, from, to);
    }

    // DFS
    DFS(&graph, S);
    freeGraph(&graph);
    return 0;
}

/*
5 7 1
1 2
1 4
5 1
3 5
4 3
3 1
2 3

8 12 7
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