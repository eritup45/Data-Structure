#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_arr(int *arr, int tot){
    int i=0;
    for(i=0; i<tot; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void read_data(int arr[], int *tot){
    FILE *fp = freopen("4input_3.txt", "r", stdin);
    while(scanf("%d", &arr[*tot]) != EOF)
        (*tot)++;
    fclose(fp);
}

int intcmp(int arr1[], int arr2[], int tot){
    int i=0;
    for(i=0; i<tot; i++){
        if(arr1[i] != arr2[i])
            return 1;
    }
    return 0;
}

void quick_sort(int *arr, int left, int right, int tot){
    if(left >= right)   return ;    //@@
    int i=left, j=right+1;  //@@
    int pivot = arr[left];
    do{
        do{ i++; }  while(arr[i] < pivot);
        do{ j--; }  while(arr[j] > pivot);
        if(i < j){
            swap(&arr[i], &arr[j]);
            print_arr(arr, tot);
        }
    }while(i < j);

    int tmp2[tot], u;
    for(u=0; u<tot; u++)
        tmp2[u] = arr[u];

    swap(&arr[left], &arr[j]);

    if(intcmp(tmp2, arr, tot) != 0)
        print_arr(arr, tot);

    quick_sort(arr, left, j-1, tot);
    quick_sort(arr, j+1, right, tot);
}

int main(){
    int i=0, j=0;
    int arr[1024], tot=0;
    read_data(arr, &tot);
    //freopen("output.txt", "w", stdout);
    quick_sort(arr, 0, tot-1, tot);
    return 0;
}
