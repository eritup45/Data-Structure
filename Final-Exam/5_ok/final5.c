#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int s, n, w;
}Edge;

Edge edgeSet[1000];
int rootSet[1000];

int cmp(const void *a, const void *b){
    Edge *A = (Edge *)a;
    Edge *B = (Edge *)b;
    int tmp = A->w - B->w;
    if(tmp == 0)
        return A->s - B->n;
    return tmp;
}

int root(int r){
    return rootSet[r] < 0 ? r : (rootSet[r] = root(rootSet[r]));
}

void unite(int x, int y){
    int xroot = root(x);
    int yroot = root(y);
    if(xroot <= yroot){
        rootSet[xroot] += rootSet[yroot];
        rootSet[yroot] = xroot; //<(@w@)>
    }
    else{
        rootSet[yroot] += rootSet[xroot];
        rootSet[xroot] = yroot;
        //xroot = yroot;
    }
}

void kruskal(int tot){
    int i=0;
    int sroot;
    int nroot;
    for(i=0; i<tot; i++){
        sroot = root(edgeSet[i].s);
        nroot = root(edgeSet[i].n);
        if(sroot != nroot){
            printf("%d %d %d\n", edgeSet[i].s+1, edgeSet[i].n+1, edgeSet[i].w);
            unite(edgeSet[i].s, edgeSet[i].n);  //<(@w@)>
        }
    }
}

int main(){
    int i=0, j=0, msize, element, tot=0;
    memset(rootSet, -1, sizeof(int)*1000);
    FILE *fp = freopen("5input_2.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &element);
            if(element && i<j){
                edgeSet[tot].s = i;
                edgeSet[tot].n = j;
                edgeSet[tot++].w = element;
            }
        }
    }
    qsort(edgeSet, tot, sizeof(Edge), cmp);

    kruskal(tot);
    return 0;
}
