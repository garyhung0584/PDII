#include <stdio.h>
#include <math.h>

void solve_quadratic(int a, int b, int c) {
    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2 * a);
        double x2 = (-b - sqrt(delta)) / (2 * a);
        if (x1 == x2) {
            printf("%.1f\n", x1);
        } else {
            printf("%.1f\n", x1);
            printf("%.1f\n", x2);
        }
    } else if (delta == 0) {
        double x = -b / (2.0 * a);
        printf("%.1f\n", x);
    } else {
        double real_part = -b / (2.0 * a);
        if (a < 0){
            a = a*-1;
        }
        double imag_part = sqrt(-delta) / (2.0 * a);
        printf("%.1f+%.1fi\n", real_part, imag_part);
        printf("%.1f-%.1fi\n", real_part, imag_part);
    }
}

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    solve_quadratic(a, b, c);
    return 0;
}
