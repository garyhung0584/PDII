#include <stdio.h>
#include <stdlib.h>

void classify_triangle(int a, int b, int c, char *result) {
    int temp;
    // 排序 a, b, c，使得 c 為最大邊
    if (a > b) { temp = a; a = b; b = temp; }
    if (b > c) { temp = b; b = c; c = temp; }
    if (a > b) { temp = a; a = b; b = temp; }

    // 不能成為三角形
    if (a + b <= c) {
        sprintf(result, "Not Triangle\n");
        return;
    }

    // 正三角形
    if (a == b && b == c) {
        sprintf(result + strlen(result), "Equilateral Triangle\n");
    }

    // 等腰三角形
    if (a == b || b == c) {
        sprintf(result + strlen(result), "Isosceles Triangle\n");
    }

    // 直角三角形
    if (a * a + b * b == c * c) {
        sprintf(result + strlen(result), "Right Triangle\n");
    }
    // 鈍角三角形
    else if (a * a + b * b < c * c) {
        sprintf(result + strlen(result), "Obtuse Triangle\n");
    }
    // 銳角三角形
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

        // 若非最後一組輸入，則添加 ** 分隔線
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
