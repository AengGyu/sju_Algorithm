    #include <stdio.h>
    #include <stdlib.h>

    #define TRUE 1
    #define FALSE 0
    #define MAX 6

    typedef struct _graph {
        int numOfV;   // number of vertices
        int numOfE;   // number of edges
        int** matrix;  // vertices array
    } Graph;

    void graphInit(Graph* pg, int numOfV) {
        // 0번 인덱스 버려놓고 1번 인덱스부터 사용
        pg->matrix = (int**)malloc(sizeof(int*)*(numOfV+1));

        pg->numOfV = numOfV;
        pg->numOfE = 0;

        for (int i = 1; i <= numOfV; i++) {
            pg->matrix[i]=(int*)malloc(sizeof(int)*(numOfV+1));
            for(int j=1; j<=numOfV;j++){
                pg->matrix[i][j] = 0;
            }
        }
    }
    //간선 추가 or 가중치 변경
    void changeWeight(Graph* pg, int from, int to, int weight) {
        // 범위 밖 입력
        if ((from < 1 || from > MAX) || (to < 1 || to > MAX)) {
            printf("-1\n");
            return;
        }
        pg->matrix[from][to] = weight;
        pg->matrix[to][from] = weight;
    } 
    void showVertexInfo(Graph* pg, int vertextNum) {
        if (vertextNum < 1 || vertextNum > MAX) {
            printf("-1\n");
            return;
        }
        for(int i=1;i<=pg->numOfV;i++){
            if(pg->matrix[vertextNum][i] != 0){
                printf(" %d %d",i,pg->matrix[vertextNum][i]);
            }
        }
        printf("\n");
    }
    void removeEdge(Graph* pg, int from, int to) {
        // 범위 밖 입력
        if ((from < 1 || from > MAX) || (to < 1 || to > MAX)) {
            printf("-1\n");
            return;
        }
        pg->matrix[from][to] = 0;
        pg->matrix[to][from] = 0;
    }
    void freeGraph(Graph* pg) {
        for(int i=1;i<=pg->numOfV;i++){
            free(pg->matrix[i]);
        }
        free(pg->matrix);
    }
    int main() {
        Graph graph;
        int numOfV = 6, n;
        int from, to, weight;
        int flag = TRUE;
        char cal;

        graphInit(&graph, numOfV);

        changeWeight(&graph, 1, 2, 1);
        changeWeight(&graph, 1, 3, 1);
        changeWeight(&graph, 1, 4, 1);
        changeWeight(&graph, 1, 6, 2);
        changeWeight(&graph, 2, 3, 1);
        changeWeight(&graph, 3, 5, 4);
        changeWeight(&graph, 5, 5, 4);
        changeWeight(&graph, 5, 6, 3);

        while (flag) {
            scanf(" %c", &cal);
            switch (cal) {
                case 'a':
                    scanf("%d", &n);
                    showVertexInfo(&graph, n);
                    break;
                case 'm':
                    scanf("%d %d %d", &from, &to, &weight);
                    // weight == 0 인 경우는 기존 간선을 삭제
                    if (weight == 0) {
                        removeEdge(&graph, from, to);
                    }
                    else{
                        changeWeight(&graph,from,to,weight);
                    }
                    break;
                case 'q':
                    flag = FALSE;
                    break;
            }
        }
        freeGraph(&graph);
        return 0;
    }


    /*
    a 2
    m 4 2 3
    a 2       
    q

    1 1 3 1
    1 1 3 1 4 3

    a 5
    m 3 5 0
    a 5    
    a 7   
    q

    3 4 5 4 6 3 
    5 4 6 3
    -1
    */