#include <stdio.h>

void drawPattern1(int M) {
    char letter = 'A';
    for (int i = 0; i < M; i++) {
        int hashCount = M - 1 - i;
        for (int j = 0; j < hashCount; j++) printf("#");
        for (int j = 0; j < i + 1; j++) {
            printf("*");
            if (j < i) printf("%c", letter);
        }
        for (int j = 0; j < hashCount; j++) printf("#");
        letter = 'A' + (i % 3);  // Fix letter cycling
        printf("\n");
    }
}

void drawPattern2(int M) {
    for (int i = 0; i < M; i++) {
        for (int j = i; j >= 0; j--) printf("%d", j + 1);
        for (int j = 0; j <= (M - 1 - i) * 2+1; j++) printf("*");
        for (int j = 1; j <= i + 1; j++) printf("%d", j);
        printf("\n");
    }
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N < 1 || N > 2 || M < 2 || M > 9) {
        printf("error\n");
        return 0;
    }

    if (N == 1) {
        drawPattern1(M);
    } else if (N == 2) {
        drawPattern2(M);
    }

    return 0;
}
