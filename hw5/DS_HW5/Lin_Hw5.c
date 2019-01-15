#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max 100
#define INF (~(0x1 << 31)) // 0X7FFFFFFF
#define IN 999
int map[100][100], all = 0;
typedef struct _EdgeData
{
    int start;
    int end;
    int weight;
} EData;
typedef struct _graph
{
    int vexs[Max]; // store the vex
    int vexnum;
    int edgnum;
    int matrix[Max][Max];
} Graph, *PGraph;
int get_position(Graph G, int k) //get the option
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == k)
            return i;
    return -1;
}
void sorted_edges(EData *edges, int n) //sort the edge
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                EData tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}
void prim(Graph G, int start) //use prim
{
    int min, i, j, k, m, n, sum, head, tail;
    int index = 0;
    char prims[Max];
    int weights[Max];
    start -= 1;
    prims[index++] = G.vexs[start];
    for (i = 0; i < G.vexnum; i++)
        weights[i] = G.matrix[start][i];
    weights[start] = 0;
    for (i = 0; i < G.vexnum; i++)
    {
        if (start == i)
            continue;
        j = 0;
        k = 0;
        min = INF;
        while (j < G.vexnum)
        {
            if (weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                k = j;
            }
            j++;
        }
        prims[index++] = G.vexs[k];
        weights[k] = 0;
        for (j = 0; j < G.vexnum; j++)
            if (weights[j] != 0 && G.matrix[k][j] < weights[j])
                weights[j] = G.matrix[k][j];
    }
    sum = 0;
    printf("\n\nThe output is\n\n");
    for (i = 1; i < index; i++)
    {
        min = INF;
        n = get_position(G, prims[i]);
        for (j = 0; j < i; j++)
        {
            m = get_position(G, prims[j]);
            if (G.matrix[m][n] < min)
            {
                min = G.matrix[m][n];
                head = m;
                tail = n;
            }
        }
        sum += min;
        printf("Edge %d: <%d,%d> cost: %d\n", i, G.vexs[head], G.vexs[tail], min);
    }
    printf("Minumum cost= %d\n", sum);
}
Graph *read_graph(int Op, FILE *fptr)
{
    int i, j, v, root;
    Graph *PG = malloc(sizeof(Graph));
    PG->edgnum = 0; //initialize
    fscanf(fptr, "%d", &PG->vexnum);
    for (i = 0; i <= PG->vexnum; i++)
        PG->vexs[i] = i + 1;
    for (i = 0; i < PG->vexnum; i++)
    {
        for (j = 0; j < PG->vexnum; j++)
        {
            fscanf(fptr, "%d", &PG->matrix[i][j]);
            if (i != j && PG->matrix[i][j] != 0)
                PG->edgnum++;
            if (i != j && Op == 2 && PG->matrix[i][j] == 0)
                PG->matrix[i][j] = INF;
        }
    }
    PG->edgnum /= 2;
    if (Op == 2) //prim
    {
        fscanf(fptr, "%d", &root);
        prim(*PG, root);
    }
    return PG;
}
int get_end(int vends[], int i)
{
    while (vends[i] != 0)
        i = vends[i];
    return i;
}
EData *get_edges(Graph G)
{
    int i, j;
    int index = 0;
    EData *edges;
    edges = (EData *)malloc(G.edgnum * sizeof(EData));
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = i + 1; j < G.vexnum; j++)
        {
            if (G.matrix[i][j] != 0)
            {
                edges[index].start = G.vexs[i];
                edges[index].end = G.vexs[j];
                edges[index].weight = G.matrix[i][j];
                index++;
            }
        }
    }
    return edges;
}
void kruskal(Graph G)
{
    int i, m, n, p1, p2;
    int length;
    int index = 0; // index for rets[]
    int vends[Max] = {0};
    EData rets[Max]; // store the result
    EData *edges;
    edges = get_edges(G); // get all edges
    sorted_edges(edges, G.edgnum);
    for (i = 0; i < G.edgnum; i++)
    {
        p1 = get_position(G, edges[i].start); //get the index of the start of the i-th edge
        p2 = get_position(G, edges[i].end);   //get the index of the end of the i-th edge

        m = get_end(vends, p1); //get p1 on the end of the tree
        n = get_end(vends, p2); //get p2 on the end of the tree
        if (m != n)
        {
            vends[m] = n;             //set m on the n
            rets[index++] = edges[i]; //store
        }
    }
    free(edges);
    length = 0;
    printf("The edges of Minimum Cost Spanning Tree are\n\n");
    for (i = 0; i < index; i++)
    {
        printf("Edge %d: <%d,%d> cost: %d\n", i + 1, rets[i].start, rets[i].end, rets[i].weight);
        length += rets[i].weight;
    }
    printf("Minumum cost= %d\n", length);
}
int read(int cost[][100])
{
    int i, j, n;
    FILE *fptr = fopen("input3.txt", "r");
    fscanf(fptr, "%d", &n);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            fscanf(fptr, "%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = IN;
        }
    }
    fclose(fptr);
    return n;
}
int dijsktra(int cost[][100], int source, int target, int N) //use dijsktra
{
    int dist[1024], prev[1024], selected[1024] = {0}, i, m, min, start, d, j;
    char path[N];
    for (i = 1; i < N; i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start] = 1;
    dist[start] = 0;
    while (selected[target] == 0)
    {
        min = IN;
        m = 0;
        for (i = 1; i < N; i++)
        {
            d = dist[start] + cost[start][i];
            if (d < dist[i] && selected[i] == 0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if (min > dist[i] && selected[i] == 0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        if (m == 0)
            break;
        selected[start] = 1;
    }
    return dist[target];
}
int main()
{
    Graph *PG;
    FILE *fptr;
    int i, j, Op;
    int co, N;
    int source, target;
    int cost[100][100];
    fptr = fopen("input1.txt", "r");
    Op = 1;
    PG = read_graph(Op, fptr);
    kruskal(*PG); // kruskal
    fptr = fopen("input2.txt", "r");
    Op = 2;
    PG = read_graph(Op, fptr); //prim
    N = read(cost);
    N++;
    while (1)
    {
        printf("\n\nEnter two vertices<start end>:");
        scanf(" %d %d", &source, &target);
        if (source == -1 && target == -1)
            break;
        co = dijsktra(cost, source, target, N);
        if (co != IN)
            printf("The cost from %d to %d is : %d\n", source, target, co);
        else
            printf("The cost from %d to %d is : -1\n", source, target);
    }
    return 0;
}