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
void HeapInsert(Heap *ph, int data)
{
    int idx = ph->numOfData + 1; 

    while(idx != 1) // 루트가 아닌 동안
    {
        if(data - ph->heapArr[getParentIdx(idx)]>0)
        {
            ph->heapArr[idx] = ph->heapArr[getParentIdx(idx)];
            idx = getParentIdx(idx);
        }
        else
            break;
    }
    ph->heapArr[idx] = data;
    ph->numOfData++;
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

int HeapDel(Heap *ph)
{
    int delData = ph->heapArr[1];
    int lastData = ph->heapArr[ph->numOfData];

    int parentIdx = 1;
    int childIdx;

    while(childIdx = getHighPriorityIdx(ph,parentIdx))
    {
        if(lastData - ph->heapArr[childIdx] >= 0)
            break;
        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx;
    }
    ph->heapArr[parentIdx] = lastData;
    ph->numOfData--;

    return delData;
}
void printHeap(Heap* ph)
{
    for(int i = 1 ; i<= ph->numOfData; i++)
    {
        printf(" %d", ph->heapArr[i]);
    }
    printf("\n");
}

int main()
{
    Heap heap;
    char cal;

    HeapInit(&heap);

    while (1)
    {
        scanf("%c", &cal);
        getchar();

        if (cal == 'i')
        { // 힙에 삽입
            int data ;
            scanf("%d",&data);
            getchar();
            HeapInsert(&heap, data);
            printf("0\n");
        }

        else if (cal == 'd')
        { // 힙에서 삭제 루트노드 반환
            printf("%d\n", HeapDel(&heap));
        }

        else if (cal == 'p')
        { // 힙을 레벨 순서로 출력
            printHeap(&heap);
        }

        else if (cal == 'q')
        { // 프로그램 종료
            break;
        }
    }

    return 0;
}