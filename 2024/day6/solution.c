#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *fd = fopen("./input", "r");
	fseek(fd, 0, SEEK_END);

	size_t size = ftell(fd);
	rewind(fd);

	char *map = malloc(size);
	fread(map, 1, size, fd);

	int32_t pos_x = 0, pos_y = 0;
	int8_t dir_x = 0, dir_y = -1;
	size_t w = strchr(map, '\n') - map;
	size_t h = size / (w + 1);
	size_t pos = strchr(map, '^') - map;
	pos_x = pos % (w + 1);
	pos_y = (pos - pos_x) / w;

	while(pos_x >= 0 && pos_x <= w && pos_y >= 0 && pos_y < h) {
		map[pos_y * (w + 1) + pos_x] = 'X';
		char *next = map + (pos_y + dir_y) * (w + 1) + pos_x + dir_x;

		if(*next == '#') {
			int8_t tmp = dir_x;
			dir_x = dir_x != 0 ? 0 : dir_y * -1;
			dir_y = dir_y != 0 ? 0 : tmp;
		}

		pos_x += dir_x;
		pos_y += dir_y;
	}

	size_t part1 = 0;

	for(size_t i = 0; i < size; i++) {
		if(map[i] == 'X') {
			part1++;
		}
	}

	printf("Part 1: %zu\n", part1);

	return 0;
}
