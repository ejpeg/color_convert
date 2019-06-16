#include "ppm.h"

#include <stdlib.h>

int
ppm_p3_read(FILE *stream, uint8_t **buffer,
	size_t *width, size_t *height) {
	char magicnumber[3];
	unsigned int colorspace;

	if(fscanf(stream, "%2s %lu %lu %u",
		magicnumber, width, height, &colorspace) != 4
		|| magicnumber[0] != 'P'
		|| magicnumber[1] != '3'
		|| colorspace != 255) {
		return -1;
	}

	size_t length = *width * *height * 3;
	uint8_t *rgb = malloc(length);
	uint8_t * const end = rgb + length;

	if(rgb == NULL) {
		return -1;
	}

	*buffer = rgb;
	while(rgb != end) {
		unsigned int r, g, b;

		if(fscanf(stream, "%u %u %u", &r, &g, &b) != 3) {
			return -1;
		}

		rgb[0] = (uint8_t)r;
		rgb[1] = (uint8_t)g;
		rgb[2] = (uint8_t)b;

		rgb += 3;
	}

	return 0;
}

int
ppm_p3_write(FILE *stream, const uint8_t *buffer,
	size_t width, size_t height) {

	if(fprintf(stream, "P3\n%lu %lu\n255\n", width, height) < 0) {
		return -1;
	}

	const uint8_t * const end = buffer + width * height * 3;
	while(buffer != end) {
		if(fprintf(stream, "%u %u %u\n", buffer[0], buffer[1], buffer[2]) < 0) {
			return -1;
		}

		buffer += 3;
	}

	return 0;
}

