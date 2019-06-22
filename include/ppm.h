#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdint.h>

int
ppm_p3_read(FILE *stream, uint8_t **buffer,
	size_t *width, size_t *height);

int
ppm_p3_write(FILE *stream, const uint8_t *buffer,
	size_t width, size_t height);

/* PPM_H */
#endif
