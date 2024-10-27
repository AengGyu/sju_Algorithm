#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _treenode {
    struct _treenode* leftChild;
    struct _treenode* rightChild;
    int key;
} Node;

Node* makeNode() {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;
    return newnode;
}

void setData(Node* node, int key) { node->key = key; }

int getData(Node* node) { return node->key; }

void makeLeftSubTree(Node* root, Node* node) { 
    root->leftChild = node; 
}

void makeRightSubTree(Node* root, Node* node){
    root->rightChild = node;
}

// void changeLeftSubTree(Node* root, Node* node){
//     root->leftChild = node;
// }

// void changeRightSubTree(Node* root, Node* node){
//     root->rightChild = node;
// }

Node* getLeftSubTree(Node* root) { return root->leftChild; }

Node* getRightSubTree(Node* root) { return root->rightChild; }

Node* removeLeftSubTree(Node* root) {
    Node* delNode;
    if (root != NULL) {
        delNode = getLeftSubTree(root);
        makeLeftSubTree(root, NULL);
    }
    return delNode;
}

Node* removeRightSubTree(Node* root) {
    Node* delNode;
    if (root != NULL) {
        delNode = getRightSubTree(root);
        makeRightSubTree(root, NULL);
    }
    return delNode;
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf(" %d", root->key);
    preorder(root->leftChild);
    preorder(root->rightChild);
}

int getHeight(Node* root){ // 높이 구하기
    int left, right;

    if(root == NULL){
        return 0;
    }

    left = getHeight(getLeftSubTree(root));
    right = getHeight(getRightSubTree(root));

    if(left > right){
        return left+1;
    }
    else{
        return right+1;
    }
}

int getHeightDiff(Node* root){ // 높이 차이 계산
    if(root == NULL){
        return 0;
    }
    int leftH = getHeight(getLeftSubTree(root));
    int rightH = getHeight(getRightSubTree(root));

    return leftH - rightH; // 왼쪽으로 치우쳐지면 양수, 왼쪽으로 치우쳐지면 음수
}

Node* rotateLL(Node*root){ // LL 회전
    Node* pNode = root; // parent node
    Node* cNode = getLeftSubTree(pNode); // current node

    makeLeftSubTree(pNode,getRightSubTree(cNode));
    makeRightSubTree(cNode,pNode);
    return cNode;
}

Node* rotateRR(Node* root){ // RR 회전
    Node* pNode = root;// parent node
    Node* cNode = getRightSubTree(pNode); // current node

    makeRightSubTree(pNode,getLeftSubTree(cNode));
    makeLeftSubTree(cNode,pNode);

    return cNode;
}

Node* rotateLR(Node* root){ // LR 회전
    Node* pNode = root;
    Node* cNode = getLeftSubTree(pNode);

    makeLeftSubTree(pNode,rotateRR(cNode)); // RR회전 후
    return rotateLL(pNode); // LL회전
}

Node* rotateRL(Node* root){
    Node* pNode = root;
    Node* cNode = getRightSubTree(pNode);

    makeRightSubTree(pNode, rotateLL(cNode)); // LL회전 후
    return rotateRR(pNode); // RR 회전
}

Node* reBalance(Node** root){
    int diff = getHeightDiff(*root);

    if(diff > 1){ // LL or LR
        if(getHeightDiff(getLeftSubTree(*root))>0){ // LL
            *root = rotateLL(*root);
        }
        else{ // LR
            *root = rotateLR(*root);
        }
    }
    if(diff < -1){ // RR or RL
        if(getHeightDiff(getRightSubTree(*root))<0){ // RR
            *root = rotateRR(*root);
        }
        else{ // RL
            *root = rotateRL(*root);
        }
    }

    return *root;
}

void BSTInit(Node** root) { *root = NULL; }

Node* BSTInsert(Node** root,int key){
    if(*root == NULL){ // base case
        *root = makeNode();
        setData(*root,key);
    }
    else if(key < getData(*root)){
        Node* left = getLeftSubTree(*root);
        BSTInsert(&left, key);
        *root = reBalance(root);
    }
    else if(key > getData(*root)){
        Node* right = getRightSubTree(*root);
        BSTInsert(&right,key);
        *root = reBalance(root);
    }
    else{
        return NULL; // 중복 키
    }

    return *root;
}

Node* BSTSearch(Node* root, int key) {
    Node* cNode = root;

    while (cNode != NULL) {
        if (getData(cNode) == key) {
            return cNode;
        } else if (key < getData(cNode)) {
            cNode = getLeftSubTree(cNode);
        } else {
            cNode = getRightSubTree(cNode);
        }
    }
    return NULL;  // no such key
}

