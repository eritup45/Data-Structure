#include <stdio.h>
int main()
{
    int arr[1000], i, j, n = 0, tmp;
    freopen("9input_1.txt", "r", stdin);
    while(scanf("%d", &arr[n]) != EOF)
        n++;
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - 1 - i; j++)
            if(arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        for(j = 0; j < n; j++)
            printf("%d ", arr[j]);
        printf("\n");
    }
    return 0;
}
