//參考網址: http://alrightchiu.github.io/SecondRound/minimum-spanning-treekruskals-algorithm.html

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int vstart; //start
    int vnext;
    int weight;
}edge;

//qsort edge i[]
int cmp(const void * a, const void * b){
    edge *pA = (edge *)a;
    edge *pB = (edge *)b;
    int tmp = pA->weight - pB->weight;
    if(tmp == 0)
        return pB->vstart - pA->vstart;
    else
        return tmp;
}

//get every edges in increase order (compare weight)
void get_increaseWeight(edge increaseWeight[], int *totEdgeNum){
    int i=0, j=0, totLine=0, adjM[100][100];
    char line[1024];
    edge tmp[10000];
    printf("Please input file name:");
    scanf("%s", line);
    FILE *fp = fopen(line, "r");
    fscanf(fp, "%d", &totLine);
    for(i=0; i<totLine; i++){
        for(j=0; j<totLine; j++){
            fscanf(fp, "%d", &adjM[i][j]);
            if(adjM[i][j] != 0){
                tmp[*totEdgeNum].vstart = i;  //start from 0, not 1
                tmp[*totEdgeNum].vnext = j;
                tmp[(*totEdgeNum)++].weight = adjM[i][j];
            }
        }
    }
    qsort(tmp, *totEdgeNum, sizeof(edge), cmp);
    for(i=0, j=0; i<*totEdgeNum; i+=2, j++){
        increaseWeight[j] = tmp[i+1];
    }
    (*totEdgeNum) /= 2;

    fclose(fp);
}

//return root's position
int find_root(int rootSet[], int num){
    int root, parent;
    root = num;
    while(rootSet[root] >= 0)   //找出root's position
        root = rootSet[root];
    while(num != root){ //同步其他rootSet的值
        parent = rootSet[num];
        rootSet[num] = root;
        num = parent;
    }
    return root;
}

void unite_set(int rootSet[], int vstart, int vnext){
    int sroot = find_root(rootSet, vstart);
    int nroot = find_root(rootSet, vnext);

    if(rootSet[sroot] <= rootSet[nroot]){       //rootSet[sroot]小於零
        rootSet[sroot] += rootSet[nroot];       //vstart比較多element的時候, 以vstart作為root
        rootSet[nroot] = sroot;
    }
    else{
        rootSet[nroot] += rootSet[sroot];       //會越加越小
        rootSet[sroot] = nroot;
    }
}

int main(){
    int i=0, j=0, edgeSetNum=0, totEdgeNum=0, totLine=0;
    edge edgeSet[10000], increaseWeight[10000];
    get_increaseWeight(increaseWeight, &totEdgeNum);

    int rootSet[totEdgeNum]; //If isroot < 0, it's a root.
    for(i=0; i<totEdgeNum; i++){
        rootSet[i] = -1;
    }
    int sroot, nroot, weight=0;
    for(i=0; i<totEdgeNum; i++){
        sroot = find_root(rootSet, increaseWeight[i].vstart);
        nroot = find_root(rootSet, increaseWeight[i].vnext);
        if(sroot != nroot){
            edgeSet[edgeSetNum++] = increaseWeight[i];
            unite_set(rootSet, increaseWeight[i].vstart, increaseWeight[i].vnext);
        }
    }

    for(i=0; i<edgeSetNum; i++){
        printf("Edge %d:<%d %d> cost:%d\n", i+1, edgeSet[i].vstart+1, edgeSet[i].vnext+1, edgeSet[i].weight); //*****記得+1*****
        weight += edgeSet[i].weight;
    }
    printf("Minimum cost = %d\n", weight);
    return 0;
}
