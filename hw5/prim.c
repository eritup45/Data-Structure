//參考網址:http://alrightchiu.github.io/SecondRound/minimum-spanning-treeprims-algorithm.html

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INF 0x3fffffff  //range of int

//edge
typedef struct{
    int vstart; //start
    int vnext;
    int weight;
}edge;

//help algorithm
typedef struct
{                       //此點即是陣列的位置
    int predecessor;    //連接此點的前一個點
    int key;            //前一點與此點的weight
    int visited;        //record whether visited or not
}Graph;

edge edgeSet[10000];
int edgeNum = 0;
int **adjM;

int **get_adjMatrix(int *tot, int *startPosition){
    int i=0, j=0, totLine=0;
    char line[1024];
    printf("Please input file name:");
    scanf("%s", line);
    FILE *fp = fopen(line, "r");

    fscanf(fp, "%d", &totLine);

    //分配記憶體 adjM[totLine][totLine];
    //int **adjM, *pData;
    int *pData;
    adjM = (int**)malloc(totLine*sizeof(int *));
    pData = (int*)malloc(totLine*totLine*sizeof(int));
    for(i = 0; i < totLine; i++, pData += totLine)
        adjM[i] = pData;

    for(i=0; i<totLine; i++){
        for(j=0; j<totLine; j++){
            fscanf(fp, "%d", &adjM[i][j]);
        }
    }

    *tot = totLine;
    fscanf(fp, "%d", startPosition);    //startPosition is a pointer, so & is no needed
    fclose(fp);
    return adjM;
}

//如果weight比key[X]小，便更新predecessor[X]成vertex(2)，並且把key[X]更新成weight(2,X)
void compare_key(Graph graphJudge[], int tot, int cur){
    int i=0, j=-1;

    for(j=0; j<tot; j++){
        if(adjM[cur][j]!=0){    //找不為0的weight
            if(adjM[cur][j] < graphJudge[j].key){
                graphJudge[j].key = adjM[cur][j];
                graphJudge[j].predecessor = cur;
            }
        }
    }

    return;
}
//選取key[]值最小的vertex放進edgeSet, 並且標記
void add_least_key(Graph graphJudge[], int tot, int *cur){
    int i=0, j=0, min=INF, minPosition;
    for(i=0; i<tot; i++){   //find least key's position
        if(graphJudge[i].visited != 1){
            if(graphJudge[i].key < min){
                min = graphJudge[i].key;
                minPosition = i;
            }
        }
    }
    if(min == INF)
        printf("No spanning tree\n");
    else{
        graphJudge[minPosition].visited = 1;
        edgeSet[edgeNum].vstart = graphJudge[minPosition].predecessor;
        edgeSet[edgeNum].vnext = minPosition;
        edgeSet[edgeNum++].weight = graphJudge[minPosition].key;
        *cur = minPosition;
    }

}

int main(){
    int tot, startPosition, cur, i=0, j=0;

    //edge edgeSet[10000];
    //int edgeNum = 0;
    //int **adjM;
    adjM = get_adjMatrix(&tot, &startPosition);
    startPosition--;
    Graph graphJudge[tot];
    for(i=0; i<tot; i++){
        graphJudge[i].predecessor = -1;
        graphJudge[i].key = INF;
        graphJudge[i].visited = 0;
    }
    graphJudge[startPosition].key = 0;
    graphJudge[startPosition].visited = 1;

    cur = startPosition;
    compare_key(graphJudge, tot, cur);
    for(i=0; i<tot-1; i++){
        add_least_key(graphJudge, tot, &cur);
        compare_key(graphJudge, tot, cur);
    }
    int weight = 0;
    for(i=0; i<tot-1; i++){
        printf("Edge %d:<%d %d> cost:%d\n", i+1, edgeSet[i].vstart+1, edgeSet[i].vnext+1, edgeSet[i].weight);
        weight += edgeSet[i].weight;
    }
    printf("Minimum cost=%d\n",weight);

    return 0;
}

