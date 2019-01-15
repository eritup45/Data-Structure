#include<stdio.h>
#include<string.h>
typedef struct{
    int floor, step;
}Elevator;

Elevator que[1000];
int rear = -1, front = -1;

void push(Elevator item){
    que[++rear] = item;
}

Elevator pop(){
    return que[++front];
}

int bfs(int start, int end, int tot, int st[]){
    Elevator tmp, k;
    int visit[tot];
    memset(visit, 0, sizeof(visit));
    visit[start] = 1;
    tmp.floor = start;
    tmp.step = 0;
    push(tmp);
    while(front < rear){
        tmp = pop();
        if(tmp.floor == end){
            return tmp.step;
        }
        k.floor = tmp.floor + st[tmp.floor];
        if(( k.floor >= 1 && k.floor < tot )&& visit[k.floor] != 1 ){
            visit[k.floor] = 1; //@@
            k.step = tmp.step + 1;
            push(k);
        }
        k.floor = tmp.floor - st[tmp.floor];
        if(( k.floor >= 1 && k.floor < tot )&& visit[k.floor] != 1 ){
            visit[k.floor] = 1;
            k.step = tmp.step + 1;
            push(k);
        }
    }
    return -1;
}

int main(){
    int i=0;
    int start, end, tot;
    int st[1000];
    freopen("6input_3.txt", "r", stdin);
    scanf("%d %d %d", &tot, &start, &end);
    start--; end--;
    for(i=0; i<tot; i++)
        scanf("%d", &st[i]);
    printf("%d", bfs(start, end, tot, st));
    return 0;
}
