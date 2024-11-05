#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 6

typedef struct _node {
    int data;
    int weight;
    struct _node* next;
} Node;

typedef struct _graph {
    int numOfV;   // number of vertices
    int numOfE;   // number of edges
    int** list;  // vertices array
} Graph;