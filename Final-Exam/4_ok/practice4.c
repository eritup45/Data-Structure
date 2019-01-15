#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void SWAP(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_arr(int *arr, int tot){
    int i=0;
    for(i=0; i<tot; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int intcmp(int arr1[], int arr2[], int tot){
    int i=0;
    for(i=0; i<tot; i++)
        if(arr1[i] != arr2[i])
            return 1;
    return 0;
}

void quick_sort(int *arr, int tot, int left, int right){
    if(left >= right)   return; //@@
    int tmp[1000], k;
    int i = left;
    int j = right+1;    //@@
    int pivot = arr[left];
    do{
        do{ i++; } while(arr[i] < pivot);
        do{ j--; } while(arr[j] > pivot);
        if(i < j){
            SWAP(&arr[i], &arr[j]);
            print_arr(arr, tot);
        }
    }while(i < j);
    for(k=0; k<tot; k++)
        tmp[k] = arr[k];

    SWAP(&arr[left], &arr[j]);
    if(intcmp(tmp, arr, tot) != 0)
        print_arr(arr, tot);

    quick_sort(arr, tot, left, j-1);
    quick_sort(arr, tot, j+1, right);
}

int main(){
    int arr[100];
    int tot=0;
    FILE *fp = freopen("4input_3.txt", "r", stdin);
    while(scanf("%d", &arr[tot]) != EOF)
        tot++;
    quick_sort(arr, tot, 0, tot-1);
}
