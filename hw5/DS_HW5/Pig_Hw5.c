#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
    int u, v, w;
} edge;

int par[20000];
int graph[100][100];
int dij[100][100];

void init(int n)
{
    memset(par, -1, sizeof(int)*n);
}

int cmp(const void *a, const void *b)
{
    return ((edge*)a)->w - ((edge*)b)->w;
}

int root(int x)
{
    return par[x] < 0 ? x :( par[x] = root(par[x]));
}

void merge(int x, int y)
{
    x = root(x);
    y = root(y);
    if(x != y)
    {
        if(par[x] > par[y])
        {
            int temp = x;
            x = y;
            y = temp;
        }
        par[x] += par[y];
        par[y] = x;
    }
}

void kruskal()
{
    int i, j;
    int n, cnt = 0;
    scanf("%d", &n);
    int graph2[100][100] = {0};
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
            graph2[i][j] = graph[i][j];
            if(graph[i][j] != 0)
                cnt++;
        }
    init(n);
    cnt /= 2;
    edge e[cnt];
    cnt = 0;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(graph2[i][j] != 0)
            {
                e[cnt].u = i;
                e[cnt].v = j;
                e[cnt].w = graph2[i][j];
                cnt++;
                graph2[i][j] = graph2[j][i] = 0;
            }
    qsort(e, cnt, sizeof(edge), cmp);
    int CostSum = 0;
    for(i = j = 0; i < n-1 && j < cnt; i++, j++)
    {
        while(root(e[j].u) == root(e[j].v))
            j++;
        merge(e[j].u, e[j].v);
        printf("Edge %d:<%d %d> cost:%d\n", i+1, e[j].u+1, e[j].v+1, e[j].w);
        CostSum += e[j].w;
    }
    printf("Minimum cost = %d\n", CostSum);
    return ;
}

void prim()
{
    int i, j;
    int n, cnt, CostSum;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    int str, flag[100] = {0};
    scanf("%d", &str);
    str--;
    edge queue[100];
    memset(queue, 0, sizeof(queue));
    int front = 0, rear = -1;
    for(i = 0; i < n; i++)
        if(i != str && graph[str][i] != 0)
        {
            queue[++rear].u = str;
            queue[rear].v = i;
            queue[rear].w = graph[str][i];
        }
    /*for(front = 0; front <= rear; front++)
        printf("%d %d %d\n", queue[front].u+1, queue[front].v+1, queue[front].w);*/
    qsort(queue, rear+1, sizeof(edge), cmp);
    cnt = CostSum = 0;
    flag[str] = 1;
    while(1)
    {
        edge tmp = queue[front++];
        int addnode = tmp.v;
        if(flag[addnode])
            continue;
        flag[addnode] = 1;
        CostSum += tmp.w;
        cnt++;
        printf("Edge %d:<%d %d> cost:%d\n", cnt, tmp.u+1, tmp.v+1, tmp.w);
        if(cnt == n-1)
            break;
        for(i = 0; i < n; i++)
            if(i != addnode && graph[addnode][i] != 0)
            {
                queue[++rear].u = addnode;
                queue[rear].v = i;
                queue[rear].w = graph[addnode][i];
            }
        qsort(queue+front, rear-front+1, sizeof(edge), cmp);
    }
    printf("Minimum cost = %d\n", CostSum);
}

void dijkstra()
{
    memset(graph, 0, sizeof(graph));
    int i, j, n, used[100] = {0};
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    memset(dij, 0x3f3f3f3f, sizeof(dij));
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(graph[i][j] == 0)
                graph[i][j] = 0x3f3f3f3f;
    for(i = 0; i < n; i++)
    {
        dij[i][i] = 0;
        memset(used, 0, sizeof(used));
        while(1)
        {
            int v = -1, u;
            for(u = 0; u < n; u++)
                if(used[u] == 0 && (v == -1 || dij[i][u] < dij[i][v]))
                    v = u;
            if(v == -1)
                break;
            used[v] = 1;
            for(u = 0; u < n; u++)
                if(dij[i][u] > dij[i][v] + graph[v][u])
                    dij[i][u] = dij[i][v] + graph[v][u];
        }
    }
    int from, to;
    while(1)
    {
        printf("If want to leave, enter 0 0\n");
        printf("Enter two vertices<start end>:");
        scanf("%d %d", &from, &to);
        if(from == 0 && to == 0)
            break;
        if(from == 0 || to == 0)
        {
            printf("You are fucking idiot. Enter the vertices again!\n");
            continue;
        }
        if(dij[from-1][to-1] == 0x3f3f3f3f)
            printf("The cost from %d to %d is : -1\n", from, to);
        else
            printf("The cost from %d to %d is : %d\n", from, to, dij[from-1][to-1]);
    }
    return ;
}

int main()
{
    kruskal();
    prim();
    dijkstra();
}
