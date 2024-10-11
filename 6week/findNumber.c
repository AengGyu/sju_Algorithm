#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int A, B, n;
    char *str;

    scanf("%d %d %d", &A, &B, &n);

    str = (char *)malloc(sizeof(char) * n);

    scanf("%s", str);

    int M;

    while (A != B) {
        M = (A + B) / 2;

        if (*str == 'Y') {  // Y면 K > M, M+1 <= K <= B
            // printf("M = %d, A = %d, B = %d, %d <= K <= %d\n", M, A, B, M+1, B);
            A = M + 1;
        } else {  // N면 K <= M, A <= K <= M
            // printf("M = %d, A = %d, B = %d, %d <= K <= %d\n", M, A, B, A, M);
            B = M;
        }

        str++;
    }
    printf("%d\n", A);
    return 0;
}