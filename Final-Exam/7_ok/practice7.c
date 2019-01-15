#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 1000000
void find_parent(int end, int parent[]){
    if(end != parent[end])
        find_parent(parent[end], parent);
    printf("%d ", end + 1);
}
void dijkstra(int start, int end, int adjM[][100], int msize){
    int i=0;
    int index;
    int dist[msize], visit[msize];
    memset(dist, INF, sizeof(dist));
    memset(visit, 0, sizeof(visit));
    int parent[msize];
    parent[start] = start;
    dist[start] = 0;
    //visit[start] = 1; //@@
    while(1){   //@@
        index = -1;
        for(i=0; i<msize; i++){
            if(visit[i] == 0 && ( index==-1 || dist[i] < dist[index] )){    //@@
                index = i;
            }
        }
        if(index == -1) break;
        visit[index] = 1;
        for(i=0; i<msize; i++){
            if(dist[index] + adjM[index][i] < dist[i]){
                dist[i] = dist[index] + adjM[index][i]; //@@
                parent[i] = index;
            }
        }
    }
    if(dist[end] == INF){
        printf("-1\n");
        return ;
    }
    find_parent(end, parent);

}

int main(){
    int i=0, j=0, msize, start, end;
    int adjM[100][100];
    freopen("7input_3.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &adjM[i][j]);
            if(adjM[i][j] == 0) //@@
                adjM[i][j] = INF;
        }
    }
    scanf("%d %d", &start, &end);
    start--; end--;
    dijkstra(start, end, adjM, msize);
    return 0;
}
