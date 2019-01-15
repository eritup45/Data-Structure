#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

void parse(char*, int*, int*);
int exist(int**, int, int);
int* insert(int*, int);

int main(){
	FILE* f = fopen("12input.txt", "r");

	int** relations = NULL;

	char line[1024];
	int a, b;
	int total = 0;
	int i, j, k;
	int max;

	while(fgets(line, 1024, f) != NULL){
		parse(line, &a, &b);

		if(!exist(relations, total, a) && !exist(relations, total, b)){
			relations = (int**)realloc(relations, sizeof(int*) * (++total));
			relations[total - 1] = NULL;
			relations[total - 1] = (int*)realloc(relations[total - 1], sizeof(int));
			relations[total - 1][0] = 0;
			relations[total - 1] = insert(relations[total - 1], a);
			relations[total - 1] = insert(relations[total - 1], b);
		}
		else if(exist(relations, total, a) && !exist(relations, total, b)){
			int temp;
			for(i = 0; i < total; i++){
				for(j = 1; j < relations[i][0] + 1; j++){
					if(relations[i][j] == a)
						temp = i;

				}
			}
			relations[temp] = insert(relations[temp], b);
		}
		else if(!exist(relations, total, a) && exist(relations, total, b)){
			int temp;
			for(i = 0; i < total; i++){
				for(j = 1; j < relations[i][0] + 1; j++){
					if(relations[i][j] == b)
						temp = i;
				}
			}
			relations[temp] = insert(relations[temp], a);
		}
		else{
			int tempA, tempB;
			for(i = 0; i < total; i++){
				for(j = 1; j < relations[i][0] + 1; j++){
					if(relations[i][j] == a)
						tempA = i;
					if(relations[i][j] == b)
						tempB = i;
				}
			}

			relations[tempA] = (int*)realloc(relations[tempA], sizeof(int) * (relations[tempA][0] + relations[tempB][0] + 1));
			i = relations[tempA][0] + 1;
			j = 1;
			relations[tempA][0] += relations[tempB][0];
			while(i < relations[tempA][0] + 1){
				relations[tempA][i] = relations[tempB][j];
				i++;
				j++;
			}
			free(relations[tempB]);
			i = tempB;
			while(i < total - 1){
				relations[i] = relations[i + 1];
				i++;
			}
			total--;
		}
	}
	/*sort*/
	for(i = 0; i < total; i++){
		for(j = 1; j < relations[i][0] + 1; j++){
			max = j;
			for(k = j; k < relations[i][0] + 1; k++){
				if(relations[i][k] < relations[i][max])
					max = k;
			}
			int temp = relations[i][max];
			relations[i][max] = relations[i][j];
			relations[i][j] = temp;
		}
	}
	int* temp = NULL;
	for(i = 0; i < total; i++){
		max = i;
		for(j = i; j < total; j++){
			if(relations[j][1] < relations[max][1])
				max = j;
		}
		temp = relations[max];
		relations[max] = relations[i];
		relations[i] = temp;
	}
	/*print*/
	for(i = 0; i < total; i++){
		for(j = 1; j < relations[i][0] + 1; j++)
			printf("%d ", relations[i][j]);
		printf("\n");
	}
	/*free*/
	for(i = 0; i < total; i++)
		free(relations[i]);
	free(relations);


	fclose(f);
	return 0;
}

void parse(char* str, int* a, int* b){
	*a = atoi(str);
	*b = atoi(strstr(str, " ") + 1);
}

int exist(int** r, int tot, int n){
	int i, j;
	for(i = 0; i < tot; i++){
		for(j = 1; j < r[i][0] + 1; j++){
			if(n == r[i][j])
				return 1;
		}
	}
	return 0;
}

int* insert(int* h, int a){
	int* n = (int*)realloc(h, sizeof(int) * (h[0] + 2));
	n[0] = h[0] + 1;
	n[n[0]] = a;

	return n;
}
