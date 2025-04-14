#include <stdio.h>

void roll_dice(int *f1, int *f2, int *f3, int *f4, int *f5, int *f6, int move) {
    int tmp;
    switch (move) {
        case 1: // Roll forward
            tmp = *f1;
            *f1 = *f3;
            *f3 = *f6;
            *f6 = *f4;
            *f4 = tmp;
            break;
        case 2: // Roll backward
            tmp = *f1;
            *f1 = *f4;
            *f4 = *f6;
            *f6 = *f3;
            *f3 = tmp;
            break;
        case 3: // Roll right
            tmp = *f1;
            *f1 = *f5;
            *f5 = *f6;
            *f6 = *f2;
            *f2 = tmp;
            break;
        case 4: // Roll left
            tmp = *f1;
            *f1 = *f2;
            *f2 = *f6;
            *f6 = *f5;
            *f5 = tmp;
            break;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    int operations[4][N];  // To store the operation instructions for the dice

    // Storing the operations for each die
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &operations[j][i]);
        }
    }

    // Simulating the dice with their initial top, front, right, bottom, back, and left faces
    int dice[4][6] = {
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6}
    };

    // Simulating the dice roll operations for each die
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            roll_dice(&dice[j][0], &dice[j][1], &dice[j][2], &dice[j][3], &dice[j][4], &dice[j][5], operations[j][i]);
        }
    }
    int score = 0;
    int counts[7] = {0};

    for (int i = 0; i < 4; i++) {
        counts[dice[i][0]]++;
    }

    for (int i = 1; i <= 6; i++) {
        if (counts[i] == 4) {
            score = 18;
            break;
        }
    }

    if (score == 0) {
        int pairs = 0;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] == 2) pairs++;
        }
        if (pairs == 2) {
            for (int i = 6; i > 0; i--) {
                if(counts[i] == 2){
                    score = i*2;
                    break;
                }
            }
        }
    }

    if (score == 0) {
        int pair_value = -1;
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] == 2) {
                pair_value = i;
            }
            if (counts[i] == 1) {
                sum += i;
            }
        }
        if (pair_value != -1 && sum > 0) {
            score = sum;
        }
    }
    printf("%d\n", score);

    return 0;
}

