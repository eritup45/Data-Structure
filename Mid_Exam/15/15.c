#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void recur(int num){
    int tmp=0;
    if(num < 10){
        printf("%d\n",num);
        return ;
    }
    else{
        while(num > 0){
            tmp += (num % 10);
            num /= 10;
        }
        recur(tmp);
    }
}
int main(){
    int num;
    freopen("15input-2.txt", "r", stdin);
    freopen("15output.txt", "w", stdout);
    scanf("%d",&num);
    recur(num);
    return 0;
}
