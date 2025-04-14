#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matrix[8][8]; // �䴩�̤j 8x8
int index_expr = 0;
char expr[110];

void fill_matrix(int x, int y, int size) {
    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            matrix[i][j] = 1;
        }
    }
}

void createBlock(int x, int y, int size) {
    if (index_expr >= strlen(expr)) return;

    char ch = expr[index_expr++];
    if (ch == '0') {
        // ���աA���ΰ���
    } else if (ch == '1') {
        // ����
        fill_matrix(x, y, size);
    } else if (ch == '2') {
        int half = size / 2;
        createBlock(x, y, half);                 // ���W
        createBlock(x, y + half, half);          // �k�W
        createBlock(x + half, y, half);          // ���U
        createBlock(x + half, y + half, half);   // �k�U
    }
}

int main() {
    int n;
    scanf("%s", expr);
    scanf("%d", &n);

    memset(matrix, 0, sizeof(matrix));
    index_expr = 0;

    createBlock(0, 0, n);

    int has_black = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j]) {
                printf("%d,%d\n", i, j);
                has_black = 1;
            }

    if (!has_black)
        printf("all white\n");

    return 0;
}
