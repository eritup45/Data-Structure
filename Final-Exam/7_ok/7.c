#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 1000000

void find_parent(int end, int *parent){
    if(end != parent[end])
        find_parent(parent[end], parent);
    printf("%d ", end+1);
}

void dijkstra(int start, int end, int tot, int adjM[][100]){
    int i=0;
    int index;
    int dist[tot], visited[tot];
    memset(visited, 0, sizeof(visited));
    memset(dist, INF, sizeof(dist));
    dist[start] = 0;
    int parent[tot];
    parent[start] = start;
    while(1){
        index = -1;
        for(i=0; i<tot; i++){
            if( visited[i] == 0 && ( index == -1 || dist[i] < dist[index] )){
                index = i;
            }
        }
        if(index == -1) break;
        visited[index] = 1;
        for(i=0; i<tot; i++){
            if(dist[index] + adjM[index][i] < dist[i]){
                dist[i] = dist[index] + adjM[index][i];
                parent[i] = index;
            }
        }
    }
    if(dist[end] == INF){
        printf("nope -1");
        return;
    }
    find_parent(end, parent);
}

int main(){
    int i=0, j=0, msize;
    int start, end, adjM[100][100];
    FILE *fp = freopen("7input_3.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &adjM[i][j]);
            if(adjM[i][j] == 0)
                adjM[i][j] = INF;
        }
    }
    scanf("%d %d", &start, &end);
    start--; end--;
    dijkstra(start, end, msize, adjM);
    fclose(fp);
}
