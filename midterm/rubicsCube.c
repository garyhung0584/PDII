#include <stdio.h>

int cube[6][3][3];

void initCube()
{
    int colors[6] = {1, 2, 3, 4, 5, 6};
    for (int f = 0; f < 6; f++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cube[f][i][j] = colors[f];
}

void rotateFaceClockwise(int face[3][3])
{
    int tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tmp[i][j] = face[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            face[j][2 - i] = tmp[i][j];
}

void rotateFaceCounterClockwise(int face[3][3])
{
    int tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tmp[i][j] = face[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            face[2 - j][i] = tmp[i][j];
}

void rotateColumnForward(int col)
{
    int temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[0][i][col];
    for (int i = 0; i < 3; i++) cube[0][i][col] = cube[3][i][col];
    for (int i = 0; i < 3; i++) cube[3][i][col] = cube[5][i][col];
    for (int i = 0; i < 3; i++) cube[5][i][col] = cube[2][2 - i][2 - col];
    for (int i = 0; i < 3; i++) cube[2][i][2 - col] = temp[2 - i];


    if (col == 0) rotateFaceCounterClockwise(cube[4]);
    else if (col == 2) rotateFaceClockwise(cube[1]);
}

void rotateRowLeft(int row)
{
    int temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[3][row][i];
    for (int i = 0; i < 3; i++) cube[3][row][i] = cube[1][row][i];
    for (int i = 0; i < 3; i++) cube[1][row][i] = cube[2][row][i];
    for (int i = 0; i < 3; i++) cube[2][row][i] = cube[4][row][i];
    for (int i = 0; i < 3; i++) cube[4][row][i] = temp[i];

    if (row == 0) rotateFaceClockwise(cube[0]);
    else if (row == 2) rotateFaceCounterClockwise(cube[5]);
}


int main()
{
    int M, op;
    scanf("%d", &M);
    initCube();

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &op);
        int d = op / 10;
        int pos = op % 10;
        if (d == 1) rotateColumnForward(pos);
        else if (d == 2) rotateRowLeft(pos);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("%d %d %d\n", cube[3][i][0], cube[3][i][1], cube[3][i][2]);
    }

    return 0;
}
