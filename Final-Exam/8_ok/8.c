#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INF 0x3fffffff  //range of int

//edge
typedef struct{
    int vstart; //start
    int vnext;
    int weight;
}Edge;

//help algorithm
typedef struct
{
    int predecessor;    //�s�����I���e�@���I
    int key;            //�e�@�I�P���I��weight(�Z��)
    int visited;        //record whether visited or not
}Graph;

void SWAP(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void get_adjM(int adjM[][100], int *totLine, int *startP){
    int i=0, j=0, min=10000;
    int tot;
    FILE *fp = fopen("8input_2.txt", "r");
    fscanf(fp, "%d", &tot);
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            fscanf(fp, "%d", &adjM[i][j]);
            if(adjM[i][j] != 0 && adjM[i][j] < min){
                *startP = i;
                min = adjM[i][j];
            }
        }
    }
    *totLine = tot;
    fclose(fp);
}

//�p�Gweight��key[X]�p�A�K��spredecessor[X]��vertex(2)�A�åB��key[X]��s��weight(2,X)
void compare_key(Graph graphJudge[], int tot, int cur, int adjM[][100]){
    int j=0;
    for(j=0; j<tot; j++){   //�䤣��0��weight
        if(adjM[cur][j] != 0){
            if(adjM[cur][j] < graphJudge[j].key){
                graphJudge[j].key = adjM[cur][j];
                graphJudge[j].predecessor = cur;
            }
        }
    }
    return;
}

void add_least_key(Graph graphSet[], int tot, int *cur, Edge edgeSet[], int *edgeNum){
    int i=0, j=0;
    int min = INF, minP;
    for(i=0; i<tot; i++){
        if(graphSet[i].visited != 1){
            if(graphSet[i].key < min){
                min = graphSet[i].key;
                minP = i;
            }
        }
    }
    graphSet[minP].visited = 1;
    if(min == INF)
        printf("No spanning tree\n");
    else{
        edgeSet[*edgeNum].vstart = graphSet[minP].predecessor;  //@@
        edgeSet[*edgeNum].vnext = minP;
        if(edgeSet[*edgeNum].vstart > edgeSet[*edgeNum].vnext)  //�ѰO���D��
            SWAP(&edgeSet[*edgeNum].vstart, &edgeSet[*edgeNum].vnext);

        edgeSet[(*edgeNum)++].weight = graphSet[minP].key;
        *cur = minP;    //@@
    }
}

int main(){
    int i=0, j=0;
    int startP;
    int adjM[100][100], totLine;

    Edge edgeSet[10000];
    int edgeNum = 0;

    get_adjM(adjM, &totLine, &startP);

    Graph graphSet[totLine];
    for(i=0; i<totLine; i++){
        graphSet[i].predecessor = -1;
        graphSet[i].key = INF;
        graphSet[i].visited = 0;
    }
    graphSet[startP].key = 0;   //@@
    graphSet[startP].visited = 1;

    int cur = startP;
    compare_key(graphSet, totLine, cur, adjM);
    for(i=0; i<totLine-1; i++){ //@@
        add_least_key(graphSet, totLine, &cur, edgeSet, &edgeNum);
        compare_key(graphSet, totLine, cur, adjM);
    }

    for(i=0; i<edgeNum; i++)
        printf("%d %d %d %d\n", i+1, edgeSet[i].vstart+1, edgeSet[i].vnext+1, edgeSet[i].weight);
    return 0;
}
