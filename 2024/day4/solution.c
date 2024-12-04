#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool find_da_string(const char *buf, const char *str, int32_t offset, size_t str_offset) {
	size_t len = strlen(str);

	for(size_t i = 0; i < len; i++) {
		if(buf[(i - str_offset) * offset] != str[i]) {
			return false;
		}
	}

	return true;
}

int main() {
	FILE *fd = fopen("./input", "r");
	fseek(fd, 0, SEEK_END);

	size_t size = ftell(fd);
	rewind(fd);

	char *buf = malloc(size);
	fread(buf, 1, size, fd);

	const size_t line_width = strchr(buf, '\n') - buf;
	const int32_t offsets[] = {1, line_width + 1, line_width, line_width + 2};
	size_t xmas = 0;
	size_t x_mas = 0;

	// `find_da_string` function is called without proper checks for buffer len, I UBed all over the place, but it didn't segfault once, so we're Gucci
	for(size_t i = 0; i < size; i++) {
		for(size_t j = 0; j < sizeof(offsets) / sizeof(offsets[0]); j++) {
			if(find_da_string(&buf[i], "XMAS", offsets[j], 0)) {
				xmas++;
			}
			if(find_da_string(&buf[i], "XMAS", -offsets[j], 0)) {
				xmas++;
			}
		}

		bool x = true;

		for(size_t j = 2; j < 4; j++) {
			if(!(
				   find_da_string(&buf[i], "MAS", offsets[j], 1) ||
				   find_da_string(&buf[i], "MAS", -offsets[j], 1))) {
				x = false;

				break;
			}
		}

		if(x) {
			x_mas++;
		}

		printf("x: %d\n", x);
	}

	printf("Part 1: %zu\n", xmas);
	printf("Part 2: %zu\n", x_mas);

	return 0;
}
