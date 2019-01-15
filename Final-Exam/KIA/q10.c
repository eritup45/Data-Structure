#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

int G[MAXLEN][MAXLEN];	// 圖 
int dfn[MAXLEN];		// dfn 
int low[MAXLEN];		// low
int ans[MAXLEN];		// 紀錄某點是不是Articulation point 
int n, root, depth, ans_num;

int min(int a, int b) {
	return a<b?a:b;
}

int dfs(int node, int parent) {
	int i, tmp;
	dfn[node] = low[node] = depth++; 
	
	for(i=1; i<=n; i++) {
		if(G[node][i]) { 
			if(dfn[i] < 0) {	// dfn < 0 代表沒造訪過 
				dfs(i, node);	// 造訪 
				low[node] = min(low[node], low[i]);	// 更新當前點的low，可能是當前點的dfn或是子節點的low 
				if(low[i] >= dfn[node]) {			// 如果子節點的low 大於等於 當前點的dfn 代表他是 Articulation point
					ans[node] = 1;
				}
			} else if (i != parent) {				// 當前點已被造訪過 且 不是父節點 代表有另外一條路徑可以到點 i (back edge or forward edge)
				low[node] = min(dfn[i], low[node]);	// 當前點可能是 當前點的dfn 或是 子節點的low 或是 i的dfn(back edge)
			}
		}
	}
}

void printAns() {
	int i;
	for(i=1; i<=n; i++) printf("%d ", dfn[i]);
	printf("\n");
	for(i=1; i<=n; i++) printf("%d ", low[i]);
	printf("\n");
	for(i=0; i<=n; i++) if(ans[i]) printf("%d ", i);
	printf("\n");
}

int main() {
	int i, j;
	freopen("10input.txt", "r", stdin);
//	freopen("5output_1.txt", "w", stdout);
	scanf("%d%d", &root, &n);
	for(i=1; i<=n; i++) {
		for(j=1; j<=n; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	depth = ans_num = 0;
	for(i=1; i<=n; i++) dfn[i] = -1;
	for(i=1; i<=n; i++) low[i] = -1;
	for(i=1; i<=n; i++) ans[i] = 0;

	dfs(root, -1);
	printAns();
	return 0;
} 
