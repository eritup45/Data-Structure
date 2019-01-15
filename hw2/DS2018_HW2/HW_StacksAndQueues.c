#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_maze_size 17
#define max_stack_size 1000

struct Data
{
    int row;
    int col;
};
typedef struct Data data;

int mazeA[max_maze_size][max_maze_size], mazeB[max_maze_size][max_maze_size];
int Atop, Btop;
int flagA, flagB;
data *Astack, *Bstack;

void pop(data *arr, int Top)
{
    if(Top < 0)
    {
        printf("The stack doesn't have any datum.\n");
        return ;
    }
    Top--;
    return ;
}

data top(data *arr, int Top)
{
    if(Top < 0)
    {
        printf("The stack doesn't have any datum.\n");
        return ;
    }
    data temp;
    temp.row = arr[Top].row;
    temp.col = arr[Top].col;
    return temp;
}

void push(data *arr, int Top, data input)
{
    Top++;
    arr[Top].row = input.row;
    arr[Top].col = input.col;
    return ;
}

void dfsA()
{
    data des_now;
    if(flagA)
    {
        dfsB();
        return ;
    }
    des_now = top(Astack, Atop);
    //printf("ratA(%d,%d)\n", des_now.row-1, des_now.col-1);
    if(des_now.row == max_maze_size - 2 && des_now.col == max_maze_size - 2)
    {
        flagA = 1;
        return ;
    }
    if(!flagA && !mazeA[des_now.row][des_now.col+1])
    {
        des_now.col++;
        push(Astack, Atop++, des_now);
        dfsB();
        des_now.col--;
    }
    if(!flagA && !mazeA[des_now.row+1][des_now.col])
    {
        des_now.row++;
        push(Astack, Atop++, des_now);
        dfsB();
        des_now.row--;
    }
    if(!flagA && !mazeA[des_now.row-1][des_now.col])
    {
        mazeA[des_now.row][des_now.col] = 1;
        des_now.row--;
        push(Astack, Atop++, des_now);
        dfsB();
        des_now.row++;
    }
    if(!flagA && !mazeA[des_now.row][des_now.col-1])
    {
        mazeA[des_now.row][des_now.col] = 1;
        des_now.col--;
        push(Astack, Atop++, des_now);
        dfsB();
        des_now.col++;
    }
    pop(Astack, Atop--);
    return ;
}

void dfsB()
{
    int flag_dfsB = 0;
    data des_now;
    if(flagB)
    {
        dfsA();
        return ;
    }
    des_now = top(Bstack, Btop);
    printf("ratB(%d,%d)\n", des_now.row, des_now.col);
    if(des_now.row == 1 && des_now.col == 1)
    {
        flagB = 1;
        return ;
    }
    if(!flagB && !mazeB[des_now.row][des_now.col-1])
    {
        des_now.col--;
        push(Bstack, Btop++, des_now);
        dfsA();
        des_now.col++;
    }
    if(!flagB && !mazeB[des_now.row-1][des_now.col])
    {
        des_now.row--;
        push(Bstack, Btop++, des_now);
        dfsA();
        des_now.row++;
    }
    if(!flagB && !mazeB[des_now.row+1][des_now.col])
    {
        mazeB[des_now.row][des_now.col] = 1;
        des_now.row++;
        push(Bstack, Btop++, des_now);
        dfsA();
        des_now.row--;
    }
    if(!flagB && !mazeB[des_now.row][des_now.col+1])
    {
        mazeB[des_now.row][des_now.col] = 1;
        des_now.col++;
        push(Bstack, Btop++, des_now);
        dfsA();
        des_now.col--;
    }
    pop(Bstack, Btop--);
    return ;
}

int main()
{
    int i, j;
    freopen("maze.txt", "r", stdin);//open file
    //freopen("result.txt", "w", stdout);
    for(i = 0; i < max_maze_size; i++)//initialize
    {
        for(j = 0; j < max_maze_size; j++)
        {
            mazeA[i][j] = 1;
            mazeB[i][j] = 1;
        }
    }
    Atop = Btop = -1;
    flagA = flagB = 0;
    Astack = malloc(max_stack_size * sizeof(data));
    Bstack = malloc(max_stack_size * sizeof(data));
    data temp;
    temp.row = temp.col = 1;
    push(Astack, Atop++, temp);
    temp.row = temp.col = max_maze_size-2;
    push(Bstack, Btop++, temp);
    for(i = 1; i < max_maze_size-1; i++)//read maze
    {
        char input[100];
        memset(input, 0, sizeof(input));
        fgets(input, 100, stdin);
        for(j = 1; j < max_maze_size-1; j++)
        {
            mazeA[i][j] = input[j-1] - '0';
            mazeB[i][j] = input[j-1] - '0';
        }
    }
    dfsA();
    //dfsB();
    return 0;
}
