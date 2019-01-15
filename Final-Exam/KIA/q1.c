#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int G[MAXLEN][MAXLEN];	// adjacency matrix 
int visit[MAXLEN];		// �����I���S���X�ݹL 
int indeg[MAXLEN];		// �����C���I��in-degree 

int n;

void visitAdj(int x) {	// ��x���F�~�A�վ��in-degree 
	int i;
	for(i=0; i<n; i++) {
		if(G[x][i]) {	// ���@����O(x, i)�A�ҥHi�O�F�~ 
			indeg[i]--;	// i��in-degree -1 (�]��x�w�g�]��F) 
		}
	}
}

int main() {
	int i=0, j=0;
	freopen("1input_1.txt", "r", stdin);
	scanf("%d", &n);
	for(i=0; i<n; i++) indeg[i]=0;			// ��in-degree ��l�� 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &G[i][j]);
			if(G[i][j]!=0) indeg[j]++;		// ��J���K����in-degree 
		}
	}
	
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) { 
			if(indeg[j]==0) {				// �C�����ein-degree�ȵ���0�B�̤p���I 
				indeg[j] = -1;				// �R���o���I 
				printf("%d ", j+1); 
				visitAdj(j);				// �h�X�ݳo���I���Ҧ��F�~�A�վ�F�~��in-degree 
				break;
			}
		}
	}
	return 0;
}
 
