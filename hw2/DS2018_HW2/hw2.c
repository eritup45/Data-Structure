#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>

typedef struct{
        int row;
        int col;
        int dir;
}element;

int readMaze(char*, int**);
void free2D(int**, int);

int dirTableA[4][2] = {
        {0, 1},         //0
        {1, 0},         //1
        {-1, 0},        //2
        {0, -1}         //3
};

int dirTableB[4][2] = {
        {0, -1},        //0
        {-1, 0},        //1
        {1, 0},         //2
        {0, 1}          //3
};

int main(int argc, char* argv[]){
        int** maze = NULL;
        int aMark[15][15];
        int bMark[15][15];
        element aStack[255];
        element bStack[255];
        int aTop = -1, bTop = -1;

        int i, j;
        int aRow = 0, aCol = 0, bRow = 14, bCol = 14;

        maze = (int**)malloc(sizeof(int*) * 15);
        for(i = 0; i < 15; i++)
                maze[i] = (int*)malloc(sizeof(int) * 15);

        if(argv[1]){
                if(!readMaze(argv[1], maze)){
                        printf("Read maze file failed.\n");
                        return -1;
                }
        }
        else{
                if(!readMaze("maze.txt", maze)){
                        printf("Read maze file failed.\n");
                        return -1;
                }
        }

        /* mark[] set zero */
        for(i = 0; i < 15; i++){
                for(j = 0; j < 15; j++){
                        aMark[i][j] = 0;
                        bMark[i][j] = 0;
                }
        }

        int afterRow, afterCol;

        while(aRow != 14 || aCol != 14){
                aMark[aRow][aCol] = 1;

                printf("%d, %d\n", aRow, aCol);

                for(i = 0; i < 4; i++){
                        afterRow = aRow + dirTableA[i][0];
                        afterCol = aCol + dirTableA[i][1];

                        if(afterRow >= 0 && afterRow < 15 && afterCol >= 0 && afterCol < 15){
                                if(maze[afterRow][afterCol] == 0 && aMark[afterRow][afterCol] == 0)
                                        break;
                        }
                }

                if(i == 4){
                        /* no way to go, go back to last position, then move the "top" index down 1 block */
                        aRow = aStack[aTop].row;
                        aCol = aStack[aTop].col;

                        aTop--;
                }
                else{
                        /* push current x, y, dir into stack */
                        aStack[++aTop].row = aRow;
                        aStack[aTop].col = aCol;
                        aStack[aTop].dir = i;

                        aRow = afterRow;
                        aCol = afterCol;
                }
        }

        for(i = 0; i < aTop; i++)
                printf("%d", aStack[i].dir);

        free2D(maze, 15);

        return 0;
}

int readMaze(char* fileName, int** m){
        FILE* file = fopen(fileName, "r");
        char line[1024];
        int i = 0, j;

        if(!file)
                return 0;
        else{
                while(fgets(line, 1024, file) != NULL){
                        for(j = 0; j < 15 ;j++)
                                m[i][j] = line[j] - '0';
                        i++;
                }
                return 1;
        }
}

void free2D(int** p, int r){
        int i;
        for(i = 0; i < r; i++)
                free(p[i]);
        free(p);
}
