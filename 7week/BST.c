#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
    struct _node* leftChild;
    // struct _node * parent; 굳이 필요한가...? 없는게 더 편한거같은디
    struct _node* rightChild;
    int key;
} Node;
// 이진트리 기본 메소드
Node* makeNode() {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->leftChild = NULL;
    // newnode->parent = NULL;
    newnode->rightChild = NULL;

    return newnode;
}
int getData(Node* node) { return node->key; }
void setData(Node* node, int key) { node->key = key; }
Node* getLeftSubTree(Node* node) { return node->leftChild; }
Node* getRightSubTree(Node* node) { return node->rightChild; }
void makeLeftSubTree(Node* root, Node* node) { root->leftChild = node; }
void makeRightSubTree(Node* root, Node* node) { root->rightChild = node; }
Node* removeLeftSubTree(Node* node) {
    Node* delNode;
    if (node != NULL) {
        delNode = node->leftChild;
        node->leftChild = NULL;
    }
    return delNode;
}
Node* removeRightSubTree(Node* node) {
    Node* delNode;
    if (node != NULL) {
        delNode = node->rightChild;
        node->rightChild = NULL;
    }
    return delNode;
}
void preorder(Node* node) {
    if (node == NULL) return;
    printf(" %d", getData(node));
    preorder(node->leftChild);
    preorder(node->rightChild);
}
// 요기까지
// 이제부터 이진탐색트리 메소드
void BSTMakeAndInit(Node** root) { *root = NULL; }
void BSTInsert(Node** root, int key) {
    Node* pnode = NULL;
    Node* cnode = *root;
    Node* newnode = NULL;

    while (cnode != NULL) {
        if (getData(cnode) == key) {  // 중복키
            return;
        }
        pnode = cnode;
        if (getData(cnode) > key) {
            cnode = getLeftSubTree(cnode);
        } else {
            cnode = getRightSubTree(cnode);
        }
    }
    newnode = makeNode();
    setData(newnode, key);

    if (pnode != NULL) {  // 새로운 노드가 루트가 아닌 경우
        if (key < getData(pnode)) {  // left
            makeLeftSubTree(pnode, newnode);
        } else {  // right
            makeRightSubTree(pnode, newnode);
        }
    } else {  // 새로운 노드가 루트인 경우
        *root = newnode;
    }
}
Node* BSTSearch(Node* root, int key) {
    Node* cnode = root;
    while (cnode != NULL) {
        if (getData(cnode) == key) {
            return cnode;
        } else if (key < getData(cnode)) {
            cnode = getLeftSubTree(cnode);
        } else {
            cnode = getRightSubTree(cnode);
        }
    }

    return NULL;  // NoSuchKey
}
Node* BSTRemove(Node** root, int key){
    Node* tmpRoot = makeNode(); // 가상루트노드
    Node* pnode = tmpRoot;
    Node* cnode = *root;
    Node* delNode;

    makeRightSubTree(tmpRoot, *root); // 실제 루트를 가상의 루트의 오른쪽 자식 노드로 만들음
    
    while(cnode!=NULL && getData(cnode) != key){
        pnode = cnode;
        if(key < getData(cnode)){
            cnode = getLeftSubTree(cnode);
        }
        else{
            cnode = getRightSubTree(cnode);
        }
    }

    if(cnode == NULL){ // NoSuchKey
        return NULL;
    }

    delNode = cnode;

    if(getLeftSubTree(delNode) == NULL && getRightSubTree(delNode)==NULL){ // 삭제할 노드의 자식 노드가 없는 경우
        if(getLeftSubTree(pnode) == delNode){
            removeLeftSubTree(pnode);
        }
        else{
            removeRightSubTree(pnode);
        }
    }
    else if(getLeftSubTree(delNode)==NULL || getRightSubTree(delNode)== NULL){ // 삭제할 노드의 자식이 하나인 경우
        Node* dcNode; // delNode의 자식노드 
        
        if(getLeftSubTree(delNode) != NULL){ //자식이 왼쪽 자식인지 오른쪽 자식인지 결정
            dcNode = getLeftSubTree(delNode);
        }
        else{
            dcNode = getRightSubTree(delNode);
        }
        
        if(getLeftSubTree(pnode) == delNode){
            makeLeftSubTree(pnode,dcNode);
        }
        else{
            makeRightSubTree(pnode,dcNode);
        }
    }
    else{ // 삭제할 노드가 자식이 두 개인 경우
        Node* mNode = getRightSubTree(delNode); // 대체할 노드
        Node* mpNode = delNode; // 대체할 노드의 부모노드
        int delkey;

        while(getLeftSubTree(mNode) != NULL){ // 대체 노드 찾기
            mpNode = mNode;
            mNode = getLeftSubTree(mNode);
        }  
        delkey = getData(delNode);
        setData(delNode, getData(mNode)); // 삭제할 노드의 키값을 대체 노드의 키값으로 변경

        if(getLeftSubTree(mpNode) == mNode){
            makeLeftSubTree(mpNode,getRightSubTree(mNode));
        }
        else{
            makeRightSubTree(mpNode,getRightSubTree(mNode));
        }
        delNode = mNode;
        setData(delNode,delkey);
    }
    
    if(getRightSubTree(tmpRoot)!= *root){
        *root = getRightSubTree(tmpRoot);
    }

    free(tmpRoot);
    return delNode;
}

int main() {
    Node* root;          // BST root
    Node* searchResult;  // result of search
    char cal;            // i d s p q
    int key;
    int flag = TRUE;
    BSTMakeAndInit(&root);

    while (flag) {
        scanf("%c", &cal);
        getchar();
        switch (cal) {
            case 'i': {  // 키를 입력 받아 노드 생성 및 트리에 삽입
                scanf("%d", &key);
                getchar();
                BSTInsert(&root, key);
                break;
            }
            case 'd': {  // 입력 받은 키가 존재하면 키를 삭제하고 키 값을
                         // 출력(없으면 X 출력))
                scanf("%d", &key);
                getchar();
                searchResult= BSTRemove(&root,key);
                if (searchResult == NULL) {
                    printf("X\n");
                } else {
                    printf("%d\n", getData(searchResult));
                }
                free(searchResult);
                break;
            }
            case 's': {  // 입력 받은 키가 트리내에 존재하는지 탐색 후 키 값을
                         // 출력(없으면 X 출력)
                scanf("%d", &key);
                getchar();
                searchResult = BSTSearch(root, key);
                if (searchResult == NULL) {
                    printf("X\n");
                } else {
                    printf("%d\n", getData(searchResult));
                }
                break;
            }
            case 'p': {  // 전위순회
                preorder(root);
                printf("\n");
                break;
            }
            case 'q': {  // 종료
                flag = FALSE;
                break;
            }
        }
    }
}