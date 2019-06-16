#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

#include <sys/types.h>
#include <stdint.h>

#define RGB_COLORSPACE_SIZE 3
#define YCBCR_COLORSPACE_SIZE 3

void
color_convert_rgb_to_ycbcr(const uint8_t *rgb, uint8_t *ycbcr, size_t count);

void
color_convert_ycbcr_to_rgb(const uint8_t *ycbcr, uint8_t *rgb, size_t count);

/* COLOR_CONVERT_H */
#endif
