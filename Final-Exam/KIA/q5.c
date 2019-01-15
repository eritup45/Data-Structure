#include <stdio.h>
#define MAXLEN 1000
#define INTMAX 0x7fffffff

int map[MAXLEN][MAXLEN];
int root[MAXLEN];
int n;

int findRoot(int x) {	// ��Ӥl�𪺮� 
	return x==root[x]?x:(root[x]=findRoot(root[x]));
}

int unionSet(int a, int b) {	// �p�������l�� 
	root[findRoot(b)] = findRoot(a);
}

void kruskal() {		// kruskal: �C����̤p����A�ե[�i�h�ͦ���A�p�G����(��ݳ��b�ͦ���)�N�߱� 
	int T=n-1;
	int i, j; 
	int t[MAXLEN]={0};	// �����Y�I�O���O�w�g�b�ͦ��𤺤F 

	for(i=0; i<n; i++) {
		root[i] = i;
	}

	while(T) {			// �ͦ���|��n-1����
		int min = INTMAX, min_x=-1, min_y=-1;
		
		for(i=0; i<n; i++) {				// ��̤p�� 
			for(j=i+1; j<n; j++) {
				if(map[i][j] < min) {
					min = map[i][j];
					min_x = i;
					min_y = j;
				}
			}
		}
		if(min_x == -1) break;				// �p�G�S��F �Nbreak�� (�D�بS�O�ҷ|���ͦ��� �����ӷ|�� �ҥH�g�w�ߪ�) 
		map[min_x][min_y] = INTMAX;			// ����R�� 
		if(findRoot(min_x) == findRoot(min_y)) continue;	// �p�G���I�b�P�@�ʥͦ��� �h�|�Φ��� ��U���� 
		unionSet(min_x, min_y);								// �p���ͦ���
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
			map[i][j] = !tmp?INTMAX:tmp;	// �p�Gtmp�O0 ��(i,j)�������Z���N�OINTMAX 
		}

	kruskal();
	return 0;
} 
