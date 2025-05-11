
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int numerator;
    int denominator;
} Fraction;

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

void simplify(Fraction *frac)
{
    if (frac->denominator == 0) return;
    if (frac->numerator == 0)
    {
        frac->denominator = 1;
        return;
    }
    int divisor = gcd(abs(frac->numerator), abs(frac->denominator));
    frac->numerator /= divisor;
    frac->denominator /= divisor;
    if (frac->denominator < 0)
    {
        frac->numerator = -frac->numerator;
        frac->denominator = -frac->denominator;
    }
}

Fraction parseFraction(char *input)
{
    Fraction frac = {0, 1};
    int whole = 0, numerator = 0, denominator = 1;

    if (strchr(input, '('))
    {
        sscanf(input, "%d(%d/%d)", &whole, &numerator, &denominator);
        frac.numerator = whole * denominator + (whole < 0 ? -numerator : numerator);
        frac.denominator = denominator;
    }
    else
    {
        sscanf(input, "%d/%d", &numerator, &denominator);
        frac.numerator = numerator;
        frac.denominator = denominator;
    }
    return frac;
}

Fraction operate(Fraction a, Fraction b, char op)
{
    Fraction result = {0, 1};
    if (a.denominator == 0 || b.denominator == 0)
    {
        result.denominator = 0;
        return result;
    }
    switch (op)
    {
    case '+':
        result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
        result.denominator = a.denominator * b.denominator;
        break;
    case '-':
        result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
        result.denominator = a.denominator * b.denominator;
        break;
    case '*':
        result.numerator = a.numerator * b.numerator;
        result.denominator = a.denominator * b.denominator;
        break;
    case '/':
        if (b.numerator == 0)
        {
            result.denominator = 0;
            return result;
        }
        result.numerator = a.numerator * b.denominator;
        result.denominator = a.denominator * b.numerator;
        break;
    }
    simplify(&result);
    return result;
}

void printFraction(Fraction frac)
{
    if (frac.denominator == 0)
    {
        printf("Error\n");
        return;
    }
    if (frac.numerator == 0)
    {
        printf("0\n");
        return;
    }
    if (abs(frac.numerator) >= frac.denominator)
    {
        int whole = frac.numerator / frac.denominator;
        int remainder = abs(frac.numerator) % frac.denominator;
        if (remainder == 0)
            printf("%d\n", whole);
        else
            printf("%d(%d/%d)\n", whole, remainder, frac.denominator);
    }
    else
    {
        printf("%d/%d\n", frac.numerator, frac.denominator);
    }
}

int main()
{
    char input1[20], input2[20], op, cont;
    Fraction results[100];
    int count = 0;

    do
    {
        scanf("%s", input1);
        scanf(" %c", &op);
        scanf("%s", input2);

        Fraction frac1 = parseFraction(input1);
        Fraction frac2 = parseFraction(input2);
        results[count++] = operate(frac1, frac2, op);

        scanf(" %c", &cont);
    }
    while (cont == 'y');

    for (int i = 0; i < count; i++)
    {
        printFraction(results[i]);
    }

    return 0;
}
