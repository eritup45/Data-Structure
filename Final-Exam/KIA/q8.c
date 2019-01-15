#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 100
#define INTMAX 0x3f3f3f3f

int G[MAXLEN][MAXLEN];	// �� 
int n;					// �I���ƶq 

void prim() {			// ��w�@����@���ͦ���A�C����q�ͦ����ͦ���~�I���̤p��A�[�J�ͦ��� 
    int i, j, V=1, min=INTMAX, x=-1, y;
    int st[MAXLEN]={0};	// �Y�I�O���O�b�ͦ��� 
   
    for(i=0; i<n; i++) {	// ����@�ӳ̤p�� 
        for(j=i+1; j<n; j++) {
        	if(G[i][j] && G[i][j] < min) {
        		min = G[i][j];
        		x = i;
        		y = j;
			}
    	}
    }
    G[x][y] = INTMAX;		// �R���� 
   	printf("%d %d %d %d\n", V++, x+1, y+1, min);
	st[x] = st[y] = 1;		// �����w�b�ͦ��� 

    while(V < n) {
    	min = INTMAX;
		x = -1;
	    for(i=0; i<n; i++) {
	        for(j=0; j<n; j++) {
	        	if(G[i][j] && st[i] && !st[j] && G[i][j] < min) {	// �@��b�ͦ���@�䤣�b ���̤p�� 
	        		min = G[i][j];
	        		x = i;
	        		y = j;
				}
	    	}
	    }
	    if(x==-1) break;	// �䤣�쪺���p �D�بS�O�� �����ӷ|�� 
		st[x] = st[y] = 1;	// �����w�b�ͦ��� 
	    G[x][y] = INTMAX;	// �R���� 
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
