//implement circular queue
//  maxsize=6
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void enqueue(int *queue, int num, int *front, int *rear){
    *rear = ((*rear) + 1) % 6;
    if(*front == *rear){
        printf("The queue is full.\n");
        (*rear)--;
        if(*rear == -1)
            *rear = 5;
        return;
    }
    else{
        queue[(*rear)] = num;
        return;
    }
}
int dequeue(int *queue, int *front, int *rear){
    if(*front == *rear){
        printf("The queue is empty.\n");
        return -1;
    }
    else{
        *front = ((*front) + 1) % 6;
        return queue[(*front)];
    }
}
void display(int *queue, int front, int rear){
    int i=0;
    if(front == rear){
        printf("The queue is empty.\n");
        return;
    }
    for(i = front + 1; i != rear + 1; i++){
        i = i % 6;
        printf("%d ", queue[i]);
    }
    printf("\n");
    return;
}
int main(){
    int queue[6], front=0, rear=0, op, num;
    freopen("8input.txt", "r", stdin);
    freopen("8output.txt", "w", stdout);
    while(scanf("%d", &op) != EOF){
        if(op == 1){
            scanf("%d", &num);
            enqueue(queue, num, &front, &rear);
        }
        else if(op == 2){
            num = dequeue(queue, &front, &rear);
        }
        else if(op == 3){
            display(queue, front, rear);
        }
    }
    return 0;
}
