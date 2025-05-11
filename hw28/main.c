#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_block(const char *s, int len, int k) {
    int type_upper = isupper(s[0]);
    for (int i = 0; i < len; i += k) {
        if (i + k > len)
            return 0;

        for (int j = 0; j < k; ++j) {
            char c = s[i + j];
            if ((type_upper && !isupper(c)) || (!type_upper && !islower(c)))
                return 0;
        }

        type_upper = !type_upper;
    }
    return 1;
}

int find_max_k_alternating(const char *s, int k) {
    int n = strlen(s);
    int maxlen = 0;

    for (int i = 0; i < n; ++i) {
        for (int blocks = 2; i + blocks * k <= n; ++blocks) {
            int length = blocks * k;
            if (is_valid_block(s + i, length, k)) {
                if (length > maxlen)
                    maxlen = length;
            } else {
                break;
            }
        }
    }
    return maxlen;
}

int main() {
    int N;
    scanf("%d", &N);

    char s[1001];
    int k;
    for (int i = 0; i < N; ++i) {
        scanf("%s %d", s, &k);
        int result = find_max_k_alternating(s, k);
        printf("%d\n", result);
    }

    return 0;
}
