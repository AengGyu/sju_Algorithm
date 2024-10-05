#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int *arr;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = n - 1; i > 0; i--)
    {
        int maxIdx = i;

        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[maxIdx])
                maxIdx = j;
        }

        int tmp = arr[maxIdx];
        arr[maxIdx] = arr[i];
        arr[i] = tmp;

    }
    for (int j = 0; j < n; j++)
    {
        printf(" %d", arr[j]);
    }

    free(arr);
    
    return 0;
}
