#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

int G[MAXLEN][MAXLEN];	// �� 
int dfn[MAXLEN];		// dfn 
int low[MAXLEN];		// low
int ans[MAXLEN];		// �����Y�I�O���OArticulation point 
int n, root, depth, ans_num;

int min(int a, int b) {
	return a<b?a:b;
}

int dfs(int node, int parent) {
	int i, tmp;
	dfn[node] = low[node] = depth++; 
	
	for(i=1; i<=n; i++) {
		if(G[node][i]) { 
			if(dfn[i] < 0) {	// dfn < 0 �N��S�y�X�L 
				dfs(i, node);	// �y�X 
				low[node] = min(low[node], low[i]);	// ��s��e�I��low�A�i��O��e�I��dfn�άO�l�`�I��low 
				if(low[i] >= dfn[node]) {			// �p�G�l�`�I��low �j�󵥩� ��e�I��dfn �N��L�O Articulation point
					ans[node] = 1;
				}
			} else if (i != parent) {				// ��e�I�w�Q�y�X�L �B ���O���`�I �N���t�~�@�����|�i�H���I i (back edge or forward edge)
				low[node] = min(dfn[i], low[node]);	// ��e�I�i��O ��e�I��dfn �άO �l�`�I��low �άO i��dfn(back edge)
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
