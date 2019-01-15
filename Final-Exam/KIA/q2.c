#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int indeg[MAXLEN];	// �����C���I��in-degree 
int outdeg[MAXLEN]; // �����C���I��out-degree 

int n;				// �I���ƶq 

int main() {
	int i=0, j=0, tmp;
	
	freopen("2input_1.txt", "r", stdin);
//	freopen("2output_1.txt", "w", stdout);
	scanf("%d", &n);

	for(i=0; i<n; i++) indeg[i]=0;	// ��l�� 
	for(i=0; i<n; i++) outdeg[i]=0;

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &tmp);		// ��J���K��in-degree��out-degree 
			if(tmp) {				// �p�G (i, j) �Ȥ����s�A�N���@��i��j���� 
				indeg[j]++;			// i��out-degree +1 
				outdeg[i]++;		// j��in-degree +1 
			}
		}
	}

	for(i=0; i<n; i++) {
		printf("%d %d %d\n", i+1, indeg[i], outdeg[i]);	//��X 
	}
	
	return 0;
}
