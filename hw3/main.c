#include <stdio.h>
#include <string.h>

// 定義合法元素對應的位元位置
#define VALID_RANGE 63
char elements[] = "abcdef";

// 取得元素對應的位元值
int get_bit_value(char e) {
    char *pos = strchr(elements, e);
    return (pos) ? (1 << (pos - elements)) : -1;
}

int main() {
    int S0, S1, S2;
    char e1, e2;
    int error = 0;

    // 讀取輸入並檢查錯誤
    if (scanf("%d", &S0) != 1 || S0 < 0 || S0 > VALID_RANGE) {
        printf("S0 ERROR\n");
        error = 1;
    }
    if (scanf("%d", &S1) != 1 || S1 < 0 || S1 > VALID_RANGE) {
        printf("S1 ERROR\n");
        error = 1;
    }
    if (scanf(" %c", &e1) != 1 || get_bit_value(e1) == -1) {
        printf("e1 ERROR\n");
        error = 1;
    }
    if (scanf(" %c", &e2) != 1 || get_bit_value(e2) == -1) {
        printf("e2 ERROR\n");
        error = 1;
    }

    if (error) {
        return 0;
    }

    // 計算S2 = S1 加入 e1
    S2 = S1 | get_bit_value(e1);

    // (1) 判斷 e2 是否為 S2 的元素
    printf("%c\n", (S2 & get_bit_value(e2)) ? 'Y' : 'N');

    // (2) 判斷 S2 是否為 S0 的子集合
    printf("%c\n", ((S0 & S2) == S2) ? 'Y' : 'N');

    // (3) 計算 S0 和 S2 的交集
    printf("%d\n", S0 & S2);

    // (4) 計算 S0 和 S2 的聯集
    printf("%d\n", S0 | S2);

    // (5) 計算 S0 和 S2 的差集 (S0 - S2)
    printf("%d\n", S0 & ~S2);

    return 0;
}
