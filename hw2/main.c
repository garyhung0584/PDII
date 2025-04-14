#include <stdio.h>

void updateBases(int *bases, int hit, int *score) {
    if (hit == 4) {
        *score += 1 + bases[0] + bases[1] + bases[2];
        bases[0] = bases[1] = bases[2] = 0;
    } else {
        for (int i = 2; i >= 0; i--) {
            if (bases[i]) {
                if (i + hit >= 3) {
                    (*score)++;
                } else {
                    bases[i + hit] = 1;
                }
                bases[i] = 0;
            }
        }
        if (hit < 4) {
            bases[hit - 1] = 1;
        }
    }
}

int main() {
    int bases[3] = {0}; // 依序代表一壘、二壘、三壘
    int score = 0, outs = 0, hit;

    for (int i = 0; i < 5; i++) {
        scanf("%d", &hit);
        if (hit == 0) {  // 出局
            outs++;
            if (outs == 3) {  // 三出局，壘包清空
                bases[0] = bases[1] = bases[2] = 0;
            }
        } else {
            updateBases(bases, hit, &score);
        }
    }

    printf("%d\n", score);
    printf("%d %d %d\n", bases[0], bases[1], bases[2]);

    return 0;
}
