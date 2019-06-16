#include <stdio.h>

#include "color_convert.h"

void
ycbcr_to_ppm(FILE *input) {
}

int
main(int argc,
	char **argv) {

	if(argc > 2) {
		char **iterator = argv + 1, ** const end = argv + argc;

		while(iterator < end) {
			FILE *input = fopen(*iterator, "r");

			if(input != NULL) {
				ycbcr_to_ppm(input);

				fclose(input);
			}

			iterator++;
		}
	} else {
		ycbcr_to_ppm(stdin);
	}

	return 0;
}

