#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int top = -1;

int precedence(char c){
    if(c == '*' || c == '/')
        return 2;
    else if(c == '-' || c == '+')
        return 1;
    else
        return 0;
}
void push(char *stack, char c){
    stack[++top]=c;
}
char pop(char *stack){
    return stack[top--];
}
int main(){
    char stack[1024], line[1024], op, *token;
    int i=0, j=0, max=0;
    FILE *rfp,*wfp;
    rfp = freopen("6input.txt", "r", stdin);
    wfp = freopen("6output-1.txt", "w", stdout);
    while(scanf("%c",&line[i]) != EOF){
        if(isalpha(line[i])){
            printf("%c",line[i]);
            i++;
            continue;
        }
        else if(precedence(line[i]) == 0){
            i++;
            continue;
        }
        else if(top == -1){
            push(stack, line[i]);
            i++;
        }
        else if(precedence(line[i]) > precedence(stack[top])){
            push(stack, line[i]);
            i++;
        }
        else{
            if((top+1) > max){  //record the max num of top
                max = top+1;
            }
            while(top >= 0 && precedence(line[i]) <= precedence(stack[top])){
                op = pop(stack);
                printf("%c", op);
            }
            push(stack, line[i]);
            i++;
        }
    }
    while(top != -1){
        if((top+1) > max){
            max = top+1;
        }
        op = pop(stack);
        printf("%c",op);
    }
    printf("\n%d\n",max);
    fclose(rfp);
    fclose(wfp);
    return 0;
}
