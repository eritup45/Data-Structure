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

void usage(){
    printf("(1)Selection Sort\n");
    printf("(2)Bubble Sort\n");
    printf("(3)Insertion Sort\n");
    printf("(4)Quick Sort\n");
}

void read_file(int *arr, int *tot, int *option){
    FILE *fp;
    usage();
    scanf("%d", option);
    fp = fopen("test.txt", "r");
    while(fscanf(fp, "%d", &arr[*tot]) != EOF){
        (*tot)++;
    }
    printf("Input array:\n");
    print_arr(arr, *tot);
    fclose(fp);
}

void selection_sort(int *arr, int tot){
    int i=0, j=0, min, minP;
    for(i=0; i<tot; i++){
        min = arr[i];
        minP = i;
        for(j=i; j<tot; j++){
            if(arr[j] < min){
                min = arr[j];
                minP = j;
            }
        }
        swap(&arr[i], &arr[minP]);
        print_arr(arr, tot);
    }
    printf("Total step: %d", i);
}

void bubble_sort(int *arr, int tot){
    int i=0, j=0;
    for(i=0; i<tot-1; i++){
        for(j=0; j<tot-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
        print_arr(arr, tot);
    }
    printf("Total step: %d\n", i);
}

void insertion_sort(int *arr, int tot){
    int i=0, j=0, key;
    print_arr(arr, tot);
    for(i=1; i<tot; i++){   //change arr[i]
        key = arr[i];   //aka tmp
        for(j=i-1; j>=0; j--){
            if(key < arr[j]){   //If arr[j] > key, move backward.
                arr[j+1] = arr[j];
            }
            else    break;
        }
        arr[j+1] = key;

        print_arr(arr, tot);
    }
    printf("Total step: %d\n", i);
}

//right is equal to "right position"
void quick_sort(int *arr, int left, int right, int tot){    //tot is just for printing the result.
    if(left >= right)   return ;
    int i=left, j=right+1;
    int pivot;  //the compared number
    pivot = arr[left];
    do{
        do{ i++; }    while(arr[i] < pivot);  //find element > pivot
        do{ j--; }    while(arr[j] > pivot);  //find element < pivot
        if(i < j){
            swap(&arr[i], &arr[j]); //swap arr[i](bigger) and arr[j](smaller)
        }
    }while(i < j);
    if(i > j)
    swap(&arr[left], &arr[j]);  //pivot is in the middle now.
    print_arr(arr, tot);

    quick_sort(arr, left, j-1, tot);    //j-1 = pivot left
    quick_sort(arr, j+1, right, tot);   //j+1 = pivot right
}

int main(){
    int arr[100010], tot = 0, option;
    read_file(arr, &tot, &option);
    if(option == 1){
        printf("Selection sort:\n");
        selection_sort(arr, tot);
    }
    else if(option == 2){
        printf("Bubble sort:\n");
        bubble_sort(arr, tot);
    }
    else if(option == 3){
        printf("Insertion sort:\n");
        insertion_sort(arr, tot);
    }
    else if(option == 4){
        printf("Quick sort:\n");
        quick_sort(arr, 0, tot-1, tot);
    }
    return 0;
}
