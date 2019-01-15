#include <stdio.h>
#define MAXLEN 1000
#define INTMAX 0x7fffffff

int map[MAXLEN][MAXLEN];
int root[MAXLEN];
int n;

int findRoot(int x) {	// 找該子樹的根 
	return x==root[x]?x:(root[x]=findRoot(root[x]));
}

int unionSet(int a, int b) {	// 聯集兩顆子樹 
	root[findRoot(b)] = findRoot(a);
}

void kruskal() {		// kruskal: 每次找最小的邊，試加進去生成樹，如果有環(兩端都在生成樹內)就拋棄 
	int T=n-1;
	int i, j; 
	int t[MAXLEN]={0};	// 紀錄某點是不是已經在生成樹內了 

	for(i=0; i<n; i++) {
		root[i] = i;
	}

	while(T) {			// 生成樹會有n-1個邊
		int min = INTMAX, min_x=-1, min_y=-1;
		
		for(i=0; i<n; i++) {				// 找最小邊 
			for(j=i+1; j<n; j++) {
				if(map[i][j] < min) {
					min = map[i][j];
					min_x = i;
					min_y = j;
				}
			}
		}
		if(min_x == -1) break;				// 如果沒邊了 就break掉 (題目沒保證會有生成樹 但應該會有 所以寫安心的) 
		map[min_x][min_y] = INTMAX;			// 把邊刪掉 
		if(findRoot(min_x) == findRoot(min_y)) continue;	// 如果兩點在同一棵生成樹中 則會形成環 找下個邊 
		unionSet(min_x, min_y);								// 聯集生成樹
		T--;
		printf("%d %d %d\n", min_x+1, min_y+1, min);
	}
}

int main() {
	int i, j, tmp;
	freopen("5input_3.txt", "r", stdin);
//	freopen("5output_1.txt", "w", stdout);
	scanf("%d", &n);
	for(i=0; i<n; i++) 
		for(j=0; j<n; j++) {
			scanf("%d", &tmp);
			map[i][j] = !tmp?INTMAX:tmp;	// 如果tmp是0 那(i,j)之間的距離就是INTMAX 
		}

	kruskal();
	return 0;
} 
