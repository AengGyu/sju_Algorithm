#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef struct _treeNode {
    int data;
    struct _treeNode* left;
    struct _treeNode* right;
} Node;

// 노드 생성
Node* makeNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 노드 삽입
Node* BSTInsert(Node* root, int data){
    Node* cNode = root; // current node
    Node* pNode = NULL; // parent node of cNode

    // 삽입할 위치를 찾아놓기
    while(cNode != NULL){ 
        if(data == cNode->data)
            return root;
        pNode = cNode;
        if(data < cNode->data){
            cNode = cNode->left;
        }
        else{
            cNode = cNode->right;
        }
    }

    Node* newNode = makeNode(data);

    // 삽입 위치가 루트인 경우
    if(pNode == NULL){
        root = newNode;
        return root;
    }
    
    // 데이터가 작으면 왼쪽에 달고 크면 오른쪽에 달기
    // cNode == pNode->left 이런식으로 조건을 달면 안됨 주의 
    if(data < pNode->data){
        pNode->left = newNode;
    }
    else{
        pNode->right = newNode;
    }
    return root;
}
// 탐색
Node* BSTSearch(Node* root, int data){
    Node* cNode = root;

    while(cNode!=NULL){
        if(cNode->data == data){ // 일치하는 노드를 찾으면 return
            return cNode;
        }
        else if(data<cNode->data){
            cNode = cNode->left;
        }
        else{
            cNode = cNode->right;
        }
    }

    return NULL; // while문에서 return 된 게 아니면 해당 데이터 값은 없음
}
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}
// 삭제
Node* BSTDelete(Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    if (data < root->data) {
        root->left = BSTDelete(root->left, data);
    } else if (data > root->data) {
        root->right = BSTDelete(root->right, data);
    } else {
        // no child
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        // only right child
        else if(root->left == NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // only left child
        else if(root->right == NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // left, right child
        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = BSTDelete(root->right, temp->data);
        }
    }
    return root;
}
// 전위순회
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    printf(" %d", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main(){
    Node* root = NULL;
    Node* result;
    char cal;
    int data, flag = TRUE;

    while(flag){
        scanf(" %c",&cal);

        switch(cal){
            case 'i':
                scanf("%d",&data);
                root = BSTInsert(root,data);
                break;
            case 's':
                scanf("%d",&data);
                result = BSTSearch(root,data);
                if(result != NULL){
                    printf("%d\n", result->data);
                }
                else{
                    printf("X\n");
                }
                break;
            case 'd':
                scanf("%d", &data);
                if (BSTSearch(root, data) != NULL) {
                    printf("%d\n", data);
                    root = BSTDelete(root, data);
                } else {
                    printf("X\n");
                }
                break;
            case 'p':
                preorder(root);
                printf("\n");
                break;
            case 'q':
                flag = FALSE;
                break;
        }
    }

    return 0;
}

/*
i 9
i 2
i 15
i 1
i 7
i 11
i 5
i 8
i 3
i 4
p
d 2
d 13
p
q
*/