#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int main(void) {
    char      input[BUFFER_SIZE];
    long long numbers[MAX_NUMBERS];

    printf("Enter text with numbers: ");
    if (!fgets(input, sizeof(input), stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

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
