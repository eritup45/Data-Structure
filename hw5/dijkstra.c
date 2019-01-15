#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 1000000
typedef struct{
    int vstart; //start
    int vnext;
    int weight;
}edge;

int dist[10000];    // dist[] -- the distance from the ith node to the source node
int visited[10000];
int **adjM;         // adjM[][] -- adjacency matrix, adjM[from][to] == weight
int tot;            // tot -- tot nodes

int **get_adjMatrix(){
    int i=0, j=0, totLine=0;
    char line[1024];
    /*printf("Please input file name:");
    scanf("%s", line);
    FILE *fp = fopen(line, "r");*/
    FILE *fp = fopen("input3.txt", "r");
    fscanf(fp, "%d", &totLine);

    int *pData;
    adjM = (int**)malloc(totLine*sizeof(int *));
    pData = (int*)malloc(totLine*totLine*sizeof(int));
    for(i = 0; i < totLine; i++, pData += totLine)
        adjM[i] = pData;

    for(i=0; i<totLine; i++){
        for(j=0; j<totLine; j++){
            fscanf(fp, "%d", &adjM[i][j]);
            if(adjM[i][j] == 0){
                adjM[i][j] = INF;
            }
        }
    }

    tot = totLine;
    fclose(fp);
    return adjM;
}

//若要找出某一點的最短路徑，就可以利用parent陣列了。
void find_path(int x, int *parent)  //印出由起點到x點的最短路徑
{
    if (x != parent[x]) //先把之前的路徑都印出來
        find_path(parent[x], parent);
    printf("%d ", x + 1);  //再把現在的位置印出來
}

//return the shortest cost from start to end
int dijkstra(int start, int end){
    int i=0;
    int index;
    int parent[tot];    //記錄各個點在最短路徑樹上的父親是誰
    parent[start] = start;

    memset(dist, INF, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;

    //renew all dist[] once, and mark the visited point
    while(1){
        index = -1;
        //find the shortest distance from the unvisited vertex
        for(i=0; i<tot; i++){
                //not visited        //first loop or has shortest cost
            if((visited[i] == 0) && ((index == -1) || (dist[i] < dist[index]) )){
                index = i;
            }
        }
        //all visited or can't build
        if(index == -1) break;
        visited[index] = 1;
        for(i=0; i<tot; i++){
            if(dist[index] + adjM[index][i] < dist[i]){
                dist[i] = dist[index] + adjM[index][i];
                parent[i] = index;
            }
        }
    }
    if(dist[end] == INF)    //the shortest path is not exist
        return -1;
    printf("The path:");
    find_path(end, parent);
    printf("\n");
    return dist[end];
}

int main(){
    int i=0, j=0;
    int start, end, cost;
    adjM = get_adjMatrix();
    printf("Enter two vertices<start end>:");
    scanf("%d %d", &start, &end);
    start--;    end--;

    cost = dijkstra(start, end);

    printf("The cost from %d to %d is : %d\n", start+1, end+1, cost);
    return 0;
}
