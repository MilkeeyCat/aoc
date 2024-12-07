#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD 0
#define MUL 1

typedef struct {
	size_t result;
	size_t nums[32];
	size_t nums_len;
} Equation;

char *find_non_digit(char *buf) {
	while(isdigit(*buf)) {
		buf++;
	}

	return buf;
}

bool check_ops(size_t *nums, size_t nums_len, size_t target, size_t value) {
	if(nums_len == 0) {
		return value == target;
	}

	if(check_ops(nums + 1, nums_len - 1, target, value + *nums)) {
		return true;
	}

	if(check_ops(nums + 1, nums_len - 1, target, value * *nums)) {
		return true;
	}

	char buf[16];
	size_t len = sprintf(buf, "%zu%zu", value, *nums);
	buf[len] = '\0';
	if(check_ops(nums + 1, nums_len - 1, target, strtoull(buf, NULL, 0))) {
		return true;
	}

	return false;
}

int main() {
	FILE *fd = fopen("./input", "r");
	fseek(fd, 0, SEEK_END);

	size_t size = ftell(fd);
	rewind(fd);

	char *buf = malloc(size);
	fread(buf, 1, size, fd);

	size_t lines = 0;
	for(size_t i = 0; i < size; i++) {
		if(buf[i] == '\n') {
			lines++;
		}
	}

	Equation *equations = malloc(sizeof(Equation) * lines);
	memset(equations, 0, sizeof(Equation) * lines);

	for(size_t i = 0, equation_i = 0; i < size - 1; i++, equation_i++) {
		char *result_end = find_non_digit(&buf[i]);
		*result_end = '\0';

		size_t result = strtoull(&buf[i], NULL, 0);
		i = result_end - buf + 2;
		equations[equation_i].result = result;

		while(true) {
			char *num_end = find_non_digit(&buf[i]);
			bool is_eol = *num_end == '\n';
			*num_end = '\0';

			size_t num = atoi(&buf[i]);
			i = num_end - buf;

			equations[equation_i].nums[equations[equation_i].nums_len++] = num;

			if(is_eol) {
				break;
			}

			i++;
		}
	}

	size_t part1 = 0;

	// Works for part one as bit can be either 0 or 1
	for(size_t i = 0; i < lines; i++) {
		const size_t max = (1 << (equations[i].nums_len - 1));

		for(uint64_t state = 0; state < max; state++) {
			size_t res = equations[i].nums[0];

			for(size_t j = 1; j < equations[i].nums_len; j++) {
				uint8_t op = (state >> (j - 1)) & 1;

				if(op == ADD) {
					res += equations[i].nums[j];
				} else if(op == MUL) {
					res *= equations[i].nums[j];
				}
			}

			if(res == equations[i].result) {
				part1 += res;

				break;
			}
		}
	}

	size_t part2 = 0;

	for(size_t i = 0; i < lines; i++) {
		if(check_ops(equations[i].nums + 1, equations[i].nums_len - 1, equations[i].result, equations[i].nums[0])) {
			part2 += equations[i].result;
		}
	}

	free(buf);
	printf("Part 1: %zu\n", part1);
	printf("Part 2: %zu\n", part2);

	return 0;
}
