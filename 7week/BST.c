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
void makeLeftSubTree(Node* root, Node* node) { root->leftChild = node; }
void makeRightSubTree(Node* root, Node* node) { root->rightChild = node; }
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

void BSTInit(Node** root) { *root = NULL; }
void BSTInsert(Node** root, int key) {
    Node* cNode = *root;  // current node
    Node* pNode = NULL;   // cNode 부모노드
    Node* newNode;        //

    while (cNode != NULL) {         // 빈 공간 찾기
        if (getData(cNode) == key)  // 중복키
            return;
        pNode = cNode;              // 부모를 항상 유지
        if (key < getData(cNode)) {
            cNode = getLeftSubTree(cNode);
        } else {
            cNode = getRightSubTree(cNode);
        }
    }
    newNode = makeNode();
    setData(newNode, key);

    if (pNode != NULL) {  // 새로운 노드가 루트가 아닌 ㄱ ㅕㅇ우
        if (key < getData(pNode)) {
            makeLeftSubTree(pNode, newNode);
        } else {
            makeRightSubTree(pNode, newNode);
        }
    } else {  // 새로운 노드가 루트인경우
        *root = newNode;
    }
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
    return delNode;
}

int main() {
    // Node* root;
    // Node* result;
    // char cal;
    // int key;
    // int flag = TRUE;

    // BSTInit(&root);

    // while (flag) {
    //     scanf("%c", &cal);
    //     getchar();
    //     switch (cal) {
    //         case 'i':  // insert
    //             scanf("%d", &key);
    //             getchar();
    //             BSTInsert(&root, key);
    //             break;

    //         case 'd':  // delete
    //             scanf("%d", &key);
    //             getchar();
    //             result = BSTRemove(&root, key);
    //             if (result == NULL) {  // no such key
    //                 printf("X\n");
    //             } else {
    //                 printf("%d\n", getData(result));
    //             }
    //             free(result);
    //             break;

    //         case 's':  // search
    //             scanf("%d", &key);
    //             getchar();
    //             result = BSTSearch(root, key);
    //             if (result == NULL) {  // no such key
    //                 printf("X\n");
    //             } else {
    //                 printf("%d\n", getData(result));
    //             }
    //             break;

    //         case 'p':  // preorder
    //             preorder(root);
    //             printf("\n");
    //             break;

    //         case 'q':  // quit
    //             flag = FALSE;
    //             break;
    //     }
    // }

    // Node * avlRoot;
	// Node * clNode;		// current left node
	// Node * crNode;		// current right node
	// BSTInit(&avlRoot);

	// BSTInsert(&avlRoot, 1);
	// BSTInsert(&avlRoot, 2);
	// BSTInsert(&avlRoot, 3);
	// BSTInsert(&avlRoot, 4);
	// BSTInsert(&avlRoot, 5);
	// BSTInsert(&avlRoot, 6);
	// BSTInsert(&avlRoot, 7);
	// BSTInsert(&avlRoot, 8);
	// BSTInsert(&avlRoot, 9);

	// printf("��Ʈ ���: %d \n", getData(avlRoot));

	// clNode = getLeftSubTree(avlRoot);
	// crNode = getRightSubTree(avlRoot);
	// printf("����1: %d, ������1: %d \n", getData(clNode), getData(crNode));

	// clNode = getLeftSubTree(clNode);
	// crNode = getRightSubTree(crNode);
	// printf("����2: %d, ������2: %d \n", getData(clNode), getData(crNode));

	// clNode = getLeftSubTree(clNode);
	// crNode = getRightSubTree(crNode);
	// printf("����3: %d, ������3: %d \n", getData(clNode), getData(crNode));

	// clNode = getLeftSubTree(clNode);
	// crNode = getRightSubTree(crNode);
	// printf("����4: %d, ������4: %d \n", getData(clNode), getData(crNode));
	return 0;
}