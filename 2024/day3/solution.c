#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VALID_LEN 8

char *find_non_digit(char *buf) {
	while(isdigit(*buf)) {
		buf++;
	}

	return buf;
}

int main() {
	FILE *fd = fopen("./input", "r");
	fseek(fd, 0, SEEK_END);

	size_t size = ftell(fd);
	rewind(fd);

	char *buf = malloc(size);
	fread(buf, 1, size, fd);

	bool mul_enabled = true;
	size_t sum = 0;
	size_t sum_with_mul_enabled = 0;

	for(size_t i = 0; i < size; i++) {
		if(i < size - MIN_VALID_LEN && memcmp(&buf[i], "mul(", 4) == 0) {
			i += 4;

			char *lhs_end = find_non_digit(buf + i);
			if(lhs_end && *lhs_end != ',') {
				continue;
			}
			*lhs_end = '\0';
			uint32_t lhs = atoi(buf + i);
			i = lhs_end - buf + 1;

			char *rhs_end = find_non_digit(buf + i);
			if(lhs_end && *rhs_end != ')') {
				continue;
			}
			*rhs_end = '\0';
			uint32_t rhs = atoi(buf + i);
			i = rhs_end - buf;

			sum += lhs * rhs;

			if(mul_enabled) {
				sum_with_mul_enabled += lhs * rhs;
			}
		} else if(i < size - 7 && memcmp(&buf[i], "don't()", 7) == 0) {
			mul_enabled = false;
		} else if(i < size - 4 && memcmp(&buf[i], "do()", 4) == 0) {
			mul_enabled = true;
		}
	}

	printf("Part 1: %zu\n", sum);
	printf("Part 2: %zu\n", sum_with_mul_enabled);

	return 0;
}
