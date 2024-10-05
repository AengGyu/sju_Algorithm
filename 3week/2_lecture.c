#include <stdio.h>

#define True 1
#define False 0

typedef struct _heap
{
    int numOfData;
    int heapArr[100];

} Heap;

void HeapInit(Heap *ph)
{
    ph->numOfData = 0;
}
int getParentIdx(int idx)
{
    return idx / 2;
}
int getLeftChildIdx(int idx)
{
    return idx * 2;
}
int getRightChildIdx(int idx)
{
    return idx * 2 + 1;
}
int getHighPriorityIdx(Heap *ph, int idx)
{
    if (getLeftChildIdx(idx) > ph->numOfData)
        return 0;
    else if (getLeftChildIdx(idx) == ph->numOfData)
        return getLeftChildIdx(idx);
    else
    {
        if (ph->heapArr[getLeftChildIdx(idx)] > ph->heapArr[getRightChildIdx(idx)])
            return getLeftChildIdx(idx);
        else
            return getRightChildIdx(idx);
    }
}
void downHeap(Heap *ph, int idx)
{
    int parentIdx = idx;
    int childIdx = getHighPriorityIdx(ph, parentIdx);
    if (childIdx == 0)
        return;
    if (ph->heapArr[parentIdx] >= ph->heapArr[childIdx])
        return;
    int tmp = ph->heapArr[parentIdx];
    ph->heapArr[parentIdx] = ph->heapArr[childIdx];
    ph->heapArr[childIdx] = tmp;
    downHeap(ph, childIdx);
}
void buildHeap(Heap *ph, int idx)
{
    if (getLeftChildIdx(idx) > ph->numOfData)
        return;
    buildHeap(ph, getLeftChildIdx(idx));
    buildHeap(ph, getRightChildIdx(idx));
    downHeap(ph,idx);
}
void printHeap(Heap *ph)
{
    for (int i = 1; i <= ph->numOfData; i++)
    {
        printf(" %d", ph->heapArr[i]);
    }
    printf("\n");
}

int main()
{
    Heap heap;
    int numOfKey;

    scanf("%d", &numOfKey);
    heap.numOfData = numOfKey;

    for(int i=1;i<=numOfKey;i++){

        scanf("%d",&heap.heapArr[i]);
    }

    buildHeap(&heap,1);
    printHeap(&heap);

    return 0;
}