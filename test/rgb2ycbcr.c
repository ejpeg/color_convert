#include <stdio.h>

#include "color_convert.h"

void
ppm_to_ycbcr(FILE *input) {
}

int
main(int argc,
	char **argv) {

	if(argc > 2) {
		char **iterator = argv + 1, ** const end = argv + argc;

		while(iterator < end) {
			FILE *input = fopen(*iterator, "r");

			if(input != NULL) {
				ppm_to_ycbcr(input);

				fclose(input);
			}

			iterator++;
		}
	} else {
		ppm_to_ycbcr(stdin);
	}

	return 0;
}

