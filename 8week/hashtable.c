// 분리연쇄법
// 배열의 요소는 연결리스트
// 연결리스트 배열 동적할당
// 해시테이블 구조체 선언
#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef struct _node{
    int data;
    struct _node* next;
}Node;
typedef struct _hashTable{
    Node** arr;
    int size;
}HashTable;

Node* listInsert(Node* head, int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->next = NULL;
    newnode->data = data;

    if(head == NULL){
        head = newnode;
        return head;
    }
    newnode->next = head;
    head = newnode;
    
    return head;
}

void listTraverse(Node* head){
    Node* cur = head;

    while(cur != NULL){
        printf(" %d",cur->data);
        cur = cur->next;
    }
}
//해시테이블 함수
HashTable* hashTableInit(int size){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->arr = (Node**)malloc(sizeof(Node*)*size);

    for(int i = 0;i<size;i++){
        table->arr[i] = NULL;
    }

    return table;
}
int hash(int data,int size){
    return data%size;
}
void tableInsert(HashTable* table, int data){
    int hashValue = hash(data,table->size);

    table->arr[hashValue] = listInsert(table->arr[hashValue],data);
}
void tableSearch(HashTable* table, int data){
    int hashValue = hash(data,table->size);
    Node* cur = table->arr[hashValue];
    int cnt = 1;

    while(cur != NULL){
        if(cur->data == data){
            printf("%d\n", cnt);
            return;
        }
        cnt++;
        cur = cur->next;
    }
    printf("0\n");
    return;
}
void tableRemove(HashTable* table, int data){
    int hashValue = hash(data,table->size);
    Node* cur = table->arr[hashValue];
    Node* prev = NULL;
    int cnt = 1;

    while(cur !=NULL){
        if(cur->data == data){
            printf("%d\n", cnt);
            if(prev == NULL){ //삭제할 값이 처음 데이터인 경우
                table->arr[hashValue] = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("0\n");
    return;
}
void tableTraverse(HashTable* table){
    for(int i=0;i<table->size;i++){
        listTraverse(table->arr[i]);
    }
    printf("\n");
}
int main(){
    HashTable* table;
    int size;
    char cal;
    int flag = TRUE;
    int data;

    scanf("%d",&size);

    table = hashTableInit(size);

    while(flag){
        scanf(" %c",&cal);

        switch(cal){
            case 'i': //insert
            scanf("%d",&data);
            tableInsert(table,data);
            break;
            case 's': // search
            scanf("%d",&data);
            tableSearch(table,data);
            break;
            case 'd':
            scanf("%d",&data);
            tableRemove(table,data);
            break;
            case 'p':
            tableTraverse(table);
            break;
            case 'e':
            flag = FALSE;
            break;
        }
    }
}