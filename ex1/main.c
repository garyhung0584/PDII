#include <stdio.h>
#include <stdarg.h>

int computeArea(int len, ...) {
    va_list args;
    va_start(args, len);

    int area;
    if (len <= 0) {
        area = 0;
    } else {
        int width = va_arg(args, int);
        if (width == 0) {
            area = len * len;
        } else {
            area = len * width;
        }
    }

    va_end(args);
    return area;
}

int main() {
    printf("%d\n", computeArea(5, 0));
    printf("%d\n", computeArea(5, 10, 15));
   return 0;
}
