#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* arr, int start, int end, int key, int* max_idx) {
    int mid;
    while(start <= end){
        mid = (start+end)/2;
        if(key == arr[mid]){
            return mid;
        }
        else if(key < arr[mid]){
            *max_idx = mid; // 사전의 키 값들(x) 중에서 찾고자 하는 키(key)보다 작은 것들 중에서 제일 작은 값
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
    }
    return -1;
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
        if (arr[n-1] < key) {
            printf("%d", n);
        } else {
            printf("%d",max_idx);
        }
    }
    else
        printf("%d",result);
}