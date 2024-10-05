// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <Windows.h>

// void selectSort(int *arr, int size)
// {
//     int i, j;
//     int maxIdx;

//     for (i = size - 1; i > 0; i--)
//     {
//         maxIdx = i;
//         for (j = i - 1; j >= 0; j--)
//         {
//             if (arr[j] > arr[maxIdx])
//             {
//                 maxIdx = j;
//             }
//         }
//         int tmp = arr[maxIdx];
//         arr[maxIdx] = arr[i];
//         arr[i] = tmp;
//     }
// }

// void insertSort(int *arr, int size)
// {
//     int i, j;
//     int tmp;

//     for (i = 1; i < size; i++)
//     {
//         tmp = arr[i];

//         for (j = i - 1; j >= 0; j--)
//         {
//             if (arr[j] > tmp)
//             {
//                 arr[j + 1] = arr[j];
//             }
//             else
//             {
//                 break;
//             }
//         }
//         arr[j + 1] = tmp;
//     }
// }

// int main()
// {
//     int n;
//     int *arr1, *arr2;
//     LARGE_INTEGER ticksPerSec; 
//     LARGE_INTEGER start, end, diff;
    
//     srand(time(NULL));

//     scanf("%d", &n);

//     arr1 = (int *)malloc(sizeof(int) * n);
//     arr2 = (int *)malloc(sizeof(int) * n);

//     for (int i = 0; i < n; i++)
//     {
//         int tmp = rand() % 10000 + 1;
//         arr1[i] = tmp;
//         arr2[i] = tmp;
//     }
    
//     QueryPerformanceFrequency(&ticksPerSec); 
//     QueryPerformanceCounter(&start);
//     selectSort(arr1,n);
//     QueryPerformanceCounter(&end);
    
//     diff.QuadPart = end.QuadPart – start.QuadPart;
//     printf("time: %.12f sec\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
    
//     QueryPerformanceFrequency(&ticksPerSec); 
//     QueryPerformanceCounter(&start);
//     insertSort(arr2,n);
//     QueryPerformanceCounter(&end);
    
//     diff.QuadPart = end.QuadPart – start.QuadPart;
//     printf("time: %.12f ms\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart)*1000); 
    
//     return 0;
// }
