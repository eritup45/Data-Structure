#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Elevator
{
    int lift, step; //lift = 該樓層, step = 該樓層走的步數
} Elevator;
int start, finish, n, front = -1, rear = -1;
Elevator que[1000];
void que_push(Elevator ele)
{
    que[++rear] = ele;
}
Elevator que_pop(void)
{
    return que[++front];
}
int bfs(int *st, int *visit)
{
    Elevator tmp, k;
    tmp.lift = start; //存入起始位置
    tmp.step = 0;
    visit[tmp.lift] = 1;
    que_push(tmp);
    while(front < rear)
    {
        tmp = que_pop();
        if(tmp.lift == finish)
            return tmp.step;
        k.lift = tmp.lift - st[tmp.lift]; //往下走
        if(k.lift >=0 && k.lift < n && !visit[k.lift])
        {
            k.step = tmp.step + 1;
            visit[tmp.lift] = 1;
            que_push(k);
        }
        k.lift = tmp.lift + st[tmp.lift]; //往上走
        if(k.lift >= 0 && k.lift < n && !visit[k.lift])
        {
            visit[tmp.lift] = 1;
            k.step = tmp.step + 1;
            que_push(k);
        }
    }
    return -1;
}
int main()
{
    freopen("6input_1.txt", "r", stdin);
    scanf("%d %d %d", &n, &start, &finish);
    start--; //改陣列起始位址為0
    finish--;
    int i, st[n], visit[n];
    memset(visit, 0, sizeof(visit));
    for(i = 0; i < n; i++)
        scanf("%d", &st[i]);
    printf("%d\n", bfs(st, visit));
    return 0;
}
