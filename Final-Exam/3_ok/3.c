#include<stdio.h>
int main(){
    int i=0, j=0, k=0;
    int tmp, tot;
    FILE *fp = freopen("3input_2.txt", "r", stdin);
    scanf("%d", &tot);
    int arr[tot][tot];
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    for(k=0; k<tot; k++){
        for(i=0; i<tot; i++){
            for(j=0; j<tot; j++){
                arr[i][j] = arr[i][j] || arr[i][k] && arr[k][j];
            }
        }
    }
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
