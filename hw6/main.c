#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    float x = 0, y = 0;
    float score;
    char card[10];

    for (int i = 0; i < 2; i++) {
        score = 0;  // 每回合重新計算分數
        for (int j = 0; j < 3; j++) {
            scanf("%s", card);
            if (strcmp(card, "A") == 0) {
                score += 1;
            } else if (strcmp(card, "J") == 0 || strcmp(card, "Q") == 0 || strcmp(card, "K") == 0) {
                score += 0.5;
            } else {
                score += atof(card);
            }
        }
        if (score > 10.5) score = 0;

        if (i == 0) {
            x = score;
        } else {
            y = score;
        }
    }

    if (x - (int)x == 0){
        printf("%d\n",(int)x);
    } else {
        printf("%.1f\n", x);
    }
    if (y - (int)y == 0){
        printf("%d\n",(int)y);
    } else {
        printf("%.1f\n", y);
    }

    if (x > y) {
        printf("X Win\n");
    } else if (x < y) {
        printf("Y Win\n");
    } else {
        printf("Tie\n");
    }

    return 0;
}
