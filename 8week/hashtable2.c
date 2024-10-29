#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _hashTable {
    int* arr;
    int size;
} HashTable;

HashTable* tableInit(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));

    table->size = size;

    table->arr = (int*)calloc(size, sizeof(int));

    return table;
}
int hash(int data, int size) { return data % size; }
void tableInsert(HashTable* table, int data) {
    int hashValue = hash(data, table->size);

    while (table->arr[hashValue]) {  // 해당 인덱스에 값이 있으면
        hashValue = (hashValue + 1) % table->size;
        printf("C");
    }
    printf("%d\n", hashValue);
    table->arr[hashValue] = data;
}
void tableSearch(HashTable* table, int data) {
    int hashValue = hash(data, table->size);

    while (table->arr[hashValue]) {
        if (table->arr[hashValue] == data) {
            printf("%d %d\n", hashValue, data);
            return;
        }
        hashValue = (hashValue + 1) % table->size;
    }
    printf("-1\n");
    return;
}
void Free(HashTable* table) {
    free(table->arr);
    free(table);
}
int main() {
    int size, n;
    char cal;
    int flag = TRUE;
    HashTable* table;
    int data;

    scanf("%d %d", &size, &n);

    table = tableInit(size);

    while (flag) {
        scanf(" %c", &cal);
        switch (cal) {
            case 'i':
                scanf("%d", &data);
                tableInsert(table, data);
                break;
            case 's':
                scanf("%d", &data);
                tableSearch(table, data);
                break;
            case 'e':
                flag = FALSE;
                break;
        }
    }
    Free(table);
}

/*
7 3
i 17011112
i 17012345
i 17012687
s 17011111
e


13 10
i 16110243
i 17011111
i 17012331
i 17012354
i 17013672
i 16012342
s 17012354
i 15013986
i 102067
i 113478
i 14012322
s 16110243
e

*/