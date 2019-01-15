#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 100
#define INTMAX 0x3f3f3f3f

int G[MAXLEN][MAXLEN];	// 圖 
int n;					// 點的數量 

void prim() {			// 選定一個邊作為生成樹，每次找從生成樹到生成樹外點的最小邊，加入生成樹 
    int i, j, V=1, min=INTMAX, x=-1, y;
    int st[MAXLEN]={0};	// 某點是不是在生成樹內 
   
    for(i=0; i<n; i++) {	// 先選一個最小邊 
        for(j=i+1; j<n; j++) {
        	if(G[i][j] && G[i][j] < min) {
        		min = G[i][j];
        		x = i;
        		y = j;
			}
    	}
    }
    G[x][y] = INTMAX;		// 刪掉邊 
   	printf("%d %d %d %d\n", V++, x+1, y+1, min);
	st[x] = st[y] = 1;		// 紀錄已在生成樹中 

    while(V < n) {
    	min = INTMAX;
		x = -1;
	    for(i=0; i<n; i++) {
	        for(j=0; j<n; j++) {
	        	if(G[i][j] && st[i] && !st[j] && G[i][j] < min) {	// 一邊在生成樹一邊不在 的最小邊 
	        		min = G[i][j];
	        		x = i;
	        		y = j;
				}
	    	}
	    }
	    if(x==-1) break;	// 找不到的情況 題目沒保證 但應該會有 
		st[x] = st[y] = 1;	// 紀錄已在生成樹中 
	    G[x][y] = INTMAX;	// 刪掉邊 
	    if(x<y)
	   		printf("%d %d %d %d\n", V++, x+1, y+1, min);
	   	else
	   		printf("%d %d %d %d\n", V++, y+1, x+1, min);
    }
}

int main() {
    int i, j;
    scanf("%d", &n);
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    prim();
    return 0;
}
