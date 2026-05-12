#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define BUFFER_SIZE  256
#define MAX_NUMBERS  100

static int compare_ll(const void *a, const void *b) {
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    return (x > y) - (x < y);
}

static int parse_numbers(const char *str, long long out[], int out_capacity) {
    int count = 0;
    char *end;

    while (*str != '\0' && count < out_capacity) {
        if (isdigit((unsigned char)*str) || (*str == '-' && isdigit((unsigned char)*(str + 1)))) {
            out[count++] = strtoll(str, &end, 10);
            str = end;
        } else {
            str++;
        }
    }

    return count;
}

static void print_array(const long long arr[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%lld", arr[i]);
        if (i < count - 1) printf(", ");
    }
    printf("\n");
}

/* Uppercase all alphabetic characters in-place, leave everything else untouched.
 * Uses wide chars to handle UTF-8 and multi-byte encodings correctly. */
static void uppercase_string(char *str, size_t capacity) {
    wchar_t wide[BUFFER_SIZE];

    if (mbstowcs(wide, str, BUFFER_SIZE) == (size_t)-1)
        return;

    for (int i = 0; wide[i] != L'\0'; i++) {
        if (!iswdigit(wide[i]))
            wide[i] = towupper(wide[i]);
    }

    wcstombs(str, wide, capacity);
}

int main(void) {
    setlocale(LC_ALL, "");

    char      input[BUFFER_SIZE];
    long long numbers[MAX_NUMBERS];

    printf("Enter text with numbers: ");
    if (!fgets(input, sizeof(input), stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    uppercase_string(input, sizeof(input));
    printf("Uppercased: %s", input);

    int count = parse_numbers(input, numbers, MAX_NUMBERS);

    if (count == 0) {
        printf("No numbers found.\n");
        return 0;
    }

    qsort(numbers, (size_t)count, sizeof(long long), compare_ll);

    printf("Found %d number(s), sorted: ", count);
    print_array(numbers, count);

    return 0;
}
