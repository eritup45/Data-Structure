#include<stdio.h>
#include<string.h>
int main(){
    int i=0, j=0, tot, tmp;
    freopen("2input_1.txt", "r", stdin);
    scanf("%d", &tot);
    int in[tot], out[tot];
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            scanf("%d", &tmp);
            if(tmp == 1){
                in[j]++;
                out[i]++;
            }
        }
    }
    for(i=0; i<tot; i++){
        printf("%d %d %d\n", i+1, in[i], out[i]);
    }
}
