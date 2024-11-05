#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 6

typedef struct _node {
    int data;
    int weight;
    struct _node* next;
} Node;

typedef struct _graph {
    int numOfV;   // number of vertices
    int numOfE;   // number of edges
    Node** list;  // vertices array
} Graph;

Node* listInit(Node* head) {
    head = NULL;
    return head;
}
Node* listInsert(Node* head, int data, int weight) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    Node* cur = head;
    newnode->data = data;
    newnode->weight = weight;
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
Node* listRemove(Node* head, int data) {
    Node* prev = NULL;
    Node* cur = head;

    while (cur != NULL) {
        if (cur->data == data) {
            // 헤드 삭제
            if (prev == NULL) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }

    return head;
}
void listTraverse(Node* head) {
    Node* p = head;

    while (p != NULL) {
        printf(" %d %d", p->data, p->weight);
        p = p->next;
    }
}
// 그래프 초기화
void graphInit(Graph* pg, int numOfV) {
    // 0번 인덱스 버려놓고 1번 인덱스부터 사용
    pg->list = (Node**)malloc(sizeof(Node*) * (numOfV + 1));

    pg->numOfV = numOfV;
    pg->numOfE = 0;

    for (int i = 1; i <= numOfV; i++) {
        pg->list[i] = listInit(pg->list[i]);
    }
}
int existEdge(Graph* pg, int from, int to) {
    // 범위 밖 입력
    // 이게 없으면 runtime error, 범위 밖 수가 입력 됐을 때 존재하지 않는 인덱스를 참조하게 됨.
    // 메인 함수에서 직접 확인하는 게 아니라 함수 호출을 하고 유효한 인덱스인지 확인하기 때문에 그럼.
    if ((from < 1 || from > MAX) || (to < 1 || to > MAX)) {
        return FALSE;
    }
    Node* p = pg->list[from];

    while (p != NULL) {
        if (p->data == to) {
            return TRUE;
        }
        p = p->next;
    }

    return FALSE;
}
// 간선 추가
void addEdge(Graph* pg, int from, int to, int weight) {
    // 범위 밖 입력
    if ((from < 1 || from > MAX) || (to < 1 || to > MAX)) {
        printf("-1\n");
        return;
    }
    if (from == to) {
        pg->list[from] = listInsert(pg->list[from], to, weight);
        return;
    }
    pg->list[from] = listInsert(pg->list[from], to, weight);
    pg->list[to] = listInsert(pg->list[to], from, weight);
}
void changeWeight(Graph* pg, int from, int to, int weight) {
    Node* p = pg->list[from];

    // 함수화 해도 될 거 같은데
    while (p != NULL) {
        if (p->data == to) {
            p->weight = weight;
            break;
        }
        p = p->next;
    }

    p = pg->list[to];

    while (p != NULL) {
        if (p->data == from) {
            p->weight = weight;
            break;
        }
        p = p->next;
    }
}
void showVertexInfo(Graph* pg, int vertextNum) {
    if (vertextNum < 1 || vertextNum > MAX) {
        printf("-1\n");
        return;
    }
    listTraverse(pg->list[vertextNum]);
    printf("\n");
}
// 간선 삭제
void removeEdge(Graph* pg, int from, int to) {
    // 범위 밖 입력
    if ((from < 1 || from > MAX) || (to < 1 || to > MAX)) {
        printf("-1\n");
        return;
    }
    pg->list[from] = listRemove(pg->list[from], to);
    pg->list[to] = listRemove(pg->list[to], from);
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
}
int main() {
    Graph graph;
    int numOfV = 6, n;
    int from, to, weight;
    int flag = TRUE;
    char cal;

    graphInit(&graph, numOfV);

    addEdge(&graph, 1, 2, 1);
    addEdge(&graph, 1, 3, 1);
    addEdge(&graph, 1, 4, 1);
    addEdge(&graph, 1, 6, 2);
    addEdge(&graph, 2, 3, 1);
    addEdge(&graph, 3, 5, 4);
    addEdge(&graph, 5, 5, 4);
    addEdge(&graph, 5, 6, 3);

    while (flag) {
        scanf(" %c", &cal);
        switch (cal) {
            case 'a':
                scanf("%d", &n);
                showVertexInfo(&graph, n);
                break;
            case 'm':
                scanf("%d %d %d", &from, &to, &weight);
                // weight == 0 인 경우는 기존 간선을 삭제
                if (weight == 0) {
                    removeEdge(&graph, from, to);
                }
                // 기존에 가중치가 있던 경우 가중치 변경
                else if (existEdge(&graph, from, to)) {
                    changeWeight(&graph, from, to, weight);
                }
                // 기존에 가중치가 없던 경우 새로운 간선 추가
                // 간선이 존재하는지 확인하는 함수 필요 boolean
                else if (!existEdge(&graph, from, to)) {
                    addEdge(&graph, from, to, weight);
                }
                // changeWeight 함수를 boolean 반환형으로 만들어서 가중치를 바꾸는데 실패하면 FALSE를 반환
                // if(!changeWeight) addEdge() , 이런식으로도 작성 가능 
                break;
            case 'q':
                flag = FALSE;
                break;
        }
    }
    freeGraph(&graph);
    return 0;
}

/*
input
a 2
m 4 2 3
a 2
q

output
 1 1 3 1
 1 1 3 1 4 3

input
a 5
m 3 5 0
a 5
a 7
q

output
 3 4 5 4 6 3
 5 4 6 3
-1
*/