#include <stdio.h>

int round_bmi(double bmi) {
    int integer_part = (int)bmi;
    int first_decimal = (int)(bmi * 10) % 10;

    if (first_decimal < 5) {
        if (first_decimal == 4) {
            return integer_part;
        }
    } else if (first_decimal > 5) {
        return integer_part + 1;
    } else {
        if (integer_part % 2 == 0) {
            return integer_part + 1;
        }
    }
    return integer_part;
}

int main() {
    int w, h;
    scanf("%d", &w);
    scanf("%d", &h);

    if (w < 20 || w > 100 || h < 100 || h > 200) {
        printf("ERROR\n");
        return 0;
    }

    double height_m = h / 100.0;
    double bmi = w / (height_m * height_m);
    int rounded_bmi = round_bmi(bmi);

    printf("%d\n", rounded_bmi);

    if (rounded_bmi < 18) {
        printf("too low\n");
    } else if (rounded_bmi > 24) {
        printf("too high\n");
    }

    return 0;
}
