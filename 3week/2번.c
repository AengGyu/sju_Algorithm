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
int isEmpty(Heap *ph)
{
    if (ph->numOfData == 0)
        return True;
    else
        return False;
}
int getParentIdx(int idx)
{
    return idx/2;
}
int getLeftChildIdx(int idx)
{
    return idx*2;
}
int getRightChildIdx(int idx)
{
    return idx*2 + 1;
}
int getHighPriorityIdx(Heap*ph,int idx)
{
    if(getLeftChildIdx(idx) > ph->numOfData) // 자식이 없는 경우
        return 0;
    else if(getLeftChildIdx(idx) == ph->numOfData) // 자식이 왼쪽만
        return getLeftChildIdx(idx);
    else // 자식 둘 다 있는 경우
    {
        if(ph->heapArr[getLeftChildIdx(idx)] - ph->heapArr[getRightChildIdx(idx)]>0)
            return getLeftChildIdx(idx);
        else
            return getRightChildIdx(idx);
    }
}
void downHeap(Heap *ph, int parentIdx)
{
    int childIdx;
    int lastData = ph->heapArr[parentIdx];

    while ((childIdx = getHighPriorityIdx(ph, parentIdx)))
    {
        if (lastData >= ph->heapArr[childIdx])
            break;
        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx;
    }
    ph->heapArr[parentIdx] = lastData;
}

void buildHeap(Heap *ph)
{
    for (int i = ph->numOfData / 2; i > 0; i--)
    {
        downHeap(ph, i);
    }
}

int main()
{
    int n;
    Heap heap;

    scanf("%d",&n);
    heap.numOfData = n;

    for(int i=1;i<=n;i++)
    {
        scanf("%d",&(heap.heapArr[i]));
    }
    
    buildHeap(&heap);

    for(int i=1;i<=n;i++)
    {
        printf(" %d",heap.heapArr[i]);
    }

    return 0;
}