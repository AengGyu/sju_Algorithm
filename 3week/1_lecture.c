#include <stdio.h>

typedef struct _heap
{
    int numOfData;
    int heapArr[100];
} Heap;

void heapInit(Heap *ph)
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
void upHeap(Heap *ph, int idx)
{
    if (idx == 1)
        return;
    if (ph->heapArr[idx] <= ph->heapArr[getParentIdx(idx)])
        return;
    int tmp = ph->heapArr[idx];
    ph->heapArr[idx] = ph->heapArr[getParentIdx(idx)];
    ph->heapArr[getParentIdx(idx)] = tmp;
    upHeap(ph, getParentIdx(idx));
}
void heapInsert(Heap *ph, int key)
{
    int idx = ph->numOfData + 1;
    ph->heapArr[idx] = key;
    upHeap(ph, idx);
    ph->numOfData++;
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
int heapDel(Heap *ph)
{
    int delData = ph->heapArr[1];
    int lastData = ph->heapArr[ph->numOfData];

    ph->heapArr[1] = lastData;
    downHeap(ph, 1);
    ph->numOfData--;

    return delData;
}
void printHeap(Heap*ph){
    for(int i=1;i<=ph->numOfData;i++){
        printf(" %d",ph->heapArr[i]);
    }
    printf("\n");
}

int main()
{
    Heap heap;
    char cal;

    heapInit(&heap);

    while(1)
    {
        scanf("%c",&cal);
        getchar();

        if(cal == 'i'){
            int data;
            scanf("%d",&data);
            getchar();
            heapInsert(&heap, data);
            printf("0\n");
        }
        else if(cal == 'd'){
            printf("%d\n",heapDel(&heap));
        }
        else if(cal == 'p'){
            printHeap(&heap);
        }
        else if(cal == 'q')
        {
            break;
        }
    }
    return 0;
}