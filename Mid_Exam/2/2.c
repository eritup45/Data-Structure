#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void get_lps(char *pat, int *lps){
    int i=0, j=0, len_pat = strlen(pat);
    lps[0] = -1;
    for(j=1; j<len_pat; j++){
        i = lps[j-1];
        while(pat[j] != pat[i+1] && i>=0)
            i = lps[i];
        if(pat[j] == pat[i+1])
            lps[j] = i + 1;
        else
            lps[j] = -1;
    }
    printf("F : %d", lps[0]); //print lps
    for (i = 1; i < len_pat; i++)
        printf(" %d", lps[i]);
    printf("\n");
}
int pop_pat(char *pat, char *string, int *lps){
    int i = 0, j = 0, len_s = strlen(string), len_pat = strlen(pat); //i for string, j for pat
    while (i < len_s && j < len_pat){
        if (string[i] == pat[j]){
            i++;
            j++;
        }
        else if(j == 0)
            i++;
        else
            j = lps[j - 1] + 1; //move back the pat
    }
    return j == len_pat ? i-len_pat : -1;
}

int main()
{
    char line[100010], string[100010], pat[100010];
    int i, j, match;
    freopen("2input.txt", "r", stdin);
    //freopen("2output1.txt", "w", stdout);

    //read data
    fgets(line, 100010, stdin);
    for(i = 0, j = 4; j < strlen(line) - 1 && line[j] != '\n' && line[j] != '\0'; i++, j += 2)
        string[i] = line[j];
    string[i] = '\0';
    fgets(line, 100010, stdin);
    for(i = 0, j = 4; j < strlen(line) && line[j] != '\n' && line[j] != '\0'; i++, j += 2)
        pat[i] = line[j];
    pat[i] = '\0';

    int lps[strlen(pat)];
    get_lps(pat, lps);
    match = pop_pat(pat, string, lps);
    if(match == -1)
        printf("Not found\n");
    else
        printf("Yes,%d,%d\n", match, match + strlen(pat) - 1);
    return 0;
}
