#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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
// 높이
int getHeight(Node* root) {
    int left;
    int right;

    if (root == NULL) {
        return 0;
    }

    left = getHeight(root->left);
    right = getHeight(root->right);

    if (left > right) {
        return left + 1;
    } else {
        return right + 1;
    }
}
// 균형 인수
int getDiff(Node* root) {
    int left;
    int right;

    if (root == NULL) {
        return 0;
    }

    left = getHeight(root->left);
    right = getHeight(root->right);

    return left - right;
}
// LL회전
Node* rotateLL(Node* root) {
    Node* pNode = root;
    Node* cNode = root->left;

    pNode->left = cNode->right;
    cNode->right = pNode;

    return cNode;
}
// RR회전
Node* rotateRR(Node* root) {
    Node* pNode = root;
    Node* cNode = root->right;

    pNode->right = cNode->left;
    cNode->left = pNode;

    return cNode;
}
// LR회전
Node* rotateLR(Node* root) {
    Node* pNode = root;
    Node* cNode = root->left;

    pNode->left = rotateRR(cNode);
    // cNode = rotateRR(cNode); << 이렇게 하게 되면 cNode 값만 바뀌고 pNode엔 변경이 적용이 안 될 수 있음, 부모 노드의 자식을 갱신 해야됨
    return rotateLL(pNode);
}
// RL회전
Node* rotateRL(Node* root) {
    Node* pNode = root;
    Node* cNode = root->right;

    pNode->right = rotateLL(cNode);
    // cNode = rotateLL(cNode);
    return rotateRR(pNode);
}
Node* reBalance(Node* root) {
    int diff = getDiff(root);

    // LL or LR
    if (diff > 1) {
        // LL
        if (getDiff(root->left) >= 0) {
            root = rotateLL(root);
        }
        // LR
        else {
            root = rotateLR(root);
        }
    }
    // RR or RL
    else if (diff < -1) {
        // RR
        if (getDiff(root->right) <= 0) {
            root = rotateRR(root);
        }
        // RL
        else {
            root = rotateRL(root);
        }
    }
    return root;
}
// 노드 삽입
Node* BSTInsert(Node* root, int data) {
    if (root == NULL) {
        root = makeNode(data);
        return root;
    } else if (data < root->data) {
        root->left = BSTInsert(root->left, data);
    } else if (data > root->data) {
        root->right = BSTInsert(root->right, data);
    }
    return reBalance(root);
}
// 탐색
Node* BSTSearch(Node* root, int data) {
    Node* cNode = root;

    while (cNode != NULL) {
        if (cNode->data == data) {  // 일치하는 노드를 찾으면 return
            return cNode;
        } else if (data < cNode->data) {
            cNode = cNode->left;
        } else {
            cNode = cNode->right;
        }
    }

    return NULL;  // while문에서 return 된 게 아니면 해당 데이터 값은 없음
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
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // only right child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // only left child
        else if (root->right == NULL) {
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
    return reBalance(root);
}
// 전위순회
void preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf(" %d", root->data);
    preorder(root->left);
    preorder(root->right);
}
void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main() {
    Node* root = NULL;
    Node* result;
    char cal;
    int data, flag = TRUE;

    while (flag) {
        scanf(" %c", &cal);

        switch (cal) {
            case 'i':
                scanf("%d", &data);
                root = BSTInsert(root, data);
                break;
            case 's':
                scanf("%d", &data);
                result = BSTSearch(root, data);
                if (result != NULL) {
                    printf("%d\n", result->data);
                } else {
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
    freeTree(root);
    return 0;
}

/*
i 9
i 31
i 66
i 30
i 1
s 30
i 24
p
s 47
i 61
d 30
i 13
q
*/