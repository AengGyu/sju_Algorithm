#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* arr, int start, int end, int key, int* max_idx) {
    if (start > end) return -1;

    int mid = (start + end) / 2;
    if (key == arr[mid]) {
        return mid;
    } else if (key < arr[mid]) { // 키보다 큰 경우
        return binarySearch(arr, start, mid - 1, key, max_idx);
    } else { // 사전의 키 값들(x) 중 찾고자 하는 키(key) 값보다 작거나 같은 경우 (x<k) max_idx 를 갱신
        *max_idx = mid; // 
        return binarySearch(arr, mid + 1, end, key, max_idx);
    }
}

int main() {
    int n, key, max_idx;
    int* arr;

    scanf("%d%d", &n, &key);

    arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int result = binarySearch(arr, 0, n - 1, key, &max_idx);

    if (result == -1) {
        if (arr[0] > key) {
            printf("-1");
        } else {
            printf("%d",max_idx);
        }
    }
    else
        printf("%d",result);
}