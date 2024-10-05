#include <stdio.h>

typedef struct _heap {  // min heap
    int numOfData;
    int heapArr[100];
} Heap;

void initHeap(Heap* ph) { ph->numOfData = 0; }

int getParentIdx(int idx) { return idx / 2; }
int getLeftChildIdx(int idx) { return idx * 2; }
int getRightChildIdx(int idx) { return idx * 2 + 1; }
void upHeap(Heap* ph, int idx) {
    if (idx == 1) {
        return;
    }
    if (ph->heapArr[idx] >= ph->heapArr[getParentIdx(idx)]) {
        return;
    }
    int tmp = ph->heapArr[idx];
    ph->heapArr[idx] = ph->heapArr[getParentIdx(idx)];
    ph->heapArr[getParentIdx(idx)] = tmp;
    upHeap(ph, getParentIdx(idx));
}
void insertHeap(Heap* ph, int key) {
    int idx = ph->numOfData + 1;
    ph->heapArr[idx] = key;
    upHeap(ph, idx);
    ph->numOfData++;
}
int getHighPriorityIdx(Heap* ph, int idx) {
    if (getLeftChildIdx(idx) > ph->numOfData) {
        return 0;
    } else if (getLeftChildIdx(idx) == ph->numOfData) {
        return getLeftChildIdx(idx);
    } else {
        if (ph->heapArr[getLeftChildIdx(idx)] < ph->heapArr[getRightChildIdx(idx)]) {
            return getLeftChildIdx(idx);
        } else {
            return getRightChildIdx(idx);
        }
    }
}
void downHeap(Heap* ph, int idx) {
    int parentIdx = idx;
    int childIdx = getHighPriorityIdx(ph, parentIdx);

    if (childIdx == 0) {
        return;
    }
    if (ph->heapArr[parentIdx] <= ph->heapArr[childIdx]) {
        return;
    }
    int tmp = ph->heapArr[parentIdx];
    ph->heapArr[parentIdx] = ph->heapArr[childIdx];
    ph->heapArr[childIdx] = tmp;
    downHeap(ph, childIdx);
}
int deleteHeap(Heap* ph) {
    int delKey = ph->heapArr[1];
    int lastKey = ph->heapArr[ph->numOfData];

    ph->heapArr[1] = lastKey;
    downHeap(ph, 1);
    ph->numOfData--;

    return delKey;
}
void buildHeap(Heap *ph, int idx)
{
    if (getLeftChildIdx(idx) > ph->numOfData)
        return;
    buildHeap(ph, getLeftChildIdx(idx));
    buildHeap(ph, getRightChildIdx(idx));
    downHeap(ph,idx);
}

void heapSort(Heap* heap, int n) {
    for (int i = 1; i <= n; i++) {
        printf(" %d", deleteHeap(heap));
    }
}

int main() {
    int n;
    Heap heap;

    initHeap(&heap);

    scanf("%d", &n);
    heap.numOfData = n;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &heap.heapArr[i]);
    }

    buildHeap(&heap,1);

    heapSort(&heap, n);
}