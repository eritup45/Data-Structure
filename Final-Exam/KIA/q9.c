#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 10000

int list[MAXLEN];
int n;

void printList() {
	int i=0;
	for(i=0; i<n; i++) printf("%d ", list[i]);
	printf("\n");
} 

void swp(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_sort() {
	int i, j, flag;
	for(i=1; i<n; i++) {		// 進行n-1次 
		for(j=0; j<n-i; j++) {	// 每次j從0到n-1 (或 n-i) 
			if(list[j] > list[j+1]) {
				flag = 0;
				swp(list+j, list+j+1);
			}
		}
		printList();
	}
}

int main() {
	freopen("9input_1.txt", "r", stdin);
//	freopen("5output_1.txt", "w", stdout);
	n = 0;
	while(scanf("%d", list+n)!=EOF) n++;
	bubble_sort();
	return 0;
} 
