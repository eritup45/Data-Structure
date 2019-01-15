#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define mtx 10

typedef struct {
    int u,v,w;  //from u to v, weight
}Edge;

int subset[mtx];
Edge edge[mtx];

int cmp(const void *a,const void *b){
    return (*(Edge *)a).w-(*(Edge *)b).w;
}

int find(int i){    //find set collapsing
    return subset[i]<0?i:(subset[i]=find(subset[i]));
}

void unionset(int X,int Y){
    int x=find(X),y=find(Y);

    if(subset[x]>subset[y]){
        subset[y]+=subset[x];
        subset[x]=y;
    }
    else{
        subset[x]+=subset[y];
        subset[y]=x;
    }
}

void kruskal(int n){
    int i,cnt=0;
    Edge mst[n];

    qsort(edge,n,sizeof(edge[0]),cmp);
    for(i=0;i<n;i++){
        if(find(edge[i].u)==find(edge[i].v))continue;
        mst[cnt++]=edge[i];
        unionset(edge[i].u,edge[i].v);
    }
    for(i=0;i<cnt;i++)
       printf("%d %d %d\n",mst[i].u,mst[i].v,mst[i].w);
}

int main(){
    int i,j,n=0,msize,element;
    char file[100],*ptr=NULL;
    FILE *fp=stdin;
    memset(subset,-1,sizeof(subset));   //initialize

    /*printf("File name: ");  //read file
    fgets(file,100,stdin);
    ptr=strtok(file," \n");
    fp=freopen(ptr,"r",stdin);*/

    freopen("5input_3.txt", "r", stdin);

    scanf("%d",&msize);
    for(i=0;i<msize;i++){
        for(j=0;j<msize&&scanf("%d",&element);j++){
            if(element&&i<j){   //matrix is symmetrical
                edge[n].u=i+1;
                edge[n].v=j+1;
                edge[n++].w=element;
            }
        }
    }
    kruskal(n);
    fclose(fp);
    return 0;
}
