#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define NOTEXIST -1
#define BEGIN -1
#define MAXVEX 100
#define INFINITY 65535
#define TRUE 1
#define FALSE 0
typedef int EdgeType;
typedef char VertexType;
int path[MAXVEX];
int dist[MAXVEX];
int known[MAXVEX];

typedef struct Graph {
	int vex[MAXVEX];
	int edge[MAXVEX][MAXVEX];
	int vex_num, edge_num;
}Graph;

 int **get_adjMatrix(){
    int i=0, j=0, totLine=0;
    char line[1024];
    FILE *fp = fopen("input3.txt", "r");

    fscanf(fp, "%d", &totLine);

    //分配記憶體 adjM[totLine][totLine];
    int *adjM, *pData;
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

int get_pos(Graph g, char ch)
{
	int i;
	for (i = 0; i < g.vex_num; i++) {
		if (g.vex[i] == ch)
			return i;
	}
	return -1;
}

/*char read_char()
{
	char ch;
	do {
		ch = getchar();
	} while (!isalpha(ch));
	return ch;
}*/

/*void create_graph(Graph *g)
{
	int i, j, k;
	printf("请输入顶点数与边数:\n");
	scanf("%d%d", &g->vex_num, &g->edge_num);
	for (i = 0; i < g->vex_num; i++) {
		for (j = 0; j < g->vex_num; j++) {
			if (i == j) {
				g->edge[i][j] = 0;
			}
			else
				g->edge[i][j] = INFINITY;
		}
	}
	printf("请输入顶点信息:\n");
	for (i = 0; i < g->vex_num; i++) {
		g->vex[i] = read_char();
	}
	printf("请输入边的信息:\n");
	char c1, c2;
	int p1, p2, w;
	for (k = 0; k < g->edge_num; k++) {
		c1 = read_char();
		c2 = read_char();
		scanf("%d", &w);
		p1 = get_pos(*g, c1);
		p2 = get_pos(*g, c2);
		g->edge[p1][p2] = w;//有向边的权重
	}
}*/

void init_graph(Graph *g, int end)
{
	int i;
	for (i = 0; i < g->vex_num; i++) {
		path[i] = NOTEXIST;
		known[i] = FALSE;
		dist[i] = INFINITY;
	}

	dist[end] = 0;
}

int find_min(Graph g)
{
	int min;
	min = INFINITY;
	int i;
	int index;
	for (i = 0; i < g.vex_num; i++) {
		if (known[i] == FALSE && dist[i] < min) {
			index = i;
			min = dist[i];
		}
	}
	if (min == INFINITY)
		return -1;
	else
		return index;
}

void Dijkstra(Graph g)
{
	int v;
	int w;
	while (1) {
		v = find_min(g);
		//printf("v = %d", v);
		if (v == NOTEXIST)
			break;
		known[v] = TRUE;
		for (w = 0; w < g.vex_num; w++) {
			if (known[w] == FALSE && (dist[v] + g.edge[v][w] < dist[w])) {
				dist[w] = dist[v] + g.edge[v][w];
				path[w] = v;
			}
		}
	}
}

void print_graph(Graph g)
{
	int i, j;
	for (i = 0; i < g.vex_num; i++) {
		for (j = 0; j < g.vex_num; j++) {
			if (g.edge[i][j] == INFINITY)
				printf("%c", '*');
			else {
				printf("%d", g.edge[i][j]);
			}
		}
		printf("\n");
	}
}

/*void print_path2(Graph g, int end)//这里 直接传递最后位置的索引
{
	if (path[end] != BEGIN) {
		print_path2(g, path[end]);
		printf("->");
	}
	printf("%c ", g.vex[end]);
}*/

int main()
{
	Graph g;
	int start, end;
	char c1, c2;
	create_graph(&g);
	printf("Enter two vertices<start end>:");
    scanf("%d %d", &start, &end);
    start--;    end--;
	g.edge = get_adjMatrix();
	init_graph(&g,start);
	Dijkstra(g);
	if(dist[end] == INFINITY)
		printf("-1");
	else{
		printf("最短路径为:\n\n");
		print_path2(g, end);
		printf("\n\n最小花费 : %d",dist[end]);
	}

	return 0;
}
