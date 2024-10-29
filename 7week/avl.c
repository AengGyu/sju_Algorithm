#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _treenode {
    struct _treenode* leftChild;
    struct _treenode* rightChild;
    int key;
} Node;

Node* makeNode(int key) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;
    newnode->key = key;
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

Node* reBalance(Node* root){
    int diff = getHeightDiff(root);

    if(diff > 1){ // LL or LR
        if(getHeightDiff(getLeftSubTree(root))>0){ // LL
            root = rotateLL(root);
        }
        else{ // LR
            root = rotateLR(root);
        }
    }
    if(diff < -1){ // RR or RL
        if(getHeightDiff(getRightSubTree(root))<0){ // RR
            root = rotateRR(root);
        }
        else{ // RL
            root = rotateRL(root);
        }
    }

    return root;
}

Node* BSTInsert(Node* root,int key){
    if(root == NULL){
        return makeNode(key);
    }
    if(key < getData(root)){
        root->leftChild = BSTInsert(getLeftSubTree(root),key);
    }
    else if(key > getData(root)){
        root->rightChild = BSTInsert(getRightSubTree(root),key);
    }
    return reBalance(root);
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

Node* findMin(Node* root) {
    while (root->leftChild != NULL) root = root->leftChild;
    return root;
}

Node* BSTRemove(Node* root, int key){
    if(root == NULL){
        return NULL;
    }
    if(key < getData(root)){
        root->leftChild = BSTRemove(getLeftSubTree(root),key);
    }
    else if (key > getData(root)){
        root->rightChild = BSTRemove(getRightSubTree(root),key);
    }   
    else{
        if(getLeftSubTree(root) == NULL || getRightSubTree(root)== NULL){
            Node* temp = (getLeftSubTree(root)) ? getLeftSubTree(root) : getRightSubTree(root);
            free(root);
            return temp;
        }
        else{
            Node* temp = findMin(getRightSubTree(root));
            setData(root,getData(temp));
            root->rightChild = BSTRemove(getRightSubTree(root),getData(temp));
        }
    }
    return reBalance(root);
}

int main() {
    Node* root = NULL;
    Node* result;
    char cal;
    int key;
    int flag = TRUE;

    while (flag) {
        scanf("%c", &cal);
        getchar();
        switch (cal) {
            case 'i':  // insert
                scanf("%d", &key);
                getchar();
                root = BSTInsert(root, key);
                break;

            case 'd':  // delete
                scanf("%d", &key);
                getchar();
                result = BSTSearch(root,key);
                if (result == NULL) {  // no such key
                    printf("X\n");
                } else {
                    printf("%d\n",key);
                    root = BSTRemove(root,key);
                }
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

/*
i 44
i 17
i 78
i 32
i 50
i 88
i 48
i 62
s 88
p
q
*/