#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int G[MAXLEN][MAXLEN];	// adjacency matrix 
int visit[MAXLEN];		// 紀錄點有沒有訪問過 
int indeg[MAXLEN];		// 紀錄每個點的in-degree 

int n;

void visitAdj(int x) {	// 找x的鄰居，調整其in-degree 
	int i;
	for(i=0; i<n; i++) {
		if(G[x][i]) {	// 有一條邊是(x, i)，所以i是鄰居 
			indeg[i]--;	// i的in-degree -1 (因為x已經跑到了) 
		}
	}
}

int main() {
	int i=0, j=0;
	freopen("1input_1.txt", "r", stdin);
	scanf("%d", &n);
	for(i=0; i<n; i++) indeg[i]=0;			// 把in-degree 初始化 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &G[i][j]);
			if(G[i][j]!=0) indeg[j]++;		// 輸入順便紀錄in-degree 
		}
	}
	
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) { 
			if(indeg[j]==0) {				// 每次找當前in-degree值等於0且最小的點 
				indeg[j] = -1;				// 刪除這個點 
				printf("%d ", j+1); 
				visitAdj(j);				// 去訪問這個點的所有鄰居，調整鄰居的in-degree 
				break;
			}
		}
	}
	return 0;
}
 
