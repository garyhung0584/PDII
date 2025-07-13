#include <stdio.h>
#include <math.h>
#include <stdlib.h> // For fabs

// Define the function pointer type
typedef double (*FuncPtr)(double a, double x);

// Function definitions
double f1(double a, double x) {
    return sqrt(a - x * x);
}

double f2(double a, double x) {
    return (a * pow(x, 3) + 7 * x) / sqrt(a + x);
}

// Trapezoidal rule calculation
double trapezoidal_rule(FuncPtr func, double coeff_a, double p, double q, int n) {
    if (n == 0) return 0.0; // Should not happen with n starting at 1 and doubling
    if (fabs(p - q) < 1e-12) return 0.0; // Integral over zero width is zero

    double h = (q - p) / n;
    double sum = func(coeff_a, p) + func(coeff_a, q); // Endpoints

    for (int i = 1; i < n; i++) {
        double xi = p + i * h;
        sum += 2 * func(coeff_a, xi);
    }
    return (h / 2.0) * sum;
}

int main() {
    int func_type;
    FuncPtr selected_func = NULL;

    while (1) {
        scanf("%d", &func_type);

        if (func_type == 0) {
            break;
        } else if (func_type == 1) {
            selected_func = f1;
        } else if (func_type == 2) {
            selected_func = f2;
        } else {
            printf("Invalid\n");
            continue;
        }

        double a, p, q;
        int err;
        scanf("%lf %lf %lf %d", &a, &p, &q, &err);

        double tolerance = pow(10.0, -(double)err);

        int n = 1; // Initial number of segments
        double current_integral_val;
        double prev_integral_val;

        // First calculation
        current_integral_val = trapezoidal_rule(selected_func, a, p, q, n);

        // Iteratively increase n until desired precision is met
        do {
            prev_integral_val = current_integral_val;
            n *= 2;

            current_integral_val = trapezoidal_rule(selected_func, a, p, q, n);
        } while (fabs(current_integral_val - prev_integral_val) >= tolerance);

        printf("%.12f\n", current_integral_val);
    }

    return 0;
}

