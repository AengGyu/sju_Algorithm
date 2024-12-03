#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define MAX_V   101
#define MAX_E   1000

typedef struct _node{
    int data;
    int weight;
    struct _node* next;
} Node;
typedef struct _edge{
    int n;
    int weight;
}Edge;
typedef struct _graph{
    int numOfV;
    Node* list[MAX_V];
    int visitInfo[MAX_V];
}Graph;
typedef struct _heap{
    int numOfE;
    Edge heapArr[MAX_E];
}Heap;

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
void graphInit(Graph* pg, int numOfV) {
    // 0번 인덱스 버려놓고 1번 인덱스부터 사용
    pg->numOfV = numOfV;

    for (int i = 1; i <= numOfV; i++) {
        pg->list[i] = listInit(pg->list[i]);
        pg->visitInfo[i] = FALSE;
    }
}
void addEdge(Graph* pg, int from, int to, int weight) {
    if (from == to) {
        pg->list[from] = listInsert(pg->list[from], to, weight);
        return;
    }
    pg->list[from] = listInsert(pg->list[from], to, weight);
    pg->list[to] = listInsert(pg->list[to], from, weight);
}
void heapInit(Heap* ph){
    ph->numOfE = 0;
}
int isEmpty(Heap* ph){
    if(ph->numOfE == 0)
        return TRUE;
    else 
        return FALSE;
}
void heapInsert(Heap* ph, int n, int w){
    Edge edge = {n,w};
    int idx = ph->numOfE + 1;

    while(idx != 1){
        if(edge.weight < ph->heapArr[idx/2].weight){
            ph->heapArr[idx] = ph->heapArr[idx/2];
            idx = idx/2;
        }
        else{
            break;
        }
    }
    ph->heapArr[idx] = edge;
    ph->numOfE++;
}
int getHighPriorityIdx(Heap* ph, int idx){
    if(idx*2 > ph->numOfE) return 0;
    else if(idx*2 == ph->numOfE) return idx*2;
    else{
        if(ph->heapArr[idx*2].weight < ph->heapArr[idx*2+1].weight) return idx*2;
        else return idx*2+1;
    }
}
Edge heapDelete(Heap* ph){
    Edge del = ph->heapArr[1];
    Edge last = ph->heapArr[ph->numOfE];

    int parentIdx = 1;
    int childIdx = getHighPriorityIdx(ph,parentIdx);

    while(childIdx){
        if(last.weight <= ph->heapArr[childIdx].weight) break;

        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx;
        childIdx = getHighPriorityIdx(ph,parentIdx);
    }
    ph->heapArr[parentIdx] = last;
    ph->numOfE--;

    return del;
}
int prim(Graph* pg, int start){
    Heap heap;
    int weight = 0;
    
    heapInit(&heap);
    
    Node* p = pg->list[start];
    while(p!=NULL){
        heapInsert(&heap,p->data,p->weight);
        p = p->next;
    }
    pg->visitInfo[start] = TRUE;
    printf(" %d", start);

    while(!isEmpty(&heap)){
        Edge edge = heapDelete(&heap); // 우선순위 큐에서 꺼낸 노드 번호
        int n = edge.n;   

        if(!pg->visitInfo[n]){ // 방문하지 않은 노드라면 연결된 간선들을 우선순위 큐에 추가
            printf(" %d", n);
            weight += edge.weight;
            Node* p = pg->list[n];
            while(p != NULL){ 
                if(!pg->visitInfo[p->data]) heapInsert(&heap,p->data,p->weight); // 추가하려는 간선의 방문 여부 확인 후 추가 
                p = p->next;
            }
            pg->visitInfo[n] = TRUE;
        }
    }

    return weight;
}
void graphFree(Graph* pg) {
    for (int i = 1; i <= pg->numOfV; i++) {
        Node* cur = pg->list[i];
        while (cur != NULL) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}
int main(){
    Graph graph;
    int n, m;
    int to, from, weight;
    int MST_weight;

    scanf("%d %d", &n,&m);

    graphInit(&graph,n);

    for(int i=0;i<m;i++){
        scanf("%d %d %d",&from,&to,&weight);
        addEdge(&graph,from,to,weight);
    }
    
    MST_weight = prim(&graph,1);
    printf("\n%d",MST_weight);
    graphFree(&graph);
    return 0;
}

/*
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6
*/