#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	VARY_NONE,
	VARY_INCREASING,
	VARY_DECREASING,
} VaryKind;

char *find_non_digit(char *buf) {
	while(isdigit(*buf)) {
		buf++;
	}

	return buf;
}

typedef struct {
	uint32_t levels[16];
	size_t len;
} Report;

bool is_report_safe(Report *report) {
	uint32_t prev_level = 0;
	VaryKind vary = VARY_NONE;

	for(size_t i = 0; i < report->len; i++) {
		uint32_t level = report->levels[i];

		if(prev_level == 0) {
			goto end;
		}

		if(vary == VARY_NONE) {
			if(prev_level < level) {
				vary = VARY_INCREASING;
			} else {
				vary = VARY_DECREASING;
			}
		}

		size_t diff = abs((int32_t)(level - prev_level));
		if(
			(prev_level < level && vary == VARY_DECREASING) ||
			(prev_level > level && vary == VARY_INCREASING) ||
			diff < 1 ||
			diff > 3) {
			return false;
		}

	end:
		prev_level = level;
	}

	return true;
}

bool is_report_safe_without_one(Report *report) {
	for(size_t i = 0; i < report->len; i++) {
		Report tmp = *report;
		size_t len = --tmp.len;

		if(i < len) {
			memcpy(&tmp.levels[i], &report->levels[i + 1], sizeof(uint32_t) * len);
		}

		if(is_report_safe(&tmp)) {
			return true;
		}
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

	Report reports[2048] = {0};
	size_t len = 0;

	for(size_t i = 0; i < size; i++) {
		char *end_of_digit = find_non_digit(buf + i);
		bool is_end_of_report = *end_of_digit == '\n';

		if(isdigit(buf[i])) {
			*end_of_digit = '\0';

			uint32_t level = atoi(buf + i);
			reports[len].levels[reports[len].len++] = level;
			i = end_of_digit - buf;
		}

		if(is_end_of_report) {
			len++;
		}
	}

	size_t safe_reports = 0;
	size_t safe_reports_without_one = 0;

	for(size_t i = 0; i < len; i++) {
		if(is_report_safe(&reports[i])) {
			safe_reports++;
		} else if(is_report_safe_without_one(&reports[i])) {
			safe_reports_without_one++;
		}
	}

	printf("%zu reports are safe\n", safe_reports);
	printf("%zu reports are safe without one\n", safe_reports + safe_reports_without_one);
}
