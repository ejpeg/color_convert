#include "color_convert.h"

void
color_convert_rgb_to_ycbcr(const uint8_t *rgb, uint8_t *ycbcr, size_t count) {
	const uint8_t * const end = rgb + count * RGB_COLORSPACE_SIZE;

	while(rgb != end) {
		const uint16_t r = rgb[0], g = rgb[1], b = rgb[2];

		ycbcr[0] = (76 * r + 150 * g + 29 * b) >> 8;
		ycbcr[1] = 128 - (( 43 * r + 85 * g) >> 8) + (b >> 1);
		ycbcr[2] = 128 - ((107 * g + 21 * b) >> 8) + (r >> 1);

		rgb += RGB_COLORSPACE_SIZE;
		ycbcr += YCBCR_COLORSPACE_SIZE;
	}
}

void
color_convert_ycbcr_to_rgb(const uint8_t *ycbcr, uint8_t *rgb, size_t count) {
	const uint8_t * const end = ycbcr + count * YCBCR_COLORSPACE_SIZE;

	while(ycbcr != end) {
		const uint16_t y = ycbcr[0], cb = ycbcr[1], cr = ycbcr[2];

		rgb[0] = y                    + 358 * (cr - 128);
		rgb[1] = y -  88 * (cb - 128) - 182 * (cr - 128);
		rgb[2] = y + 452 * (cb - 128);

		ycbcr += YCBCR_COLORSPACE_SIZE;
		rgb += RGB_COLORSPACE_SIZE;
	}
}

