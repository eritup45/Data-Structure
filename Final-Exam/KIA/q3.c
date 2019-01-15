#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 100

int G[MAXLEN][MAXLEN];	// �� 

int main() {
	int n, i, j, k;
	freopen("3input_1.txt", "r", stdin);
//	freopen("3output_1.txt", "w", stdout);
	// ��J 
	scanf("%d", &n); 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	// floyd warshall 
	for(k=0; k<n; k++)						// �b�Ϥ���w�@���I k (���~�I) 
		for(i=0; i<n; i++)					// �b�Ϥ���w�@���I i (�X�o�I)
			for(j=0; j<n; j++)				// �b�Ϥ���w�@���I j (��F�I)
				if(G[i][k] && G[k][j])		// �p�G ���@����O i��k �B ���@����O k��j 
					G[i][j] = 1;			// ���N��i�i�H��j
 
	// �L�X�� 
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%d ", G[i][j]);	
		}
		printf("\n");
	}
	
	return 0;
}
