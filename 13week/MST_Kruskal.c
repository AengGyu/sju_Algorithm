#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_V 101
#define MAX_E 1000

typedef struct _edge {
    int from;
    int to;
    int weight;
} Edge;
typedef struct _heap {
    int numOfE;
    Edge heapArr[MAX_E];
} Heap;

void heapInit(Heap* ph) { ph->numOfE = 0; }
int isEmpty(Heap* ph) {
    if (ph->numOfE == 0)
        return TRUE;
    else
        return FALSE;
}
void heapInsert(Heap* ph, Edge edge) {
    int idx = ph->numOfE + 1;

    while (idx != 1) {
        if (edge.weight < ph->heapArr[idx / 2].weight) {
            ph->heapArr[idx] = ph->heapArr[idx / 2];
            idx = idx / 2;
        } else {
            break;
        }
    }
    ph->heapArr[idx] = edge;
    ph->numOfE++;
}
int getHighPriorityIdx(Heap* ph, int idx) {
    if (idx * 2 > ph->numOfE)
        return 0;
    else if (idx * 2 == ph->numOfE)
        return idx * 2;
    else {
        if (ph->heapArr[idx * 2].weight < ph->heapArr[idx * 2 + 1].weight)
            return idx * 2;
        else
            return idx * 2 + 1;
    }
}
Edge heapDelete(Heap* ph) {
    Edge del = ph->heapArr[1];
    Edge last = ph->heapArr[ph->numOfE];

    int parentIdx = 1;
    int childIdx = getHighPriorityIdx(ph, parentIdx);

    while (childIdx) {
        if (last.weight <= ph->heapArr[childIdx].weight) break;

        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx;
        childIdx = getHighPriorityIdx(ph, parentIdx);
    }
    ph->heapArr[parentIdx] = last;
    ph->numOfE--;

    return del;
}
int find(int parent[], int v) {
    if (parent[v] != v) {
        parent[v] = find(parent, parent[v]);
    }
    return parent[v];
}
void _union(int parent[], int v, int u) {
    int root_v = find(parent, v);
    int root_u = find(parent, u);

    if (root_v != root_u) {
        parent[root_u] = root_v;
    }
}
int kruskal(Edge edge[], int numOfV, int numOfE) {
    Heap heap;
    int edge_MST = 0;
    int weight = 0;
    heapInit(&heap);

    for (int i = 0; i < numOfE; i++) {
        heapInsert(&heap, edge[i]);
    }

    int parent[MAX_V];
    for (int i = 1; i <= numOfV; i++) {
        parent[i] = i;  // 자기 자신을 부모로
    }

    while (!isEmpty(&heap) && edge_MST < numOfV - 1) {
        Edge min_weight = heapDelete(&heap);

        int v = find(parent, min_weight.from);  // 루트를 찾음
        int u = find(parent, min_weight.to);

        if (v != u) {  // 두 루트가 다르면 union
            weight += min_weight.weight;
            edge_MST++;
            printf(" %d", min_weight.weight);
            _union(parent, min_weight.from, min_weight.to);
        }
    }
    return weight;
}

int main() {
    int n, m;
    int to, from, weight;
    int MST_weight;

    scanf("%d %d", &n, &m);

    Edge edge[m];

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &to, &from, &weight);
        edge[i] = (Edge){to, from, weight};
    }

    MST_weight = kruskal(edge, n, m);
    printf("\n%d", MST_weight);

    return 0;
}

/*
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37

5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31
*/