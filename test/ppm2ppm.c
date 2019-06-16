#include "ppm.h"

int
main(int argc,
	char **argv) {

	if(argc == 3) {
		FILE *input, *output;
		uint8_t *buffer;
		size_t width, height;

		if((input = fopen(argv[1], "r")) != NULL
			&& (output = fopen(argv[2], "r")) != NULL
			&& ppm_p3_read(input, &buffer, &width, &height) == 0
			&& ppm_p3_write(output, buffer, width, height) == 0) {
			return 0;
		}
	} else {
		fprintf(stderr, "usage: ppm2ppm <input> <output>\n");
	}

	return 1;
}

