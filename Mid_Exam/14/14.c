#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct link{
    float coef;
    int exponent;
    struct link *next;
}link;

void PrintPoly(link *list){
    link *traverse = list;
    while(traverse != NULL){
        if(traverse->exponent == 0){
            printf("%.1f\n",traverse->coef);
            return;
        }
        printf("%.1f",traverse->coef);
        printf("x^%d",traverse->exponent);
        printf("+");
        traverse = traverse->next;
    }
    //printf("---------");
    return;
}
link *Attach(link *list, float coef, int exponent){
    link *traverse = list;
    link *tmp = NULL;
    if(list == NULL){
        list = malloc(sizeof(link));
        list->coef = coef;
        list->exponent = exponent;
        list->next = NULL;
        return list;
    }
    else{
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        tmp = malloc(sizeof(link));
        tmp->coef = coef;
        tmp->exponent = exponent;
        tmp->next = NULL;
        traverse->next = tmp;
    }
    return list;
}
link *PolyAdd(link *a, link *b){
    link *result = NULL;
    float coef;
    int exponent;
    while(a != NULL){
        while(b != NULL){
            if(a->exponent == b->exponent){
                coef = a->coef + b->coef;
                exponent = a->exponent;
                result = Attach(result, coef, exponent);
                a = a->next;
                b = b->next;
                break;
            }
            else if(a->exponent > b->exponent){
                coef = a->coef;
                exponent = a->exponent;
                result = Attach(result, coef, exponent);
                a = a->next;
                break;
            }
            else if(a->exponent < b->exponent){
                coef = b->coef;
                exponent = b->exponent;
                result = Attach(result, coef, exponent);
                b = b->next;
                continue;
            }
        }
    }
    if(a == NULL && b != NULL){
        while(b != NULL){
            coef = b->coef;
            exponent = b->exponent;
            result = Attach(result, coef, exponent);
            b = b->next;
        }
    }
    else if(a != NULL && b==NULL){
        while(a != NULL){
            coef = a->coef;
            exponent = a->exponent;
            result = Attach(result, coef, exponent);
            a = a->next;
        }
    }
    return result;
}
link *PolyMul(link *a, link *b){
    link *result[100], *finalresult = NULL;
    link *traversea = a, *traverseb = b;
    int i=0,j=0,exponent;
    float coef;

    for(i=0; i<100;i++){
        result[i] = NULL;
    }
    i=0;
    while(traversea != NULL){
        while(traverseb != NULL){
            coef = traversea->coef * traverseb->coef;
            exponent = traversea->exponent + traverseb->exponent;
            result[i] = Attach(result[i], coef, exponent);
            traverseb = traverseb->next;
        }
        traverseb = b;
        traversea = traversea->next;
        i++;
    }

    finalresult = Attach(finalresult, 0, 0);
    for(j=0; j<i; j++){
        finalresult = PolyAdd(result[j],finalresult);
    }
    return finalresult;
}
int main(){
    link *a = NULL, *b = NULL, *list = a;
    link *c = NULL, *d = NULL, *e = NULL;
    char line[100],*token;
    int i=0,j=0,exponent;
    float coef;
    FILE *fp;
    fp = fopen("14input.txt","r");
    while(fgets(line,100,fp)){
        if(strcmp(line,":\n") == 0){
            a = list;
            list = b;
            continue;
        }
        token = strtok(line," \n");
        coef = atof(token);
        token = strtok(NULL," \n");
        exponent = atoi(token);
        list = Attach(list, coef, exponent);
    }
    b = list;
    c = PolyAdd(a, b);
    e = PolyMul(a, b);
    printf("A(x)=");
    PrintPoly(a);
    printf("B(x)=");
    PrintPoly(b);
    printf("C(x)=");
    PrintPoly(c);
    printf("E(x)=");
    PrintPoly(e);
}
