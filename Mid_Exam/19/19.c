#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int stacktop = -1;

void push(char word, char *stack){
    if(stacktop >= 1023){
        printf("Stack Full!");
        return;
    }
    stack[++stacktop] = word;
    //stack[stacktop+1] = '\0';
}
char pop(char *stack){
    char tmp;
    if(stacktop <= -1){
        printf("Stack Empty!");
        return;
    }
    tmp = stack[stacktop--];
    return tmp;
}
int main(){
    char string[1024], *token, tmp;
    char stack[1024];
    int M=0, len=0, count=0, i=0, j=0;
    FILE *fp;
    fp = freopen("19input-2.txt", "r", stdin);
    while(fgets(string, 1024, stdin)){
        token = strtok(string, " \r\n");
        M = atoi(token);
        token = strtok(NULL, " \r\n");
        strcpy(string, token);
        len = strlen(string);
        while((len-count) >= M){
            for(i=0; i<M; i++, count++){
                push(string[count],stack);
            }
            for(i=0; i<M; i++){
                tmp = pop(stack);
                printf("%c",tmp);
            }
        }
        while(count < len){
            printf("%c", string[count]);
            count++;
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
