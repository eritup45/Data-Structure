#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 100

int G[MAXLEN][MAXLEN];	// 圖 

int main() {
	int n, i, j, k;
	freopen("3input_1.txt", "r", stdin);
//	freopen("3output_1.txt", "w", stdout);
	// 輸入 
	scanf("%d", &n); 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	// floyd warshall 
	for(k=0; k<n; k++)						// 在圖中選定一個點 k (中繼點) 
		for(i=0; i<n; i++)					// 在圖中選定一個點 i (出發點)
			for(j=0; j<n; j++)				// 在圖中選定一個點 j (到達點)
				if(G[i][k] && G[k][j])		// 如果 有一條邊是 i到k 且 有一條邊是 k到j 
					G[i][j] = 1;			// 那代表i可以到j
 
	// 印出圖 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%d ", G[i][j]);	
		}
		printf("\n");
	}
	
	return 0;
}
