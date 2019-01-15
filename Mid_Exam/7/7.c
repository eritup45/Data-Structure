#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int main(){
    char preline[1024],stack[1024][100],tmp[100],op1[100],op2[100],op[3],postresult[1024];
    int i=0, j=0, total=0, top=-1;
    freopen("7input.txt", "r", stdin);
    //freopen("7ouput.txt", "w", stdout);
    while(scanf("%c",&preline[i]) != EOF){// read data
        if(preline[i]==' ')
            continue;
        i++;
    }
    total = i;
    preline[i++]='\0';
    for(i=total-1; i>=0; i--){
        if( isalpha(preline[i]) ){
            stack[++top][0] = preline[i];
            stack[top][1] = '\0';
        }
        else{
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            op[0] = preline[i];
            strcpy(tmp, op1);
            strcat(tmp, op2);
            strcat(tmp, op);
            strcpy(stack[++top], tmp);
        }
    }
    strcpy(postresult, stack[0]);
    printf("%s\n",postresult);
    return 0;
}
