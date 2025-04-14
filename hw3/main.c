#include <stdio.h>
#include <string.h>

// �w�q�X�k�����������줸��m
#define VALID_RANGE 63
char elements[] = "abcdef";

// ���o�����������줸��
int get_bit_value(char e) {
    char *pos = strchr(elements, e);
    return (pos) ? (1 << (pos - elements)) : -1;
}

int main() {
    int S0, S1, S2;
    char e1, e2;
    int error = 0;

    // Ū����J���ˬd���~
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

    // �p��S2 = S1 �[�J e1
    S2 = S1 | get_bit_value(e1);

    // (1) �P�_ e2 �O�_�� S2 ������
    printf("%c\n", (S2 & get_bit_value(e2)) ? 'Y' : 'N');

    // (2) �P�_ S2 �O�_�� S0 ���l���X
    printf("%c\n", ((S0 & S2) == S2) ? 'Y' : 'N');

    // (3) �p�� S0 �M S2 ���涰
    printf("%d\n", S0 & S2);

    // (4) �p�� S0 �M S2 ���p��
    printf("%d\n", S0 | S2);

    // (5) �p�� S0 �M S2 ���t�� (S0 - S2)
    printf("%d\n", S0 & ~S2);

    return 0;
}
