#include <stdio.h>
#include <stdlib.h>

void classify_triangle(int a, int b, int c, char *result) {
    int temp;
    // �Ƨ� a, b, c�A�ϱo c ���̤j��
    if (a > b) { temp = a; a = b; b = temp; }
    if (b > c) { temp = b; b = c; c = temp; }
    if (a > b) { temp = a; a = b; b = temp; }

    // ���ন���T����
    if (a + b <= c) {
        sprintf(result, "Not Triangle\n");
        return;
    }

    // ���T����
    if (a == b && b == c) {
        sprintf(result + strlen(result), "Equilateral Triangle\n");
    }

    // ���y�T����
    if (a == b || b == c) {
        sprintf(result + strlen(result), "Isosceles Triangle\n");
    }

    // �����T����
    if (a * a + b * b == c * c) {
        sprintf(result + strlen(result), "Right Triangle\n");
    }
    // �w���T����
    else if (a * a + b * b < c * c) {
        sprintf(result + strlen(result), "Obtuse Triangle\n");
    }
    // �U���T����
    else {
        sprintf(result + strlen(result), "Acute Triangle\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char output[10000] = "";

    for (int i = 0; i < n; i++) {
        int a, b, c;
        char result[1000] = "";
        scanf("%d %d %d", &a, &b, &c);
        classify_triangle(a, b, c, result);
        strcat(output, result);

        // �Y�D�̫�@�տ�J�A�h�K�[ ** ���j�u
        if (i < n - 1) {
            for (int j = 0; j < n; j++){
                strcat(output, "*");
            }
            strcat(output, "\n");
        }
    }
    printf("%s", output);
    return 0;
}
