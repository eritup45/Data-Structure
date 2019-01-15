406410027, 洪晟瑞

(A)kruskal.c:
	Using kruskal's algorithm to build a minimum spanning tree.

	Let edge structure:
	typedef struct{
		int vstart; //start
		int vnext;
		int weight;
	}edge;
	
	function:
		(a)int cmp(const void *a, const void *b):
			qsort (edge *)edgeSet.
		(b)void get_increaseWeight(edge increaseWeight[], int *totEdgeNum):
			Get increase order edges, and put into increaseWeight[], and
			renew the total edges into totEdgeNum.
		(c)int find_root(int rootSet[], int num):
			return num's root position (in rootSet[])
		(d)void unite_set(int rootSet[], int vstart, int vnext):
			If vertex vstart and vertex vnext have the same root, unite 
			them into a same sequence.
	
(B)prim.c:
	Using prim's algorithm to build a minimum spanning tree.

	Just a data type.
	typedef struct{
		int vstart; //start
		int vnext;
		int weight;
	}edge;
	
	Help judging prim.
	typedef struct
	{
		int predecessor;    //連接此點的前一個點
		int key;    //前一點與此點的weight
		int visited;    //record whether visited or not
	}Graph;

	global:
		edge edgeSet[10000];
		int edgeNum = 0;
		int **adjM;
	
	(a)void compare_key(Graph graphJudge[], int tot, int cur):
		If the weight of adjacency matrix is smaller than key, update key 
		and predecessor.
	(b)void add_least_key(Graph graphJudge[], int tot, int *cur):
		Select a smallest vertex putting in edgeSet, and mark.
	
	
(C)	dijkstra.c:
	
	typedef struct{
		int vstart;
		int vnext;
		int weight;
	}edge;
	
	global:
	int dist[10000];    // dist[] -- the distance from the ith node to the source node
	int visited[10000];
	int **adjM;         // adjM[][] -- adjacency matrix
	int tot;            // tot -- tot nodes
	int cost[100][100]; //cost[from][to] == weight
	
	(a)int dijkstra(int start, int end):
		return the shortest cost from start to end

