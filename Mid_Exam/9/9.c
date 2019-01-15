#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct bst{
    int data;
    struct bst *l;
    struct bst *r;
}bst;

void inorder(bst *tree){
    if(tree == NULL)    return;
    inorder(tree->l);
    printf("%d ",tree->data);
    inorder(tree->r);
}
void postorder(bst *tree){
    if(tree == NULL)    return;
    postorder(tree->l);
    postorder(tree->r);
    printf("%d ",tree->data);
}
void preorder(bst *tree){
    if(tree == NULL)    return;
    printf("%d ",tree->data);
    preorder(tree->l);
    preorder(tree->r);
}
bst *insert(bst *tree, int num){
    if(tree == NULL){
        tree = malloc(sizeof(bst));
        tree->data = num;
        tree->l = NULL;
        tree->r = NULL;
        return tree;
    }
    else if(num < tree->data){
        tree->l = insert(tree->l, num);
    }
    else if(num > tree->data){
        tree->r = insert(tree->r, num);
    }
    return tree;
}

int main(){
    bst *tree = NULL;
    char *token, line[1024];
    FILE *fp;
    int num, i=0;
    fp = fopen("9input.txt", "r");
    fgets(line, 1024, fp);
    token = strtok(line, " \r\n");
    num = atoi(token);
    tree = insert(tree ,num);
    while(token = strtok(NULL, " \r\n")){
        num = atoi(token);
        tree = insert(tree, num);
    }
    inorder(tree);
    printf("\n");
    postorder(tree);
    printf("\n");
    preorder(tree);
    printf("\n");
    fclose(fp);
    return 0;
}
