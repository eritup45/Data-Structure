//implement maze problem and stack

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxmaze 17
typedef struct{
    int dir;
    int row;
    int col;
}movement;

void getMaze(int maze[][maxmaze]);
void movea(movement *next);
void moveb(movement *next);
void addq(movement result[], int *tmp, movement a[], int top);
void stackpush(movement a[], int *top, movement *next);
movement stackpop(movement a[], int *top);

int main(){
    int maze[maxmaze][maxmaze], marka[maxmaze][maxmaze], markb[maxmaze][maxmaze];  //maze's size is 15
    int i=0,j=0,k=0,topa=-1,topb=-1,tmpa,tmpb;
    FILE *fp;
    movement a[maxmaze*maxmaze], b[maxmaze*maxmaze], *next = NULL;
    movement resultA[2*maxmaze*maxmaze], resultB[2*maxmaze*maxmaze];
    next = malloc(sizeof(movement));
    getMaze(maze);
    getMaze(marka);
    getMaze(markb);
	fp=fopen("result.txt","w");

	//PATH A:
    //When dir == 0, East. When dir == 1, South. When dir == 2, North. When dir == 3, West.
    a[0].dir = 0;  a[0].col = 1;  a[0].row = 1; topa=0; tmpa=0;
    while((a[topa].row != maxmaze-2) || (a[topa].col != maxmaze-2)){

        next->dir = 0;
        while(next->dir < 4){    //search four direction for one time

            if(a[topa].row == maxmaze-2 && a[topa].col == maxmaze-2){   //break
                break;
            }

            movea(next);
            next->row = a[topa].row + next->row;
            next->col = a[topa].col + next->col;

            if(maze[next->row][next->col] == 1 || marka[next->row][next->col] == 1){    //change direction
                next->dir++;
            }
            else if(maze[next->row][next->col] == 0 && marka[next->row][next->col] == 0){   //add to stack and mark
                next->dir=0;
                stackpush(a, &topa, next);  //write next in a, and topa++

                marka[a[topa].row][a[topa].col]=1;

                addq(resultA, &tmpa, a, topa);  //write a in result

            }
        }
        if(a[topa].row == maxmaze-2 && a[topa].col == maxmaze-2){   //¥¼break
                break;
        }
        //topa--; //it is part of pop
        stackpop(a, &topa);
        if(topa == -1)//if no path exists, break.
                break;
        addq(resultA, &tmpa, a, topa);

    }

    //PATH B:
    //When dir == 0, West. When dir == 1, North. When dir == 2, South. When dir == 3, East.
    b[0].dir = 0;  b[0].col = maxmaze-2;  b[0].row = maxmaze-2; topb = 0; tmpb = 0;
    while((b[topb].row != 1) || (b[topb].col != 1)){

        next->dir = 0;
        while(next->dir < 4){    //search four direction for one time

            if(b[topb].row == 1 && b[topb].col == 1){
                break;
            }

            moveb(next);
            next->row = b[topb].row + next->row;
            next->col = b[topb].col + next->col;

            if(maze[next->row][next->col] == 1 || markb[next->row][next->col] == 1){
                next->dir++;
            }
            else if(maze[next->row][next->col] == 0 && markb[next->row][next->col] == 0){   //add to stack and mark
                stackpush(b, &topb, next);

                next->dir=0;
                markb[b[topb].row][b[topb].col]=1;

                addq(resultB, &tmpb, b, topb);
            }
        }
        if(b[topb].row == 1 && b[topb].col == 1){   //¥¼break
                break;
        }
        stackpop(a, &topb);
        //topb--; //it is part of pop
        if(topb == -1){
                printf("error! topb=-1!!");
                break;
        }

        addq(resultB, &tmpb, b, topb);
    }
    fprintf(fp,"ratA(0,0)\n");
    fprintf(fp,"ratA(14,14)\n");
    k=0;
    while((k < tmpa) && (k < tmpb)){
        //if(k < tmpa)
            fprintf(fp,"ratA(%d,%d)\n",resultA[k].row-1,resultA[k].col-1);
        //if(k < tmpb)
            fprintf(fp,"ratB(%d,%d)\n",resultB[k].row-1,resultB[k].col-1);
        k++;
    }
    fclose(fp);
    return 0;
}

movement stackpop(movement a[], int *top){  //return a, then top--
    return a[(*top)--];
}
void stackpush(movement a[], int *top, movement *next){
    (*top)++;
    a[*top].row = next->row;
    a[*top].col = next->col;
}
void addq(movement result[], int *tmp, movement a[], int top){
    if(*tmp >= 2*maxmaze*maxmaze-1){
        //printf("error! too much element in queue!");
        return;
    }
    result[*tmp].row = a[top].row;
    result[*tmp].col = a[top].col;
    (*tmp)++;
}
void movea(movement *next){
    if(next->dir == 0){  //right
        next->row = 0;
        next->col = 1;
    }
    else if(next->dir == 1){ //down
        next->row = 1;
        next->col = 0;
    }
    else if(next->dir == 2){ //up
        next->row = -1;
        next->col = 0;
    }
    else if(next->dir == 3){ //left
        next->row = 0;
        next->col = -1;
    }
}
void moveb(movement *next){
    if(next->dir == 0){  //Left
        next->row = 0;
        next->col = -1;
    }
    else if(next->dir == 1){ //Up
        next->row = -1;
        next->col = 0;
    }
    else if(next->dir == 2){ //Down
        next->row = 1;
        next->col = 0;
    }
    else if(next->dir == 3){ //Right
        next->row = 0;
        next->col = 1;
    }
}

void getMaze(int maze[][maxmaze]){  //should give maxsize to input a two dimensional array
    int i=0,j=0;
    FILE *fp;
    fp=fopen("maze.txt","r");
    char tmp;
    for(i=1; i<maxmaze-1; i++){ //The maze (inside the 1's wall)
        for(j=1; j<maxmaze; j++){ //when j == maxmaze-1 ,tmp == '\n', so need to log one more. ('\n')
            tmp = fgetc(fp);
            if(tmp == '\n'){
                continue;
            }
            maze[i][j] = atoi(&tmp);
        }
    }
    for(i=0;i<maxmaze;i++){ //There is 1's wall outside.
        maze[i][0]=1;
        maze[i][maxmaze-1]=1;
        maze[0][i]=1;
        maze[maxmaze-1][i]=1;
    }
    fclose(fp);
}
