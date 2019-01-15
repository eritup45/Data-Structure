#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct{
    int s, n, w;
}Edge;

Edge edge[1000];
int roots[1000], etot=0;

int cmp(const void *a, const void *b){
    Edge *A = (Edge *)a;
    Edge *B = (Edge *)b;
    int tmp = A->w - B->w;
    if(tmp == 0){
        return A->s - B->s;
    }
    return tmp;
}

int find(int x){
    return roots[x] < 0 ? x : ( roots[x] = find(roots[x]) );
}

void unite(int x, int y){   //@@
    int sroot = find(x);
    int nroot = find(y);
    if(roots[sroot] <= roots[nroot]){
        roots[sroot] += roots[nroot];
        roots[nroot] = sroot;   //@@
    }
    else{
        roots[nroot] += roots[sroot];
        roots[sroot] = nroot;
    }
}

void kruskal(int tot){
    int sroot, nroot, i=0, j=0;
    for(i=0; i<tot; i++){
        sroot = find(edge[i].s);
        nroot = find(edge[i].n);
        if(sroot != nroot){
            printf("%d %d %d\n", edge[i].s+1, edge[i].n+1, edge[i].w);
            unite(edge[i].s, edge[i].n);
        }
    }
}

int main(){
    memset(roots, -1, sizeof(roots));
    int i=0, j=0, msize, element;
    freopen("5input_3.txt", "r", stdin);
    scanf("%d", &msize);
    for(i=0; i<msize; i++){
        for(j=0; j<msize; j++){
            scanf("%d", &element);
            if(element && i < j){
                edge[etot].s = i;
                edge[etot].n = j;
                edge[etot++].w = element;
            }
        }
    }
    qsort(edge, etot, sizeof(Edge), cmp);
    kruskal(etot);
    return 0;
}
