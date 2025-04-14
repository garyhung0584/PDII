#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct {
    int a;
    int b;
} Pair;

int compare(const void* x, const void* y) {
    Pair *p1 = (Pair*)x;
    Pair *p2 = (Pair*)y;
    if (p1->a != p2->a)
        return p1->a - p2->a;
    return p1->b - p2->b;
}

int is_duplicate(Pair* pairs, int count, Pair current) {
    for (int i = 0; i < count; i++) {
        if (pairs[i].a == current.a && pairs[i].b == current.b)
            return 1;
    }
    return 0;
}

int main() {
    int n;
    int arr[MAX_N];
    Pair inversions[MAX_N * MAX_N]; // 最多 n*(n-1)/2 個反序
    int inv_count = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                Pair new_pair = {arr[i], arr[j]};
                if (!is_duplicate(inversions, inv_count, new_pair)) {
                    inversions[inv_count++] = new_pair;
                }
            }
        }
    }

    if (inv_count == 0) {
        printf("0\n");
    } else {
        qsort(inversions, inv_count, sizeof(Pair), compare);
        for (int i = 0; i < inv_count; i++) {
            printf("(%d,%d)\n", inversions[i].a, inversions[i].b);
        }
    }

    return 0;
}
