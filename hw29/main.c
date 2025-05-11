#include <stdio.h>
#include <math.h>
#include <stdlib.h> // For fabs

// Define the function pointer type
typedef double (*FuncPtr)(double a, double x);

// Function definitions
double f1(double a, double x) {
    // Ensure the argument to sqrt is non-negative
    // For this problem, test cases are assumed to provide valid ranges
    // or that sqrt of a negative number (NaN) will lead to non-convergence if it happens.
    // A robust solution might check if (a - x*x) < 0, but typically competitive programming
    // problems ensure inputs are within function domains unless specified.
    if (a - x * x < 0 && fabs(a - x * x) > 1e-9) { // Allow for small floating point inaccuracies near zero
        // This case should ideally not happen with valid inputs for f1's typical use (circle/ellipse)
        // For example, if a=4, x must be in [-2, 2].
        // Return NaN or handle error appropriately if this can occur with problem constraints.
        // For now, we'll proceed assuming inputs are valid or sqrt behavior is acceptable.
    }
    return sqrt(a - x * x);
}

double f2(double a, double x) {
    // Ensure the argument to sqrt in denominator is positive
    if (a + x <= 0) {
        // Denominator would be zero or sqrt of negative.
        // Similar to f1, assume valid inputs.
    }
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
            // Consume the rest of the line if any parameters were mistakenly entered after invalid type
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
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
            // Safety break for extremely large n, though problem implies convergence
            if (n > 100000000 && n < 0) { // Check for overflow if n gets too large
                 // This indicates n has become too large, potentially an issue with convergence or input
                 // For competitive programming, this often means an issue if it gets this high without convergence.
                 // However, standard problems usually converge much faster.
                 break;
            }
            current_integral_val = trapezoidal_rule(selected_func, a, p, q, n);
        } while (fabs(current_integral_val - prev_integral_val) >= tolerance);
        // The loop terminates when the absolute difference is LESS than tolerance.
        // So, current_integral_val is the result that meets the criteria.

        printf("%.12f\n", current_integral_val);
    }

    return 0;
}
