#include<stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct vertex node;
typedef struct vertex{
    int vex;
    node *next;
}node;

typedef struct head{
    int cnt;
    node *next;
}link;

link *graph[100];

void insert(int i, int j){
    node *new = malloc(sizeof(node));
    new->vex = j;
    new->next = NULL;

    node *cur = graph[i]->next;
    if(cur == NULL){
        graph[i]->next = new;
    }
    else{
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = new;
    }

}

void topsort(int tot){
    int i=0, j=0;
    node *ptr;
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            if(graph[j]->cnt == 0){
                graph[j]->cnt = -1;
                break;
            }
        }
        printf("%d ",j+1);
        for(ptr = graph[j]->next; ptr != NULL; ptr = ptr->next){
            graph[ptr->vex]->cnt--;
        }
    }
}

int main(){
    int i=0, j=0, tot, tmp;
    FILE *fp = freopen("1input_2.txt", "r", stdin);
    scanf("%d", &tot);

    for(i=0; i<tot; i++){   //init
        graph[i] = malloc(sizeof(link));
        graph[i]->cnt = 0;
        graph[i]->next = NULL;
        //memset(graph[i],0,sizeof(link));
    }

    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            scanf("%d", &tmp);
            if(tmp == 1){
                graph[j]->cnt++;
                insert(i, j);
            }
        }
    }
    topsort(tot);
    return 0;
}
