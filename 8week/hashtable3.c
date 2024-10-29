#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _hashTable {
    int* arr;
    int size;
    int q;
} HashTable;

HashTable* tableInit(int size,int q) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));

    table->size = size;
    table->q = q;

    table->arr = (int*)calloc(sizeof(int), size);

    return table;
}
int hash(int data, int size) { return data % size; }
int hash_2(int data, int q) { return q - (data % q); }
void tableInsert(HashTable* table, int data) {
    int hashValue = hash(data, table->size);

    while (table->arr[hashValue]) {  // 해당 인덱스에 값이 있으면
        hashValue = (hashValue + hash_2(data,table->q)) % table->size;
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
        hashValue = (hashValue + hash_2(data,table->q)) % table->size;
    }
    printf("-1\n");
    return;
}
void tableTraverse(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        printf(" %d", table->arr[i]);
    }
    printf("\n");
}
void Free(HashTable* table) {
    free(table->arr);
    free(table);
}

int main() {
    int size, n, q;
    char cal;
    int flag = TRUE;
    HashTable* table;
    int data;

    scanf("%d %d %d", &size, &n, &q);

    table = tableInit(size,q);

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
            case 'p':
                tableTraverse(table);
                break;
            case 'e':
                tableTraverse(table);
                flag = FALSE;
                break;
        }
    }
    Free(table);
}

/*
13 10 11
i 25
i 13
i 16
i 15
i 70
p
i 28
i 31
i 20
i 14
s 20
s 27
i 38
e
*/