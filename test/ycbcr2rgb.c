#include "ppm.h"
#include "color_convert.h"

#include <stdlib.h>

int
ycbcr_to_rgb(FILE *output, const uint8_t *ycbcr,
	size_t width, size_t height) {
	size_t size = width * height;
	uint8_t *rgb = malloc(size * 3);

	color_convert_ycbcr_to_rgb(ycbcr, rgb, size);

	return ppm_p3_write(output, rgb, width, height);
}

int
main(int argc,
	char **argv) {

	if(argc == 3) {
		FILE *input, *output;
		uint8_t *buffer;
		size_t width, height;

		if((input = fopen(argv[1], "r")) != NULL
			&& (output = fopen(argv[2], "w")) != NULL
			&& ppm_p3_read(input, &buffer, &width, &height) == 0
			&& ycbcr_to_rgb(output, buffer, width, height) == 0) {
			return 0;
		}
	} else {
		fprintf(stderr, "usage: ppm2ppm <input> <output>\n");
	}

	return 1;
}

