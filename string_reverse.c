#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------ */
int main(void)
{
    const char *original = "Hello, Devin!";
    char reversed[32];
    size_t len = strlen(original);
    size_t i;

    if (len >= sizeof(reversed)) {
        fprintf(stderr, "Input string is too long to reverse.\n");
        return 1;
    }

    for (i = 0; i < len; i++) {
        reversed[i] = original[len - 1 - i];
    }
    reversed[len] = '\0';

    printf("Original: %s\n", original);
    printf("Reversed: %s\n", reversed);

    return 0;
}
