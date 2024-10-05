#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* next;
} Node;

Node* listInit(Node* head) {
    head = NULL;
    return head;
}
Node* listInsert(Node* head, int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
        return head;
    }
    newnode->next = head;
    head = newnode;
    return head;
}
void listTraverse(Node* head) {
    Node* p = head;

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}
int getSizeOfList(Node* head) {
    Node* p = head;
    int cnt = 0;
    while (p != NULL) {
        cnt++;
        p = p->next;
    }
    return cnt;
}
Node* mid(Node* L, int k) {
    Node* p = L;
    for (int i = 0; i < k; i++) {
        p = p->next;
    }

    return p;
}
Node* merge(Node* L1, Node* L2) {
    Node* L;

    if (L1 == NULL) return L2;
    if (L2 == NULL) return L1;

    if (L1->data < L2->data) {
        L = L1;
        L->next = merge(L1->next, L2);
    } else {
        L = L2;
        L->next = merge(L1, L2->next);
    }

    return L;
}

Node* mergeSort(Node* L) {
    if (getSizeOfList(L) > 1) {
        Node* middle = mid(L, getSizeOfList(L) / 2 - 1);
        Node* L1 = L;
        Node* L2 = middle->next;
        middle->next = NULL;

        L1 = mergeSort(L1);
        L2 = mergeSort(L2);

        return merge(L1, L2);
    }

    return L;
}

int main() {
    Node* head;
    int n, data;

    head = listInit(head);

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        head = listInsert(head, data);
    }

    head = mergeSort(head);

    listTraverse(head);

    return 0;
}