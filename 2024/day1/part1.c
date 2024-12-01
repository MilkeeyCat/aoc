#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	LEFT,
	RIGHT
} Side;

char *find_non_digit(char *buf) {
	while(isdigit(*buf)) {
		buf++;
	}

	return buf;
}

int compare(const void *lhs, const void *rhs) {
	return (*(uint32_t *)lhs - *(uint32_t *)rhs);
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

	uint32_t *lhs = malloc(sizeof(uint32_t) * lines);
	uint32_t *rhs = malloc(sizeof(uint32_t) * lines);
	Side side = LEFT;
	size_t id = 0;

	for(size_t i = 0; i < size; i++) {
		if(isdigit(buf[i])) {
			*find_non_digit(buf + i) = '\0';
			size_t location_id = atoi(buf + i);

			if(side == LEFT) {
				lhs[id] = location_id;
			} else {
				rhs[id] = location_id;
				id++;
			}

			i += strlen(buf + i);
			side ^= 1;
		}
	}

	free(buf);
	qsort(lhs, lines, sizeof(uint32_t), compare);
	qsort(rhs, lines, sizeof(uint32_t), compare);

	size_t distance = 0;

	for(size_t i = 0; i < lines; i++) {
		distance += abs((int32_t)(lhs[i] - rhs[i]));
	}

	free(lhs);
	free(rhs);

	printf("Total distance: %zu\n", distance);
}
