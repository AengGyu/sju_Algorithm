#include <stdio.h>
#include <stdlib.h>

void mergeTwoArr(int* arr, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int* sortedArr = (int*)malloc(sizeof(int) * (right + 1));
    int k = left;
    while (i <= left && j <= right) {
        if (arr[i] <= arr[j]) {
            sortedArr[k++] = arr[i++];
        } else {
            sortedArr[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        sortedArr[k++] = arr[i++];
    }
    while (j <= right) {
        sortedArr[k++] = arr[j++];
    }
    for (k = left; k <= right; k++) {
        arr[k] = sortedArr[k];
    }
    free(sortedArr);
}
void mergeSort(int* arr, int left, int right) {
    int mid = (left + right) / 2;

    if (left < right) {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        mergeTwoArr(arr, left, mid, right);
    }
}

int main() {
    int arr[7] = {3, 2, 4, 1, 7, 6, 5};

    mergeSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

    for (int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}