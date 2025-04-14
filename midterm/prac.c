#include<stdio.h>
#include<stdlib.h>

void roll_dice(int* f1,int* f2,int* f3,int* f4,int* f5,int* f6, int operation)
{
    int tmp;
    switch (operation)
    {
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





int main()
{
    int N;
    int operations[4][N];
    scanf("%d", &N);
    for (int i = 0; i < N ; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &operations[j][i]);
        }
    }

    int dice[4][6] =
    {
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6}
    };

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            roll_dice(&dice[j][0],&dice[j][1],&dice[j][2],&dice[j][3],&dice[j][4],&dice[j][5], operations[j][i]);
        }
    }

    int count[6];
    int two = 0;
    int score = 0;

    for (int i = 0; i < 4; i++)
    {
        count[dice[i][0]]++;
    }

    for (int i = 0; i < 6; i++)
    {
        if (count[i] == 4)
        {
            score = 18;
            break;
        }
        if(count[i] == 2)
        {
            two++;
        }
    }

    if (two == 2)
    {
        for (int i = 6; i >= 0; i++)
        {
            if (count[i] >= 0)
            {
                score = count[i]*2;
                break;
            }
        }
    }
    if (two == 1){
        for (int i = 6; i >= 0; i++){
            if (count[i] == 1){
                score += count[i];
            }
        }
    }

    printf("%d", score);
    return 0;
}
