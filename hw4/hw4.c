#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct bst{
    int data;
    struct bst *l;
    struct bst *r;
}bst;
int delete_flag = 1;
int search_flag = 0;

void modeUsage(){
    printf("(1)Binary Search Tree.\n");
    printf("(2)Treasure Hunter.\n");
    printf("(0)Exit.\n");
}

void bstUsage(){
    printf("(I)nsert a number.\n");
    printf("(D)elete a number.\n");
    printf("(S)earch a number.\n");
    printf("(P)rint Infix & Level order.\n");
    printf("(R)eturn\n");
}

void inorder(bst *tree){
    if(tree == NULL)    return;
    inorder(tree->l);
    printf("%d ",tree->data);
    inorder(tree->r);
}

bst *insert(bst *tree, int num){
    if(tree == NULL){
        tree = malloc(sizeof(bst));
        tree->data = num;
        tree->l = NULL;
        tree->r = NULL;
        return tree;
    }
    else if(num == tree->data){
        printf("Error. Number %d exists.\n",num);
    }
    else if(num < tree->data){
        tree->l = insert(tree->l, num);
    }
    else if(num > tree->data){
        tree->r = insert(tree->r, num);
    }
    return tree;
}

// Go through the right once, and go to the end of the left. Delete it!!.
bst *delete_a_node(bst *tree){
    bst *pre = tree, *traverse;
    //This node is a leaf node, delete directly.
    if( !tree->l && !tree->r ){
        free(tree);
        tree = NULL;
    }
    //tree->l == NULL, reconnect its right subtree
    else if(!tree->l){//忘記free了
        tree->data = tree->r->data;
        tree->l = tree->r->l;
        tree->r = tree->r->r;
    }
    //tree->r == NULL, reconnect its left subtree
    else if(!tree->r){
        tree->data = tree->l->data;
        tree->r = tree->l->r;
        tree->l = tree->l->l;
    }
    //left and right subtrees are not empty
    else{
        traverse = tree->r;
        //turn right, and turn left to the end
        while(traverse->l != NULL){
            pre = traverse;
            traverse = traverse->l;
        }
        tree->data = traverse->data;
        //It is common case.
        //if pre != tree (not the second one), "previous" tree's left subtree should link to deleted tree's right
        if(pre != tree)
            pre->l = traverse->r;
        //It is special case.
        //since the second one is going to be deleted, just refill the second's right tree to the previous(tree's) right
        else if(pre == tree)
            pre->r = traverse->r;   //traverse is equal to the second one (is going to be deleted)
    }
    return tree;
}

bst *bst_delete(bst *tree, int num){
    if(tree == NULL)    //delete nothing
        delete_flag = 0;
    else if(tree->data == num){
        tree = delete_a_node(tree);
    }
    else if(num < tree->data){
        tree->l = bst_delete(tree->l, num);
    }
    else if(num > tree->data){
        tree->r = bst_delete(tree->r, num);
    }
    return tree;
}

void bst_search(bst *tree,int num){ //Search the num exists or not
    search_flag = 0;    //initialize
    if(tree == NULL){
        //printf("SORRY. Number not founded.\n");
    }
    else if(tree->data == num){
        //printf("Bingo! Number is founded.\n");
        search_flag = 1;
    }
    else if(num < tree->data)
        bst_search(tree->l, num);
    else if(num > tree->data)
        bst_search(tree->r, num);
}

void level_order(bst *tree){
    int front=0, rear=0;
    bst *queue[1024], *cur;
    //push root in the first of the queue
    queue[++rear] = tree;
    while(1){
        if(front == rear)
            break;
        cur = queue[++front];   //pop previous node in queue
        if(cur){
            printf("%d ", cur->data);
            if(cur->l)
                queue[++rear] = cur->l; //if left has data, push it in queue
            if(cur->r)
                queue[++rear] = cur->r; //if right has data, push it in queue
        }
        else
            break;
    }
}

//If containing a word is bomb, delete. delete return 1. else return 0.
int is_contain_bomb(bst *tree, int bomb){
    int num, tmpData = tree->data;
    if(tmpData == 0 && bomb == 0)   //delete 0 should also be considered
        return 1;
    while(tmpData != 0){
        num = tmpData % 10;
        if(num == bomb){
            return 1;
        }
        tmpData /= 10;
    }
    return 0;
}

//should use postorder
bst *hunter_delete_bomb(bst *tree, int bomb){
    if(tree == NULL)
        return;
    tree->l = hunter_delete_bomb(tree->l, bomb);
    tree->r = hunter_delete_bomb(tree->r, bomb);
    if(is_contain_bomb(tree, bomb)){
        printf("Number %d is deleted.\n", tree->data);
        tree = delete_a_node(tree);
        return tree;
    }
    return tree;
}

