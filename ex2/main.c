#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

void f31(int **pp, int **qq, int a[], int *p) {
int **rr = qq;
a[1] = (**rr) + (*(a+2));
printf("%d\n", a[1]); // (1)
*pp = p + 1;
*rr = *pp + 1;
printf("%d\n", *(*rr+3)); // (2)
printf("%d %d %d %d\n", (**pp), *(*pp-5), (p+1), (*pp-5) + *(p+1));
*(a+1) += (**pp) + *((*pp-5) + *(p+1));
printf("%d\n", a[1]); // (3)
*qq = p+1;
*((*qq)+1) = (**rr) + (**pp);
printf("%d\n", **qq); // (4)
}
void main() {
int a[] = {3, 4, 5, 6, 7, 8, 9};
int *p = a, *q = a+2;
int **pp = &p;
f31(pp, &q, a+2, p);
}
