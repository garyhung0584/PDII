#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// �N M �i���ഫ�� 10 �i��
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

// �N 10 �i���ഫ�� N �i��
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
    // ����r��
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
        result[i] = buffer[len - 1 - i];
    }
    result[len] = '\0';
}

int main() {
    int M, N;
    char inputNum[11], outputNum[50];

    // Ū����J
    scanf("%d", &M);
    scanf("%s", inputNum);
    scanf("%d", &N);

    // M �i���� 10 �i��
    long long decimalValue = baseToDecimal(inputNum, M);

    // 10 �i���� N �i��
    decimalToBase(decimalValue, N, outputNum);

    // ��X���G
    printf("%s\n", outputNum);

    return 0;
}
