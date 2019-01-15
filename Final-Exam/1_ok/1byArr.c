#include<stdio.h>
#include<string.h>

int cnt[100], graph[100][100];

topsort(int tot){
    int i=0, j=0, k=0;
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            if(cnt[j] == 0){
                cnt[j] = -1;
                break;
            }
        }
        printf("%d ", j+1);
        for(k=0; k<tot; k++){
            if(graph[j][k])
                cnt[k]--;
        }
    }
}

int main(){
    memset(cnt, 0, sizeof(cnt));
    int i=0, j=0, msize;
    freopen("1input_3.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j])
                cnt[j]++;
        }
    }
    topsort(msize);
    return 0;
}