Node* BSTRemove(Node** root, int key) {
    Node* tmpRoot = makeNode();  // 가상 루트
    Node* cNode = *root;         // current node
    Node* pNode = tmpRoot;
    Node* delNode;
    makeRightSubTree(tmpRoot,
                     *root);  // 가상 루트의 오른쪽 자식을 실제 루트로 지정

    while (cNode != NULL && getData(cNode) != key) {  // 삭제할 노드 찾기
        pNode = cNode;

        if (key < getData(cNode)) {
            cNode = getLeftSubTree(cNode);
        } else {
            cNode = getRightSubTree(cNode);
        }
    }

    if (cNode == NULL) { // no such key
        return NULL;
    }
    delNode = cNode;

    if (getLeftSubTree(delNode) == NULL &&
        getRightSubTree(delNode) == NULL) {  // 삭제할 노드가 자식이 없는 경우
        if (getLeftSubTree(pNode) == delNode) {
            removeLeftSubTree(pNode);
        } else {
            removeRightSubTree(pNode);
        }
    } else if (getLeftSubTree(delNode) == NULL ||
               getRightSubTree(delNode) ==
                   NULL) {  // 삭제할 노드가 자식이 하나인 경우
        Node* dcNode;       // deleteNode 의 childNode

        if (getLeftSubTree(delNode) != NULL) {  // 왼쪽 자식이 있는 경우
            dcNode = getLeftSubTree(delNode);
        } else {  // 오른쪽 자식이 있는 경우
            dcNode = getRightSubTree(delNode);
        }

        if (getLeftSubTree(pNode) == delNode) {  // 삭제할 노드가 왼쪽 자식이면
            makeLeftSubTree(pNode, dcNode);
        } else {  // 삭제할 노드가 오른쪽 자식인 경우
            makeRightSubTree(pNode, dcNode);
        }
    } else {  // 삭제할 노드의 자식이 두 개인 경우
        Node* mNode = getRightSubTree(
            delNode);  // 대체 노드, 삭제할 노드의 오른쪽부터 시작해서 왼쪽으로
                       // 가서 중위후계자를 찾음
        Node* mpNode = delNode;  // 대체 노드의 부모 노드
        int delkey;

        while (getLeftSubTree(mNode) != NULL) {  // 중위 후계자 찾기
            mpNode = mNode;
            mNode = getLeftSubTree(mNode);
        }
        delkey = getData(delNode);
        setData(delNode,
                getData(mNode));  // 삭제할 노드의 값을 대체 노드의 값으로 변경

        if (getLeftSubTree(mpNode) == mNode) {  // 대체노드가 왼쪽 자식인 경우
            makeLeftSubTree(mpNode, getRightSubTree(mNode));
        } else {
            makeRightSubTree(
                mpNode,
                getRightSubTree(mNode));  // 둘 다 오른쪽 서브트리를 자식으로
                                          // 하는 이유는 왼쪽이 있었으면 중위
                                          // 후계자 찾을 때 더 내려갔을 것임
        }

        delNode = mNode;
        setData(delNode, delkey);
    }

    if (getRightSubTree(tmpRoot) != *root) {  // 루트가 바뀌었으면
        *root = getRightSubTree(tmpRoot);     // 바뀐 루트로 변경
    }

    free(tmpRoot);
    *root = reBalance(root);
    return delNode;
}

int main() {
    Node* root;
    Node* result;
    char cal;
    int key;
    int flag = TRUE;

    BSTInit(&root);

    while (flag) {
        scanf("%c", &cal);
        getchar();
        switch (cal) {
            case 'i':  // insert
                scanf("%d", &key);
                getchar();
                BSTInsert(&root, key);
                break;

            case 'd':  // delete
                scanf("%d", &key);
                getchar();
                result = BSTRemove(&root, key);
                if (result == NULL) {  // no such key
                    printf("X\n");
                } else {
                    printf("%d\n", getData(result));
                }
                free(result);
                break;

            case 's':  // search
                scanf("%d", &key);
                getchar();
                result = BSTSearch(root, key);
                if (result == NULL) {  // no such key
                    printf("X\n");
                } else {
                    printf("%d\n", getData(result));
                }
                break;

            case 'p':  // preorder
                preorder(root);
                printf("\n");
                break;

            case 'q':  // quit
                flag = FALSE;
                break;
        }
    }
}