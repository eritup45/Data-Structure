#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 1000

typedef struct{
	int val;
	int lvl;
} lift;

int grow[MAXLEN];
int visit[MAXLEN];
lift queue[MAXLEN];
int front=-1, rear=-1;
int n;

void push(lift item) {
	queue[++rear] = item;
}

lift pop() {
	return queue[++front];
}

void bfs(int start, int end) {
	lift tmp, next;

	tmp.val = start;
	tmp.lvl = 0;
	visit[start] = 1;
	push(tmp);

	while(front < rear) {
		tmp = pop();
		if(tmp.val > n && tmp.val < 1) continue;	// �p�G�Ӽh���ŦX�W�h�Npass�� 
		if(tmp.val == end) {						// ��ؼмӼh 
			printf("%d", tmp.lvl);					// �L�X�g�L���Ӽh�ƶq 
			return;
		}
		visit[tmp.val] = 1;
		next.lvl = tmp.lvl + 1;
		next.val = tmp.val + grow[tmp.val];			// �q��V�W 
		if(!visit[next.val]) push(next);
		next.val = tmp.val - grow[tmp.val];			// �q��V�U 
		if(!visit[next.val]) push(next);
	}
	printf("-1");
}

int main() {
	int i, from, to;
	freopen("6input_4.txt", "r", stdin);
//	freopen("5output_1.txt", "w", stdout);
	scanf("%d%d%d", &n, &from, &to);
	for(i=1; i<n; i++) visit[i] = 0;
	for(i=1; i<n; i++) {
		scanf("%d", grow+i); 
	}
	bfs(from, to);
	return 0;
} 
