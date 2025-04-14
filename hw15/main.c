#include <stdio.h>
#include <stdlib.h>

// �p��̤j���]�ơ]GCD�^
int gcd(int a, int b) {
    if (b == 0)
        return abs(a);
    return gcd(b, a % b);
}

// ²�Ƥ���
void simplify(int *num, int *den) {
    if (*den < 0) { // �T�O��������
        *num = -*num;
        *den = -*den;
    }
    int divisor = gcd(*num, *den);
    *num /= divisor;
    *den /= divisor;
}

// �p��î榡�ƪ��u��{��
void formatLineEquation(int x1, int y1, int x2, int y2, char *output) {
    if (x1 == x2) {
        sprintf(output, "Vertical line, undefined slope.\n");
        return;
    }

    int m_num = y2 - y1;
    int m_den = x2 - x1;
    simplify(&m_num, &m_den);

    int b_num = x2 * y1 - x1 * y2;
    int b_den = x2 - x1;
    simplify(&b_num, &b_den);

    char buffer[50];
    if (m_num == 0) {
        // �����u�A�ȿ�X y = b
        sprintf(output, "y = %d\n", b_num / b_den);
        return;
    }

    sprintf(output, "y = ");

    // ��X m
    if (m_num == 1 && m_den == 1) {
        sprintf(buffer, "x");
    } else if (m_num == -1 && m_den == 1) {
        sprintf(buffer, "-x");
    } else {
        sprintf(buffer, "%d", m_num);
        if (m_den != 1)
            sprintf(buffer + strlen(buffer), "/%d", m_den);
        sprintf(buffer + strlen(buffer), "x");
    }
    strcat(output, buffer);

    // ��X b
    if (b_num != 0) {
        strcat(output, " ");
        if (b_num > 0) strcat(output, "+ ");
        else strcat(output, "- ");
        sprintf(buffer, "%d", abs(b_num));
        if (b_den != 1)
            sprintf(buffer + strlen(buffer), "/%d", b_den);
        strcat(output, buffer);
    }

    strcat(output, "\n");
}

int main() {
    int N;
    scanf("%d", &N);

    char results[N][100];

    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        formatLineEquation(x1, y1, x2, y2, results[i]);
    }

    for (int i = 0; i < N; i++) {
        printf("%s", results[i]);
    }

    return 0;
}
