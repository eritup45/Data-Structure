#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int indeg[MAXLEN];	// 紀錄每個點的in-degree 
int outdeg[MAXLEN]; // 紀錄每個點的out-degree 

int n;				// 點的數量 

int main() {
	int i=0, j=0, tmp;
	
	freopen("2input_1.txt", "r", stdin);
//	freopen("2output_1.txt", "w", stdout);
	scanf("%d", &n);

	for(i=0; i<n; i++) indeg[i]=0;	// 初始化 
	for(i=0; i<n; i++) outdeg[i]=0;

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &tmp);		// 輸入順便算in-degree跟out-degree 
			if(tmp) {				// 如果 (i, j) 值不為零，代表有一條i到j的邊 
				indeg[j]++;			// i的out-degree +1 
				outdeg[i]++;		// j的in-degree +1 
			}
		}
	}

	for(i=0; i<n; i++) {
		printf("%d %d %d\n", i+1, indeg[i], outdeg[i]);	//輸出 
	}
	
	return 0;
}
