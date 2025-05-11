#include <stdio.h>
void print(int a[], int n) {
    int i=0;
    for (i=0; i<n; i++) {
        printf("(%x - %d)", &a[i], a[i]);
    if (i%3==2) printf("\n");
    }
}
void f1() {
    int i=0, a[]={6,5,4,3,2,1};
    int *p = a;
    *(p++) = 0;
    print(a, 6);
    printf("%x, %d\n", p, *p);
    *(++p)= -1;
    print(a, 6);
    printf("%x, %d\n", p, *p);
    a[0]=(*(p++));print(a, 6);
    printf("%x, %d\n", p, *p);
}
int main() {
    f1();
    return 0;
}
