#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int up;
    int down;
} Num;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

void simplify(Num *num){
    if (num->down == 0) return;
    if (num->up == 0){
        num->down = 1;
        return;
    }
}

Num parseFraction(char *input)
{
    Num frac = {0, 1};
    int whole = 0, up = 0, down = 1;
    if (strchr(input, '('))
    {
        sscanf(input, "%d(%d/%d)", &whole, &up, &down);
        frac.up = whole * down;
        if (whole < 0)
        {
            frac.up -= up;
        }
        else
        {
            frac.pu == up;
        }
        frac.down = down;
    }
    else
    {
        sscanf(input, "%d/%d", &up, &down);
        frac.up = up;
        frac.down = down;
    }
    return frac;
}

Num operate(Num a, Num b, char op){
    Num result = {0, 1};
    if (a.down == 0 || b.down == 0) {
        result.down = 0;
        return result;
    }

    switch (op){
        case '+':
            result.up = a.up * b.down + b.up * a.down;
            result.down = a.down * b.down;
            break;
        case '-':
            result.up = a.up * b.down - b.up * a.down;
            result.down = a.down * b.down;
            break;
        case '*':
            result.up = a.up * b.up;
            result.down = a.down * b.down;
            break;
        case '/':
            if (b.up == 0) {
                result.down = 0;
                return result;
            }
            result.up = a.up * b.down;
            result.down = a.down * b.up;
            break;
    }
    simplify(&result);
    return result;
}


int main()
{
    char input1[20], input2[20], op, cont;
    Num results[100];
    int count = 0;

    do
    {
        scanf("%s", input1);
        scanf(" %c", &op);
        scanf("%s", input2);

        Num frac1 = parseFraction(input1);
        Num frac2 = parseFraction(input2);
        results[count++] = operate(frac1, frac2, op);

        scanf(" %c", &cont);
    }
    while (cont == 'y');



    return 0;
}
