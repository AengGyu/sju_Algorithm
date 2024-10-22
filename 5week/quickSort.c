#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int middle(int* arr, int l, int r) {
    int idx1 = l + rand() % (r - l + 1);
    int idx2 = l + rand() % (r - l + 1);
    int idx3 = l + rand() % (r - l + 1);

    int n1 = arr[idx1], n2 = arr[idx2], n3 = arr[idx3];

    if ((n1 >= n2 && n1 <= n3) || (n1 >= n3 && n1 <= n2))
        return idx1;
    else if ((n2 >= n1 && n2 <= n3) || (n2 >= n3 && n2 <= n1))
        return idx2;
    else
        return idx3;
}
void partition(int* L, int left, int right, int p, int* a, int* b) {
    int i, j, k;
    k = L[p];                // k : 피벗의 원소
    swap(&L[right], &L[p]);  // 피벗을 가장 끝으로 옮겨 두기
    i = left;
    j = right - 1;
    while (i <= j) {
        while (i<= j && L[i] < k) {
            i++;
        }
        while (i<=j && L[j] > k) {
            j--;
        }
        if (i < j) {
            swap(&L[i], &L[j]);
        }
    }
    swap(&L[i], &L[right]);
    int l = i, r = i;
    while (l >= left && L[l] == k) {
        l--;
    }
    while (r <= right && L[r] == k) {
        r++;
    }
    *a = l + 1;  // 같은 값의 시작 위치
    *b = r - 1;  // 끝 위치
}
void quickSort(int* L, int left, int right) {
    if (left >= right) return;
    int a, b;
    int p = middle(L, left, right);
    partition(L, left, right, p, &a, &b);
    quickSort(L, left, a - 1);
    quickSort(L, b + 1, right);
}
int main() {
    int* arr;
    int n;
    srand(time(NULL));

    scanf("%d", &n);

    arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}