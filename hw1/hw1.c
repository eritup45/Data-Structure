#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct data
{
    char name[100],output[1024];
    int index;
} Data;

void usage(void);
void makeOutput(Data data[],int total); //store the strange string in data[any].output
void getFailure(char *pat,int *lps);    //get lps (failure[])
int kmpmatch(char *string,char *pat);   //if matched, return the start position of the matched pattern. Else return -1.
void pop(char *string,char *pat,int pstart);    //remove pat out of the string, and print the string

int main()
{
    int i=0,j=0,k=0,option,total=0;
    char line[100],*token;
    Data data[1000];
    FILE *fp;
    while(1)
    {
        usage();
        scanf("%d",&option);
        if(option == 1)
        {
            //store data in struct data
            if((fp=fopen("data.csv","r")) == NULL)
            {
                printf("Can't read the file!\n");
            }
            printf("===============================\n");
            while(fgets(line, 300, fp))
            {
                token=strtok(line, ",\r\n");  //cut when meeting , and \n
                strcpy(data[i].name,token);
                token=strtok(NULL,",\r\n");
                data[i].index=atoi(token);
                printf("===the name: %s\n",data[i].name);
                printf("===the index: %d\n",data[i].index);
                if(strlen(data[i].name) < data[i].index){   //index should not exceed the lenth of name
                    printf("index exceed the name! pleae input again.\n");
                    i--;
                }
                i++;
            }
            total=i;

            fclose(fp);
            printf("===============================\n");
            makeOutput(data, total);

            for(i=1; i<total; i++)
            {
                printf("final string is : %s\n",data[i].output);
            }
        }
        else if(option == 2)
        {
            //windows' shit : '\r'
            char redundantshit[100];
            fgets(redundantshit, 100, stdin);

            printf("Please input the data ,if end ,press enter.\n");
            printf("===============================\n");
            total=total;
            while(1)
            {
                printf("===the name : ");
                fgets(line,100,stdin);
                if(line[0] == '\n') //if user input '\n', then break.
                    break;
                else
                {
                    line[strlen(line)-1]='\0';
                    strcpy(data[total].name,line);
                }
                printf("===the index :\t");
                fgets(line,100,stdin);
                if(line[0]=='\0')   //if user input '\n', then break.
                    break;
                else
                    data[total].index=atoi(line);
                if(strlen(data[total].name) < data[total].index){   //index should not exceed the lenth of name
                    printf("index exceed the name! pleae input again.\n");
                    total--;
                }
                total++;
            }
            makeOutput(data,total);
            /*for(i=1; i<total; i++)
                printf("final string is : %s\n",data[i].output);*/
        }
        else if(option == 3)
        {
            char pat[100];
            int lps[100];
            printf("input pop name\n");
            scanf("%s",pat);
            printf("input pop name is : %s\n",pat);

            getFailure(pat,lps);
            printf("lps = {%d",lps[0]+1); //print the lps. "+1" is to meet the request.
            for(i=1; i<strlen(pat); i++)
                printf(",%d",lps[i]+1);
            printf("}\n");

            int pstart=kmpmatch(data[total-1].output, pat); //get the start of the matched pattern
            //printf("pstart=%d\n",pstart);
            pop(data[total-1].output,pat,pstart);
        }
        else if(option == 0)
            break;
    }
    return 0;
}

//remove pat out of the string, and print the string
void pop(char *string, char *pat, int pstart)
{
    int i=0,j=0;
    int lens=strlen(string);
    int lenp=strlen(pat);
    if(pstart == -1)
    {
        printf("Error! Cannot find the string.\n");
        return;
    }
    for(i=pstart+lenp; i<lens; i++)
    {
        string[i-lenp]=string[i];
    }
    string[i-lenp]='\0';
    printf("the output is :%s\n",string);
}
//if matched, return the start position of the matched pattern. Else return -1.
int kmpmatch(char *string,char *pat)
{
    int i=0,j=0;
    int lens=strlen(string);
    int lenp=strlen(pat);
    int failure[100];
    getFailure(pat, failure);
    while(i < lens && j < lenp)
    {
        if(string[i] == pat[j])
        {
            i++; j++;
        }
        else if(j == 0)
            i++;
        else
            j = failure[j-1]+1;
    }
    return( (j == lenp) ? (i-lenp) : -1);   //if j==lenp, then return i-lens. Else return -1.
}

//get lps (failure[])
void getFailure(char *pat,int *lps)
{
    int n = strlen(pat);
    int failure[100],i=0,j=0;
    failure[0]=-1;
    for(j=1; j<n; j++)
    {
        i=failure[j-1];
        while((pat[j] != pat[i+1]) && (i>=0))
            i=failure[i];
        if(pat[j] == pat[i+1])
            failure[j]=i+1;
        else
            failure[j]=-1;
    }
    for(i=0; i<n; i++)
    {
        lps[i]=failure[i];//+1;    // "+1" to meet the condition
    }
}

//store the strange string in data[any].output
void makeOutput(Data data[], int total)
{
    int i=0,j=0,k=0,l=0,len=0;
    //make the target string
    for(l=0; l<=total; l++)
    {
        for(i=0,len=0; i<l; i++) //head
        {
            for(j=0; j<data[i].index; j++,len++)    //insert until [index]
            {
                data[l-1].output[len]=data[i].name[j];
            }
        }
        for(i=l-1,len=len; i>=0; i--)   //tail
        {
            for(k=data[i].index; k<strlen(data[i].name); k++,len++) //insert from index to the last word
            {
                data[l-1].output[len]=data[i].name[k];
            }
            data[l-1].output[len]='\0';//end of string
        }
    }
}

void usage(void)
{
    printf("What do you want to do?\n\n");
    printf("\t(1)Read data from a file\n");
    printf("\t(2)Write new data\n");
    printf("\t(3)Pop data\n");
    printf("\t(0)Exit\n");
}
