#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int vstart;
    int vnext;
    int weight;
}Edge;

void print_file(Edge edgeSet[], int edgeSetNum){
    //freopen("output.txt", "w", stdout);
    int i=0;
    for(i=0; i<edgeSetNum; i++)
        printf("%d %d %d\n", edgeSet[i].vstart+1, edgeSet[i].vnext+1, edgeSet[i].weight);
}

/*int cmp(const void *a,const void *b){
    int tmp = (*(Edge *)a).weight-(*(Edge *)b).weight;
    if(tmp == 0)
        return (*(Edge *)a).vstart - (*(Edge *)b).vstart;
    return (*(Edge *)a).weight-(*(Edge *)b).weight;
}*/

int cmp(const void *a, const void *b){
    int tmp = 0;
    Edge *A = (Edge *)a;    //@@
    Edge *B = (Edge *)b;
    tmp = A->weight - B->weight;    //@@
    if(tmp == 0)
        return A->vstart - B->vstart;
    return tmp;
}

void get_increaseWeight(Edge increaseWeight[], int *totEdgeNum){
    int i=0, j=0, k=0, tot=0;
    int adjM[100][100] = {0};
    Edge tmp[1000];
    FILE *fp = fopen("5input_3.txt", "r");
    fscanf(fp, "%d", &tot);
    for(i=0; i<tot; i++){
        for(j=0; j<tot; j++){
            fscanf(fp, "%d", &adjM[i][j]);
            if(adjM[i][j] != 0){
                tmp[k].vstart = i;
                tmp[k].vnext = j;
                tmp[k++].weight = adjM[i][j];
            }
        }
    }
    qsort(tmp, k, sizeof(Edge), cmp);   //@@
    *totEdgeNum = k / 2;
    for(i=0, j=0; i<*totEdgeNum; i++, j+=2){
        increaseWeight[i].vstart = tmp[j].vstart;
        increaseWeight[i].vnext = tmp[j].vnext;
        increaseWeight[i].weight = tmp[j].weight;
        //printf("%d %d = %d\n", increaseWeight[i].vstart, increaseWeight[i].vnext, increaseWeight[i].weight);
    }
    fclose(fp);
}

int find_root(int rootSet[], int num){
    return rootSet[num] < 0 ? num : (rootSet[num] = find_root(rootSet, rootSet[num]));
}

/*int find_root(int rootSet[], int num){
    int root = num, parent;
    while(rootSet[root] >= 0){  //@@
        root = rootSet[root];
    }
    while( root != num ){   //<(@w@)>
        parent = rootSet[num];  //@@
        rootSet[num] = root;    //@@
        num = parent;       //@@
    }
    return root;
}*/

void unite_set(int rootSet[], int vstart, int vnext){
    int sroot = find_root(rootSet, vstart);
    int nroot = find_root(rootSet, vnext);

    if(rootSet[sroot] <= nroot){    //@@
        rootSet[sroot] += rootSet[nroot];   //@@
        rootSet[nroot] = sroot; //@@
    }
    else{
        rootSet[nroot] += rootSet[sroot];
        rootSet[sroot] = nroot;
    }
}

int main(){
    int i=0, j=0;
    int edgeSetNum=0, totEdgeNum=0;
    Edge edgeSet[1000], increaseWeight[1000];
    get_increaseWeight(increaseWeight, &totEdgeNum);

    int rootSet[1000];
    memset(rootSet, -1, sizeof(int) * 1000);

    int sroot, nroot;
    for(i=0; i<totEdgeNum; i++){
        sroot = find_root(rootSet, increaseWeight[i].vstart);
        nroot = find_root(rootSet, increaseWeight[i].vnext);
        if(sroot != nroot){ //find won't make circle
            edgeSet[edgeSetNum++] = increaseWeight[i];
            unite_set(rootSet, increaseWeight[i].vstart, increaseWeight[i].vnext);
        }
    }
    print_file(edgeSet, edgeSetNum);
    return 0;
}
