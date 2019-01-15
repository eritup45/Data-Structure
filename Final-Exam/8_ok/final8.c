#include<stdio.h>
#include<string.h>
#define INF 1000000
typedef struct{
    int s, n, w;
}Edge;

typedef struct{
    int pre;
    int key;
    int visit;
}Graph;

void SWAP(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void cmp_key(Graph graph[], int adjM[][100], int msize, int cur){
    int i=0;
    for(i=0; i<msize; i++){
        if(adjM[cur][i] != 0){
            if(adjM[cur][i] < graph[i].key){
                graph[i].key = adjM[cur][i];
                graph[i].pre = cur;
            }
        }
    }
}

void add_least_key(Graph graph[], int *cur, int msize, Edge edgeSet[], int *en){
    int i=0, j=0;
    int min = INF, minP;
    for(i=0; i<msize; i++){ //@@
        if(graph[i].visit != 1){
            if(graph[i].key < min){
                min = graph[i].key;
                minP = i;
            }
        }
    }
    graph[minP].visit = 1;
    if(min == INF){
        //printf("min == %d, minP == %d", min, minP+1);
        printf("no spanning tree");
    }
    else{
        edgeSet[*en].s = graph[minP].pre;
        edgeSet[*en].n = minP;
        if(edgeSet[*en].s > edgeSet[*en].n)
            SWAP(&edgeSet[*en].s, &edgeSet[*en].n);
        edgeSet[(*en)++].w = graph[minP].key;
        *cur = minP;    //@@
    }
}

void prim(int adjM[][100], int msize, int startP){
    int i=0, j=0, cur, en=0;
    Graph graph[1000];
    Edge edgeSet[msize];
    for(i=0; i<msize; i++){
        graph[i].pre = -1;
        graph[i].key = INF;
        graph[i].visit = 0;
    }
    cur = startP;
    graph[startP].visit = 1;    //@@
    graph[startP].key = 0;
    cmp_key(graph, adjM, msize, cur);
    for(i=0; i<msize-1; i++){ //<(@w@)>
        add_least_key(graph, &cur, msize, edgeSet, &en);
        cmp_key(graph, adjM, msize, cur);
    }
    for(i=0; i<en; i++)
        printf("%d %d %d %d\n", i+1, edgeSet[i].s+1, edgeSet[i].n+1, edgeSet[i].w);
}

int main(){
    int i=0, j=0, msize, startP, min=INF;
    int adjM[100][100];
    freopen("8input_3.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &adjM[i][j]);
            if(adjM[i][j] < min && adjM[i][j]!=0){
                startP = i;
                min = adjM[i][j];
            }
        }
    }
    prim(adjM, msize, startP);
    return 0;
}
