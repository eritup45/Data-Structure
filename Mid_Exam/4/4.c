#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct link{
    int num;
    struct link *next;
}link;
int listLen = 0;

void printlist(link *list){
    link *traverse = list;
    printf("Ouput:\n%d\n",listLen);
    while(traverse != NULL){
        printf("%d ",traverse->num);
        traverse = traverse->next;
    }
    return;
}
link *push(link *list,int num){
    link *traverse = list;
    link *tmp = NULL;
    listLen++;
    if(list == NULL){
        list = malloc(sizeof(link));
        list->num = num;
        list->next = NULL;
        return list;
    }
    else{
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        tmp = malloc(sizeof(link));
        tmp->num = num;
        tmp->next = NULL;
        traverse->next = tmp;
    }
    return list;
}
link *pop(link *list){
    listLen--;
    link *traverse = list;
    link *pre = traverse;
    if(list == NULL){
        listLen++;
        return list;
    }
    else if(list->next == NULL){
        free(list);
        list = NULL;
        return list;
    }
    else{
        while(traverse->next != NULL){
            pre = traverse;
            traverse = traverse->next;
        }
        pre->next = NULL;
        free(traverse);
        return list;
    }
}
int main(){
    link *list = NULL;
    char line[100],*tmp=NULL;
    int i=0,j=0,k=0,num;
    FILE *fp;
    fp = fopen("4input.txt","r");
    while(fgets(line,100,fp)){
        if(tmp = strstr(line,"Push ")){
            num = atoi(tmp+5);
            list = push(list,num);
        }
        else if(tmp = strstr(line,"Pop")){
            list = pop(list);
        }
    }
    printlist(list);
    return 0;
}
