#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_non_digit(char *buf) {
	while(isdigit(*buf)) {
		buf++;
	}

	return buf;
}

typedef struct {
	size_t start;
	size_t end;
} Order;

typedef struct {
	size_t pages[32];
	size_t len;
} Update;

bool check_update(Order *orders, size_t orders_len, Update *update) {
	for(size_t i = 0; i < orders_len; i++) {
		bool found_end = false;

		for(size_t j = 0; j < update->len; j++) {
			if(update->pages[j] == orders[i].end) {
				found_end = true;
			}

			if(update->pages[j] == orders[i].start && found_end) {
				return false;
			}
		}
	}

	return true;
}

void fix_udpate(Order *orders, size_t orders_len, Update *update) {
	for(size_t i = 0; i < orders_len; i++) {
		int32_t end = -1;

		for(size_t j = 0; j < update->len; j++) {
			if(update->pages[j] == orders[i].end) {
				end = j;
			}

			if(update->pages[j] == orders[i].start && end != -1) {
				size_t tmp = update->pages[j];

				update->pages[j] = update->pages[end];
				update->pages[end] = tmp;
			}
		}
	}
}

int main() {
	FILE *fd = fopen("./input", "r");
	fseek(fd, 0, SEEK_END);

	size_t size = ftell(fd);
	rewind(fd);

	char *buf = malloc(size);
	fread(buf, 1, size, fd);

	size_t orders_len = 0;
	size_t updates_len = 0;
	bool pages = false;

	for(size_t i = 0; i < size; i++) {
		if(buf[i] == '|') {
			orders_len++;
		} else if(buf[i] == '\n') {
			updates_len++;
		}
	}

	updates_len -= orders_len + 1;

	Order *orders = malloc(sizeof(Order) * orders_len);
	memset(orders, 0, sizeof(Order) * orders_len);
	Update *updates = malloc(sizeof(Update) * updates_len);
	memset(updates, 0, sizeof(Update) * updates_len);

	size_t orders_i = 0;
	size_t updates_i = 0;

	for(size_t i = 0; i < size; i++) {
		if(pages && isdigit(buf[i])) {
			char *page_end = find_non_digit(&buf[i]);
			bool is_new_line = false;
			if(*page_end == '\n') {
				is_new_line = true;
			}

			*page_end = '\0';
			updates[updates_i].pages[updates[updates_i].len++] = atoi(&buf[i]);
			i = page_end - buf;

			if(is_new_line) {
				updates_i++;
			}
		} else {
			char *start_end = find_non_digit(&buf[i]);
			*start_end = '\0';

			size_t start = atoi(&buf[i]);
			i = start_end - buf + 1;

			char *end_end = find_non_digit(&buf[i]);
			*end_end = '\0';

			size_t end = atoi(&buf[i]);
			i = end_end - buf;

			orders[orders_i].start = start;
			orders[orders_i].end = end;
			orders_i++;
		}

		if(buf[i + 1] == '\n') {
			i++;
			pages = true;
		}
	}

	size_t part1 = 0;
	size_t part2 = 0;

	for(size_t i = 0; i < updates_len; i++) {
		if(check_update(orders, orders_len, &updates[i])) {
			part1 += updates[i].pages[(updates[i].len - 1) / 2];
		} else {
			while(check_update(orders, orders_len, &updates[i]) != true) {
				fix_udpate(orders, orders_len, &updates[i]);
			}

			part2 += updates[i].pages[(updates[i].len - 1) / 2];
		}
	}

	printf("Part 1: %zu\n", part1);
	printf("Part 2: %zu\n", part2);

	return 0;
}
