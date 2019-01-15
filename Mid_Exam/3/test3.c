#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

typedef struct _node{
	int value;
	struct _node* next;
}node;

void readNums(node**, char*, int*);
int* readPartitions(char*, int*);
void insert(node**, int);
void reverse(node*, int);

int main(int argc, char* argv[]){
	char line[1024];
	FILE* f = fopen("3input.txt.old", "r");
	node* list = NULL;
	int size, psize, bsize;
	int* partitions = NULL;
	int i, j;

	fgets(line, 1024, f);
	readNums(&list, line, &size);
	fgets(line, 1024, f);
	partitions = readPartitions(line, &psize);
	bsize = size / 3;

	for(i = 0; i < psize; i++){
		node* temp = list;
		node* pre = list;
		for(j = 0; j < (partitions[i] - 1) * bsize; j++)
			temp = temp->next;
		for(j = 0; j < (partitions[i] - 1) * bsize - 1; j++)
			pre = pre->next;

		reverse(temp, bsize);
	}

	node* cur = list;
	for(i = 0; i < size; i++){
		printf("%d ", cur->value);
		cur = cur->next;
	}


	fclose(f);
	return 0;
}

void readNums(node** h, char* str, int* s){
	char* temp = NULL;
	int count = 1;

	insert(h, atoi(str));

	temp = strstr(str, " ");
	while(temp != NULL){
		temp++;
		insert(h, atoi(temp));
		count++;
		temp = strstr(temp, " ");
	}
	*s = count;
}

void insert(node** h, int a){
	node* n = (node*)malloc(sizeof(node));
	n->value = a;
	n->next = NULL;

	if(*h == NULL){
		(*h) = n;
	}
	else{
		node* cur = *h;
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = n;
	}
}

int* readPartitions(char* str, int* s){
	int* res = (int*)malloc(sizeof(int));
	res[0] = atoi(str);
	int count = 1;

	char* temp = strstr(str, " ");
	while(temp != NULL){
		temp++;
		res = (int*)realloc(res, sizeof(int) * (++count));
		res[count - 1] = atoi(temp);
		temp = strstr(temp, " ");
	}

	*s = count;

	return res;
}

void reverse(node* n, int s){
	node* cur = n;
	int* buf = (int*)malloc(sizeof(int) * s);
	int i;

	for(i = 0; i < s; i++){
		buf[i] = cur->value;
		cur = cur->next;
	}

	cur = n;
	for(i = 0; i < s; i++){
		cur->value = buf[s - 1 - i];
		cur = cur->next;
	}

	free(buf);
}
