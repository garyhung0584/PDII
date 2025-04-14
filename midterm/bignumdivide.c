#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const char *a, const char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    if (len_a != len_b) return len_a > len_b ? 1 : -1;
    return strcmp(a, b);
}

void subtract(const char *a, const char *b, char *res) {
    int len_a = strlen(a), len_b = strlen(b);
    int i = len_a - 1, j = len_b - 1, k = 0, borrow = 0;
    char tmp[50] = {0};

    while (i >= 0 || j >= 0 || borrow) {
        int digit_a = (i >= 0) ? a[i--] - '0' : 0;
        int digit_b = (j >= 0) ? b[j--] - '0' : 0;
        int diff = digit_a - digit_b - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        tmp[k++] = diff + '0';
    }

    while (k > 1 && tmp[k - 1] == '0') k--;

    for (int m = 0; m < k; m++) res[m] = tmp[k - 1 - m];
    res[k] = '\0';
}
void multiply_digit(const char *num, int x, char *res) {
    int len = strlen(num), carry = 0, k = 0;
    char tmp[50] = {0};
    for (int i = len - 1; i >= 0; i--) {
        int prod = (num[i] - '0') * x + carry;
        tmp[k++] = (prod % 10) + '0';
        carry = prod / 10;
    }
    if (carry) tmp[k++] = carry + '0';

    for (int i = 0; i < k; i++) res[i] = tmp[k - 1 - i];
    res[k] = '\0';
}
void divide(const char *a, const char *b, char *quotient, char *remainder) {
    char curr[100] = {0}, tmp[100], mul[100];
    int len_a = strlen(a), q_pos = 0;
    curr[0] = '\0';

    for (int i = 0; i < len_a; i++) {
        int len = strlen(curr);
        curr[len] = a[i];
        curr[len + 1] = '\0';

        int p = 0;
        while (curr[p] == '0' && curr[p + 1]) p++;
        if (p) memmove(curr, curr + p, strlen(curr) - p + 1);

        int x = 0;
        for (x = 9; x >= 0; x--) {
            multiply_digit(b, x, mul);
            if (compare(curr, mul) >= 0) {
                subtract(curr, mul, tmp);
                strcpy(curr, tmp);
                break;
            }
        }
        quotient[q_pos++] = x + '0';
    }

    quotient[q_pos] = '\0';

    int start = 0;
    while (quotient[start] == '0' && quotient[start + 1]) start++;
    if (start) memmove(quotient, quotient + start, strlen(quotient) - start + 1);

    if (curr[0]) strcpy(remainder, curr);
    else strcpy(remainder, "0");
}
void removeSlashes(char *str) {
    int i = 0, j = 0;

    // Iterate through the string
    while (str[i]) {
        if (str[i] != '/') {
            str[j++] = str[i];  // Copy the character if it's not '/'
        }
        i++;
    }
    str[j] = '\0';  // Null terminate the string
}
int main() {
    char a[50], b[50];
    char quotient[60], remainder[60];

    scanf("%s", a);
    scanf("%s", b);

    divide(a, b, quotient, remainder);

    removeSlashes(quotient);

    printf("%d\n", atoi(quotient));
    printf("%s\n", remainder);

    return 0;
}
