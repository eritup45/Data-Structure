#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>

void parse(char*, int*, int*);
int exist(int**, int, int);
void insert(int**, int);

int main(){
        FILE* f = fopen("12input.txt", "r");
        int relations[512][512], total = 0;
        char line[1024];
        int a, b ;

        while(fgets(line, 1024, f) != NULL){
                parse(line, &a, &b);

                if(!exist(relations, total, a) && !exist(relations, total, b)){
                       relations[total][0] = a;
                       relations[total][1] = b;
                }
        }

        fclose(f);
        return 0;
}

void parse(char* str, int* a, int* b){
        *a = atoi(str);
        *b = atoi(strstr(str, " ") + 1);
}

int exist(int* r[512], int tot, int n){
        int i, j;
        for(i = 0; i < tot; i++){
                for(j = 1; j < r[i][0] + 1; j++){
                        if(n == r[i][j])
                                return 1;
                }
        }
        return 0;
}

void insert(int* h[512], int n){
}
