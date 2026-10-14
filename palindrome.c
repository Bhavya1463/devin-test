#include <stdio.h>
#include <string.h>

int is_number_palindrome(unsigned long number)
{
    unsigned long original = number;
    unsigned long reversed = 0;

    do {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    } while (number != 0);

    return original == reversed;
}

int is_string_palindrome(const char *text)
{
    size_t left = 0;
    size_t right = strlen(text);

    while (left < right) {
        right--;
        if (text[left] != text[right]) {
            return 0;
        }
        left++;
    }

    return 1;
}

int main(void)
{
    const unsigned long numbers[] = {121, 12345};
    const char *words[] = {"madam", "hello"};
    size_t i;

    for (i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        printf("%lu is %sa palindrome number.\n",
               numbers[i], is_number_palindrome(numbers[i]) ? "" : "not ");
    }

    for (i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
        printf("\"%s\" is %sa palindrome string.\n",
               words[i], is_string_palindrome(words[i]) ? "" : "not ");
    }

    return 0;
}
