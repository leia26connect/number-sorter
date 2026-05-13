#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdint.h>
#include <inttypes.h>

#define BUFFER_SIZE  256
#define MAX_NUMBERS  100

static int compare_i64(const void *a, const void *b) {
	int64_t x = *(const int64_t *)a;
	int64_t y = *(const int64_t *)b;
	return (x > y) - (x < y);
}

static int parse_numbers(const char *str, int64_t out[], int out_capacity) {
	int count = 0;
	char *end;

	while (*str != '\0' && count < out_capacity) {
		if (isdigit((unsigned char)*str) || (*str == '-' && isdigit((unsigned char)*(str + 1)))) {
			out[count++] = (int64_t)strtoll(str, &end, 10);
			str = end;
		} else {
			str++;
		}
	}

	return count;
}

static void print_array(const int64_t arr[], int count) {
	for (int i = 0; i < count; i++) {
		printf("%" PRId64, arr[i]);
		if (i < count - 1) printf(", ");
	}
	printf("\n");
}

static char *uppercase_string(char *str, size_t capacity) {
	wchar_t wide[BUFFER_SIZE];

	if (mbstowcs(wide, str, BUFFER_SIZE) == (size_t)-1)
		return str;

	for (int i = 0; wide[i] != L'\0'; i++) {
		if (!iswdigit(wide[i]))
			wide[i] = towupper(wide[i]);
	}

	wcstombs(str, wide, capacity);
	return str;
}

int main(void) {
	setlocale(LC_ALL, "");

	char    input[BUFFER_SIZE];
	int64_t numbers[MAX_NUMBERS];

	printf("Enter text with numbers: ");
	if (!fgets(input, sizeof(input), stdin)) {
		fprintf(stderr, "Failed to read input.\n");
		return 1;
	}

	printf("Uppercased: %s", uppercase_string(input, sizeof(input)));

	int count = parse_numbers(input, numbers, MAX_NUMBERS);

	if (count == 0) {
		printf("No numbers found.\n");
		return 0;
	}

	qsort(numbers, (size_t)count, sizeof(int64_t), compare_i64);

	printf("Found %d number(s), sorted: ", count);
	print_array(numbers, count);

	return 0;
}
