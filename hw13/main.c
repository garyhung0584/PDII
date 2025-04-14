#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 將 M 進制轉換為 10 進制
long long baseToDecimal(const char *num, int base) {
    long long result = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        char digit = num[i];
        int value;
        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        } else {
            value = digit - 'A' + 10;
        }
        result += value * pow(base, len - 1 - i);
    }
    return result;
}

// 將 10 進制轉換為 N 進制
void decimalToBase(long long decimal, int base, char *result) {
    if (decimal == 0) {
        strcpy(result, "0");
        return;
    }
    char buffer[50];
    int index = 0;
    while (decimal > 0) {
        int remainder = decimal % base;
        if (remainder < 10) {
            buffer[index++] = remainder + '0';
        } else {
            buffer[index++] = remainder - 10 + 'A';
        }
        decimal /= base;
    }
    buffer[index] = '\0';
    // 反轉字串
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
        result[i] = buffer[len - 1 - i];
    }
    result[len] = '\0';
}

int main() {
    int M, N;
    char inputNum[11], outputNum[50];

    // 讀取輸入
    scanf("%d", &M);
    scanf("%s", inputNum);
    scanf("%d", &N);

    // M 進制轉 10 進制
    long long decimalValue = baseToDecimal(inputNum, M);

    // 10 進制轉 N 進制
    decimalToBase(decimalValue, N, outputNum);

    // 輸出結果
    printf("%s\n", outputNum);

    return 0;
}
