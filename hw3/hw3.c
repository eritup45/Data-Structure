/*
    Implement by circular and double linked list.
        Implement Russian Roulette.
        skip: skip some person, and delete a node
        finally print the last person
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
typedef struct link{
    char name[100];
    struct link *rnext;
    struct link *lnext;
}link;
int listLenth = 0;
int skipNum,option;

void usage(){
    printf("what do you want to do?\n\n");
    printf("\t(1)Read data from a file\n");
    printf("\t(2)Append new nodes\n");
    printf("\t(0)Exit\n");
}
void printList(link *list){
        printf("the list datas are :\n[");
		link *cur=list;
		if(list==NULL){//the first data
				printf("error! (list==NULL)\n");
		}
		else if(cur == list){//the first data
            printf("%s",cur->name);
            cur=cur->rnext;
		}
		while(cur!=list){//print till the first data
				printf(", %s",cur->name);
				cur=cur->rnext;
		}
		printf("]\n");
}

link *insert(link *list, char name[]){  //insert in the back and make circular
    link *tmp = NULL;
    link *traverse = list;
    listLenth++;
    if(list == NULL){
        list = malloc(sizeof(link));    //remember to malloc!
        strcpy(list->name, name);
        list->rnext = list;
        list->lnext = list;
        return list;
    }
    else{
        tmp = malloc(sizeof(link));
        while(traverse->rnext != list){
            traverse = traverse->rnext;
        }
        strcpy(tmp->name, name);
        tmp->rnext = list;  //circular
        tmp->lnext = traverse;
        traverse->rnext = tmp;
        list->lnext = tmp;  //circular

        return list;
    }
}

link *readFile(link *list){
    char name[100];
    int len;
    FILE *fp;
    fp = fopen("data.csv", "r");
    printf("Start read data from a file\n");
    while(fgets(name, 100, fp)){
        len = strlen(name);
        name[len-1] = '\0'; //linux => len-2
        list = insert(list, name);
        printf("%s is appended\n", name);
    }
    fclose(fp);
    return list;
}

link *addNode(link *list){
    char line[20];
    int num,i=0,len=0;
    printf("how many nodes do you want to append.\n");
    fgets(line, 20, stdin);
    num = atoi(line);
    for(i=0; i<num; i++){
        fgets(line, 20, stdin);
        len = strlen(line);
        line[len-1]='\0';
        printf("%s is appended\n", line);

        list = insert(list, line);
    }
    return list;
}

link *listDelete(link *list, char name[]){
    link *traverse = list;
    link *pre = list;
    if(list->rnext == list){//only one link
        //printf("Notice! do not delete the last name\n");
        return list;
    }
    else if(strcmp(list->name, name) == 0){  //delete the first //still need to link the last to the first
            listLenth--;
            while(traverse->rnext != list){
                traverse = traverse->rnext;
            }
            list = list->rnext;
            list->lnext = traverse;
            free(pre);
            traverse->rnext = list;

            return list;
    }
    //while(traverse->rnext != list){
    traverse = traverse->rnext; //delete second word, or after
    while(traverse != list){
        if(strcmp(traverse->name, name) == 0){
                listLenth--;
                pre->rnext = traverse->rnext;
                traverse->rnext->lnext = pre;
                free(traverse);
                return list;
        }
        pre = traverse;
        traverse = traverse->rnext;
    }
    return list;
}

link *skip(link *list){
    int dir,i=0;
    link *traverse = list;
    printf("choose direction\n\n");
    printf("\t(1)right\n");
    printf("\t(2)left\n");
    //scanf("%d", &dir);
    //scanf("%d", &skipNum);

    //windows' shit : '\r'
    char redundantshit[100];
    fgets(redundantshit, 100, stdin);
    dir = atoi(redundantshit);

    if(option == 1){    //decide the skipNum variable
        skipNum = rand()%listLenth;
        printf("the skip number is : %d\n",skipNum);
    }

    else if(option == 2){
        printf("Input skip number\n");
        fgets(redundantshit, 100, stdin);
        skipNum = atoi(redundantshit);
        printf("the skip number is : %d\n",skipNum);
   }

    if(dir == 1){
        while(list->rnext != list){
           for(i=0; i<=skipNum; i++){
                traverse = traverse->rnext; //deletion go right
            }
            printf("list length is : %d\n",listLenth);
            printf("the data is poped : %s\n",traverse->name);
            list = listDelete(list, traverse->name);
        }
        printf("the last name is : %s\n",list->name);
    }
    else if(dir == 2){
        while(list->lnext != list){
            for(i=0; i<=skipNum; i++){
                traverse = traverse->lnext; //deletion go left
            }
            printf("list length is : %d\n",listLenth);
            printf("the data is poped : %s\n",traverse->name);
            list = listDelete(list, traverse->name);
        }
        printf("the last name is : %s\n",list->name);
    }
    return list;
}

int main(){
    srand(time(NULL));
    link *list = NULL;
    char line[20];
    while(1){
        usage();
        //to meet window
        fgets(line, 20,stdin);
        option = atoi(line);

        if(option == 0) return 0;
        else if(option == 1){
            list = readFile(list);
            printList(list);
            list = skip(list);

            //initialize
            listLenth = 0;
            free(list);
            list = NULL;
        }
        else if(option == 2){
            list = addNode(list);
            printList(list);
            list = skip(list);

            //initialize
            listLenth = 0;
            list = NULL;
        }
    }
    return 0;
}
