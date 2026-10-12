#include <stdio.h>

#define LIMIT 50

/* ------------------------------------------------------------------ */
int main(void)
{
    int is_prime[LIMIT + 1];
    int i;
    int p;

    for (i = 0; i <= LIMIT; i++) {
        is_prime[i] = 1;
    }

    is_prime[0] = 0;
    is_prime[1] = 0;

    for (p = 2; p * p <= LIMIT; p++) {
        if (is_prime[p]) {
            for (i = p * p; i <= LIMIT; i += p) {
                is_prime[i] = 0;
            }
        }
    }

    printf("Prime numbers up to %d:\n", LIMIT);
    for (i = 2; i <= LIMIT; i++) {
        if (is_prime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