void print_hunter_least_path(bst *tree, int key, int trea_location){
    int top = -1, firstFlag = 0;
    bst *stack[1024], *cur = tree;
    printf("%d",cur->data);
    while(cur != NULL){ //print till key and put path in stack
        stack[++top] = cur;
        if(key == cur->data){   // print out latter
            break;
        }
        else if(key < cur->data){
            if(firstFlag != 0){
                printf("->%d",cur->data);
                cur = cur->l;
            }
            else{   //the first don't need to print
                firstFlag = 1;
                cur = cur->l;
            }
        }
        else if(key > cur->data){
            if(firstFlag != 0){
                printf("->%d",cur->data);
                cur = cur->r;
            }
            else{   //the first don't need to print
                firstFlag = 1;
                cur = cur->r;
            }
        }
    }
    while(trea_location != cur->data){
        bst_search(cur, trea_location);
        if(search_flag == 1){
            while(cur != NULL){ //print till trea_location and put path in stack
                if(cur == stack[++top]){    //倒V時需要另外判斷
                    firstFlag = 0;
                }
                if(trea_location == cur->data){
                    printf("->%d",cur->data);
                    break;
                }
                else if(trea_location < cur->data){
                    if(firstFlag != 0){
                        printf("->%d",cur->data);
                        cur = cur->l;
                    }
                    else{
                        cur = cur->l;
                        firstFlag = 1;
                    }
                }
                else if(trea_location > cur->data){
                    if(firstFlag != 0){
                        printf("->%d",cur->data);
                        cur = cur->r;
                    }
                    else{
                        cur = cur->r;
                        firstFlag = 1;
                    }
                }
            }
        }
        else{
            cur = stack[top--];
            printf("->%d", cur->data);  //print 6 print 8
        }
    }
}

int main(){
    bst *tree = NULL;
    char *token, line[1024], option[10];
    FILE *fp;
    int len=0, num, i=0, key, trea_location, bomb;
    modeUsage();
    while(fgets(option, 10, stdin)){
        token = strtok(option, "\r\n");
        if(strcmp(token, "1") == 0){    //Section1 Binary Search Tree
            while(1){
                bstUsage();
                fgets(option, 10, stdin);       //
                token = strtok(option, "\r\n"); //
                if(strcmp(token, "I") == 0){
                    printf("Enter a number: ");
                    fgets(option, 10, stdin);       //
                    token = strtok(option, "\r\n"); //
                    num = atoi(token);              //
                    tree = insert(tree, num);
                    printf("Number %d is inserted.\n", num);
                }
                else if(strcmp(token, "D") == 0){
                    printf("Enter a number to delete : ");
                    fgets(option, 10, stdin);       //
                    token = strtok(option, "\r\n"); //
                    num = atoi(token);              //
                    tree = bst_delete(tree, num);
                    if(delete_flag == 0){
                        printf("Number not found.\n");
                        delete_flag = 1;
                    }
                    else
                        printf("Number %d is deleted.\n", num);
                }
                else if(strcmp(token, "S") == 0){
                    printf("Enter the element to search : ");
                    fgets(option, 10, stdin);       //
                    token = strtok(option, "\r\n"); //
                    num = atoi(token);              //
                    bst_search(tree, num);
                    if(search_flag == 0)
                        printf("SORRY. Number not founded.\n");
                    else if(search_flag == 1)
                        printf("Bingo! Number is founded.\n");
                }
                else if(strcmp(token, "P") == 0){
                    printf("The tree in infix order : ");
                    inorder(tree);
                    printf("\n");

                    printf("The tree in level order : ");
                    level_order(tree);
                    printf("\n");
                }
                else
                    break;
            }
        }
        else if(strcmp(token, "2") == 0){   //Section2 Hunter Game

            printf("Please input the map file: ");
            fgets(line, 1024, stdin);
            token = strtok(line, "\r\n");   //file name
            if((fp = fopen(token, "r")))
                printf("Load file success.\n\n");
            else
                printf("No such file. Input again bitch!\n");

            while(fgets(line, 1024, fp)){
                token = strtok(line, "\r\n"); //
                num = atoi(token);              //
                tree = insert(tree, num);
            }
            fclose(fp);

            printf("Please input the key location: ");
            fgets(option, 10, stdin);       //
            token = strtok(option, "\r\n"); //
            key = atoi(token);     //
            printf("Please input the treasure location: ");
            fgets(option, 10, stdin);       //
            token = strtok(option, "\r\n"); //
            trea_location = atoi(token);    //
            printf("Please input the bomb number (0~9): ");
            fgets(option, 10, stdin);       //
            token = strtok(option, "\r\n"); //
            bomb = atoi(token);             //
            printf("\n");

            tree = hunter_delete_bomb(tree, bomb);

            bst_search(tree, key);
            if(search_flag == 1){
                bst_search(tree, trea_location);
                if(search_flag == 1){
                    printf("\nAdventurer successfully found the treasure.\n");
                    printf("Shortest path to find the treasure:\n");
                    print_hunter_least_path(tree, key, trea_location);
                    printf("\n");
                }
            }
        }
        else
            break;
        modeUsage();
    }
    return 0;
}
