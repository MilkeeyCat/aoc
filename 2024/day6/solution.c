#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int32_t x;
	int32_t y;
	int8_t dir_x;
	int8_t dir_y;
} Point;

bool is_loop(const char *map, size_t w, size_t h, Point point, Point *visited_points) {
	size_t visited_points_len = 0;

	while(point.x >= 0 && point.x <= w && point.y >= 0 && point.y <= h) {
		const char *next = map + (point.y + point.dir_y) * (w + 1) + point.x + point.dir_x;

		if(*next == '#') {
			for(size_t i = 0; i < visited_points_len; i++) {
				if(
					visited_points[i].x == point.x &&
					visited_points[i].y == point.y &&
					visited_points[i].dir_x == point.dir_x &&
					visited_points[i].dir_y == point.dir_y) {
					return true;
				}
			}

			visited_points[visited_points_len].x = point.x;
			visited_points[visited_points_len].y = point.y;
			visited_points[visited_points_len].dir_x = point.dir_x;
			visited_points[visited_points_len].dir_y = point.dir_y;
			visited_points_len++;

			int8_t tmp = point.dir_x;
			point.dir_x = point.dir_x != 0 ? 0 : point.dir_y * -1;
			point.dir_y = point.dir_y != 0 ? 0 : tmp;
		} else {
			point.x += point.dir_x;
			point.y += point.dir_y;
		}
	}

	return false;
}

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
	int32_t start_x = pos_x, start_y = pos_y;
	Point *points = malloc(sizeof(Point) * w * h);
	char **unique_points = malloc(sizeof(char *) * w * h);
	size_t unique_points_len = 0;
	size_t part2 = 0;

	while(pos_x >= 0 && pos_x <= w && pos_y >= 0 && pos_y < h) {
		map[pos_y * (w + 1) + pos_x] = 'X';
		char *next = map + (pos_y + dir_y) * (w + 1) + pos_x + dir_x;

		if(*next == '#') {
			int8_t tmp = dir_x;
			dir_x = dir_x != 0 ? 0 : dir_y * -1;
			dir_y = dir_y != 0 ? 0 : tmp;
		} else {
			pos_x += dir_x;
			pos_y += dir_y;
		}

		if(*next != '#') {
			char tmp = *next;

			*next = '#';
			if(is_loop(map, w, h, (Point){.x = start_x, .y = start_y, .dir_x = 0, .dir_y = -1}, points)) {
				bool exists = false;
				for(size_t i = 0; i < unique_points_len; i++) {
					if(unique_points[i] == next) {
						exists = true;
						break;
					}
				}

				if(!exists && (next != &map[start_y * (w + 1) + start_x])) {
					unique_points[unique_points_len++] = next;
					part2++;
				}
			}
			*next = tmp;
		}
	}

	size_t part1 = 0;

	for(size_t i = 0; i < size; i++) {
		if(map[i] == 'X') {
			part1++;
		}
	}

	printf("Part 1: %zu\n", part1);
	printf("Part 2: %zu\n", part2);

	return 0;
}
