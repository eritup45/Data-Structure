#include <stdio.h>
#include <stdlib.h> 
#define MAXLEN 1000

int arr[MAXLEN];
int n;

void printArr(int arr[]) {
	int i;
	for(i=0; i<n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int *a, int *b) { 
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	printArr(arr);
}

void quick_sort(int arr[], int lower, int upper) {
	if(lower<upper) {									// 確保至少有兩個(含)以上的元素要排序 
		int pivot=lower;
		int left=lower, right=upper+1;
		
		do {
			do left++; while(left<=upper && arr[pivot] > arr[left]); 
			do right--; while(arr[pivot] < arr[right]);
			if(left < right) swap(arr+left, arr+right);
		} while(left < right);
		if(pivot != right) swap(arr+pivot, arr+right);	// pivot等於right的情況 兩個位置一樣不用換 
		quick_sort(arr, lower, right-1);
		quick_sort(arr, right+1, upper);
	}
}

int main() {
	freopen("4input_1.txt", "r", stdin);
//	freopen("4output_1.txt", "w", stdout);
	n = 0;
	while(scanf("%d", arr+n)!=EOF) n++;
	quick_sort(arr, 0, n-1);
	return 0;
} 
