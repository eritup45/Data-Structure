#include<stdio.h>
#include<stdlib.h>



struct node{
	int data,data2;
	struct node* next;
};
typedef struct node stack_node;
stack_node* top1=NULL;
stack_node* top2=NULL;
int isempty1(){
	if(top1==NULL) return 1;
	else return 0;
}
void pop1(){
	stack_node* ptr1;
	ptr1=top1;
	top1=top1->next;
	free(ptr1);
}
void push1(int data,int data2){
	stack_node* new_node;
	new_node=(stack_node*)malloc(sizeof(stack_node));
	new_node->data=data;
	new_node->data2=data2;
	new_node->next=top1;
	top1=new_node;
}
int isempty2(){
	if(top1==NULL) return 1;
	else return 0;
}
void pop2(){
	stack_node* ptr2;
	ptr2=top2;
	top2=top2->next;
	free(ptr2);
}
void push2(int data,int data2){
	stack_node* new_node;
	new_node=(stack_node*)malloc(sizeof(stack_node));
	new_node->data=data;
	new_node->data2=data2;
	new_node->next=top2;
	top2=new_node;
}
int main(){
	char s[20][20];
	FILE *fp=fopen("maze.txt","r");
	int i=0;
	for(i=0;i<15;i++)  fscanf(fp,"%s",s[i]);
	fclose(fp);
	fp=fopen("result.txt","w");

	int x1=0,y1=0,x2=14,y2=14;
	int visit1[20][20]={{0}},visit2[20][20]={{0}};
	int stop1=0,stop2=0;
	while(1){
		int flag=0;
		visit1[x1][y1]=1;
		visit2[x2][y2]=1;
		if(stop1 && stop2) break;
		if(!stop1 && y1+1<15 && !visit1[x1][y1+1] && s[x1][y1+1]=='0'){
			//visit1[x1][y1+1]=1;
			push1(x1,y1);
			y1++;
		}
		else if(!stop1 && x1+1<15 && !visit1[x1+1][y1] && s[x1+1][y1]=='0'){
			//visit[x1+1][y1]=1;
			push1(x1,y1);
			x1++;
		}
		else if(!stop1 && y1-1>=0 && !visit1[x1][y1-1] && s[x1][y1-1]=='0'){
			//visit1[x1][y1-1]=1;
			push1(x1,y1);
			y1--;
		}
		else if(!stop1 && x1-1>=0 && !visit1[x1-1][y1] && s[x1-1][y1]=='0'){
			//visit1[x1-1][y1]=1;
			push1(x1,y1);
			x1--;
		}
		else{
			if(isempty1()) flag=1;
			else if(!stop1){
				//visit1[x1][y1]=0;
				x1=top1->data;
				y1=top1->data2;
				pop1();
			}
		}
		if(x1==14 && y1==14){
			stop1=1;
		}
		////
		if(!stop2 && y2-1>=0 && !visit2[x2][y2-1] && s[x2][y2-1]=='0'){
			push2(x2,y2);
			y2--;
		}
		else if(!stop2 && x2-1>=0 && !visit2[x2-1][y2] && s[x2-1][y2]=='0'){
			push2(x2,y2);
			x2--;
		}
		else if(!stop2 && y2+1<15 && !visit2[x2][y2+1] && s[x2][y2+1]=='0'){
			push2(x2,y2);
			y2++;
		}
		else if(!stop2 && x2+1<15 && !visit2[x2+1][y2] && s[x2+1][y2]=='0'){
			push2(x2,y2);
			x2++;
		}
		else{
			if(isempty2() && flag==1) break;
			else if(!stop2){
				//visit2[x2][y2]=0;
				x2=top2->data;
				y2=top2->data2;
				pop2();
			}
		}
		if(x2==0 && y2==0){
			stop2=1;
		}
		printf("ratA(%d,%d)\n",x1,y1);
		fprintf(fp,"ratA(%d,%d)\n",x1,y1);
		printf("ratB(%d,%d)\n",x2,y2);
		fprintf(fp,"ratB(%d,%d)\n",x2,y2);
	}
	fclose(fp);
}
