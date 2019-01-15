#include <stdio.h>
#define MAXLEN 100
#define INF 0x3f3f3f3f

int G[MAXLEN][MAXLEN];	// 圖 
int n;					// 點的數量 
int dis[MAXLEN];		// 紀錄start到 i點的距離 
int parent[MAXLEN];		// 紀錄i點的父節點 
int visit[MAXLEN];		// 紀錄是否拜訪過 

void dijkstra(int start) {
    int i, j, V=0;
    for(i=0; i<n; i++)     visit[i] =  0;	// 初始化  
    for(i=0; i<n; i++)       dis[i] = INF;
    for(i=0; i<n; i++)    parent[i] = -1;

    dis[start-1] = 0;						// 把起點距離設為0 
    parent[start-1] = start-1;				// 起點父親等於自己 
    
    while(V < n-1) {						// 最多找n個點
        int min=INF, a=-1;
        for(i=0; i<n; i++) {				// 找當前沒拜訪過，且距離最近的點 
            if(!visit[i] && dis[i] < min) {
                a = i;
                min = dis[i];
            }
        }
        if(a == -1) break;					// 找不到代表最短路徑已經找完了 
        visit[a] = 1;						// 把該點設為已訪問過 

        for(i=0; i<n; i++) {				// 用當前距離最近的點去維護距離 
            if(G[a][i] && dis[i] > dis[a]+G[a][i]) {	// 如果a可以到i 且 原本到i的距離 大於 先到a點再由a到i的距離 
                dis[i] = dis[a] + G[a][i];				// 最短距離更新 
                parent[i] = a;							// 紀錄i的上個點是 a 
            }
        }
        V++;
    }
}

void printPath(int start, int end) {
    int list[MAXLEN], num=0, curr=end-1, i;
    if (dis[curr] == INF) {		// start到不了end 
    	printf("-1");
    	return;
	}
    list[num++] = curr;			// 可以把list看成一個stack，front是終點 
    while(curr != start-1) {	// 當前點不是起點 
        curr = parent[curr];	// 把當前點的父節點丟到stack 
        list[num++] = curr;
    }
    for(num-=1; num>=0; num--) {
        printf("%d ", list[num]+1);
    }
}

int main() {
    int i, j, tmp, from, to;
	freopen("7input_1.txt", "r", stdin);
//	freopen("5output_1.txt", "w", stdout);
    scanf("%d", &n);
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            scanf("%d", &tmp);
            G[i][j] = tmp ? tmp : INF;
        }
    }
    scanf("%d %d", &from, &to);
    dijkstra(from);
    printPath(from, to);
    return 0;
}
