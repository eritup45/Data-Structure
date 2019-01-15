#include <stdio.h>
#define MAXLEN 100
#define INF 0x3f3f3f3f

int G[MAXLEN][MAXLEN];	// �� 
int n;					// �I���ƶq 
int dis[MAXLEN];		// ����start�� i�I���Z�� 
int parent[MAXLEN];		// ����i�I�����`�I 
int visit[MAXLEN];		// �����O�_���X�L 

void dijkstra(int start) {
    int i, j, V=0;
    for(i=0; i<n; i++)     visit[i] =  0;	// ��l��  
    for(i=0; i<n; i++)       dis[i] = INF;
    for(i=0; i<n; i++)    parent[i] = -1;

    dis[start-1] = 0;						// ��_�I�Z���]��0 
    parent[start-1] = start-1;				// �_�I���˵���ۤv 
    
    while(V < n-1) {						// �̦h��n���I
        int min=INF, a=-1;
        for(i=0; i<n; i++) {				// ���e�S���X�L�A�B�Z���̪��I 
            if(!visit[i] && dis[i] < min) {
                a = i;
                min = dis[i];
            }
        }
        if(a == -1) break;					// �䤣��N��̵u���|�w�g�䧹�F 
        visit[a] = 1;						// ����I�]���w�X�ݹL 

        for(i=0; i<n; i++) {				// �η�e�Z���̪��I�h���@�Z�� 
            if(G[a][i] && dis[i] > dis[a]+G[a][i]) {	// �p�Ga�i�H��i �B �쥻��i���Z�� �j�� ����a�I�A��a��i���Z�� 
                dis[i] = dis[a] + G[a][i];				// �̵u�Z����s 
                parent[i] = a;							// ����i���W���I�O a 
            }
        }
        V++;
    }
}

void printPath(int start, int end) {
    int list[MAXLEN], num=0, curr=end-1, i;
    if (dis[curr] == INF) {		// start�줣�Fend 
    	printf("-1");
    	return;
	}
    list[num++] = curr;			// �i�H��list�ݦ��@��stack�Afront�O���I 
    while(curr != start-1) {	// ��e�I���O�_�I 
        curr = parent[curr];	// ���e�I�����`�I���stack 
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
