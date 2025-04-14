#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fill(int x, int y, int size, int matrix[8][8]) {
    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            matrix[i][j] = 1; // Fill the block with 1
        }
    }
}

void createBlock(int x, int y, int size, const char* exp, int* index, int matrix[8][8]) {
    if (*index >= strlen(exp)) return;

    char ch = exp[*index];
    (*index)++;  // Increment index after reading the character
    if (ch == '0') {
        // No filling for '0', do nothing
    } else if (ch == '1') {
        fill(x, y, size, matrix);  // Fill the current block with 1's
    } else if (ch == '2') {
        int half = size / 2;
        createBlock(x, y, half, exp, index, matrix);            // Top-left
        createBlock(x, y + half, half, exp, index, matrix);      // Top-right
        createBlock(x + half, y, half, exp, index, matrix);      // Bottom-left
        createBlock(x + half, y + half, half, exp, index, matrix); // Bottom-right
    }
}

int main() {
    char exp[110];
    int n;
    int index = 0;
    int matrix[8][8] = {0};  // Initialize matrix to 0

    // Read the input expression and the size of the matrix
    scanf("%s", exp);
    scanf("%d", &n);

    // Call the createBlock function to start filling the matrix
    createBlock(0, 0, n, exp, &index, matrix);

    // Check if there are any '1's in the matrix
    int has_black = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j]) {
                printf("%d,%d\n", i, j);
                has_black = 1;
            }
        }
    }

    if (!has_black) {
        printf("all white\n");
    }

    return 0;
}
