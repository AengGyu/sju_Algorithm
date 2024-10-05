#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int i, j;
    int *arr;

    scanf("%d", &n);

    arr = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (i = 1; i < n; i++)
    {
        int tmp = arr[i];

        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] > tmp)
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = tmp;
    }

    for (i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }

    free(arr);

    return 0;
}