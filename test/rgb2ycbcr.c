#include <stdio.h>
#include <stdlib.h>

#include "color_convert.h"

void
ppm_to_ycbcr(FILE *input, FILE *output) {
	char magicnumber[3];
	unsigned int width, height, colorspace;

	fscanf(input, "%2s %u %u %u", magicnumber, &width, &height, &colorspace);
	
	unsigned int size = width * height;
	
	uint8_t *rgb = malloc(sizeof(uint8_t) * size * RGB_COLORSPACE_SIZE);

	for (unsigned int i = 0; i < size; i++) {
		unsigned int r, g, b;
		fscanf(input, "%u %u %u", &r, &g, &b);
		rgb[0] = (uint8_t)r;
		rgb[1] = (uint8_t)g;
		rgb[2] = (uint8_t)b;
		rgb += RGB_COLORSPACE_SIZE;
	}

	uint8_t *ycbcr = malloc(sizeof(uint8_t) * size * YCBCR_COLORSPACE_SIZE);

	color_convert_rgb_to_ycbcr(rgb, ycbcr, size);

	fwrite(ycbcr, sizeof(uint8_t) * size * YCBCR_COLORSPACE_SIZE, 1, output);

	free(rgb);
	free(ycbcr);
}

int
main(int argc,
	char **argv) {

	if(argc > 1) {
		char **iterator = argv + 1, ** const end = argv + argc;

		while(iterator < end) {
			FILE *input = fopen(*iterator, "r");

			if(input != NULL) {
				ppm_to_ycbcr(input, stdout);

				fclose(input);
			}

			iterator++;
		}
	} else {
		ppm_to_ycbcr(stdin, stdout);
	}

	return 0;
}

