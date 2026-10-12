#include <stdio.h>

/* ------------------------------------------------------------------ */
int main(void)
{
    int a = 42;
    int b = 17;

    printf("Before swap: a = %d, b = %d\n", a, b);

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    printf("After swap:  a = %d, b = %d\n", a, b);

    return 0;
}
