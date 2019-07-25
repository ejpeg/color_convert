#include "color_convert.h"

#if defined(CONVERT_VECTOR_EXTENSION) && defined(__has_attribute) && __has_attribute(ext_vector_type)
typedef int16_t vec3_t __attribute__((ext_vector_type(3)));

void
color_convert_rgb_to_ycbcr(const uint8_t *rgb, uint8_t *ycbcr, size_t count) {
	static const vec3_t
		c0 = {   0, 32767, 32767 },
		c1 = {  76,   -43,   127 },
		c2 = { 150,   -85,  -107 },
		c3 = {  29,   127,   -21 };
	const uint8_t * const end = rgb + count * RGB_COLORSPACE_SIZE;

	while(rgb != end) {
		const vec3_t r = { rgb[0], rgb[0], rgb[0] },
			g = { rgb[1], rgb[1], rgb[1] },
			b = { rgb[2], rgb[2], rgb[2] };

		const vec3_t converted = (c0 + (c1 * r) + (c2 * g) + (c3 * b)) >> 8;

		ycbcr[0] = converted.x;
		ycbcr[1] = converted.y;
		ycbcr[2] = converted.z;

		rgb += RGB_COLORSPACE_SIZE;
		ycbcr += YCBCR_COLORSPACE_SIZE;
	}
}

void
color_convert_ycbcr_to_rgb(const uint8_t *ycbcr, uint8_t *rgb, size_t count) {
	static const vec3_t
		c0 = { 128,  128, 128 },
		c1 = {   0,  -88, 452 },
		c2 = { 358, -182,   0 };
	const uint8_t * const end = ycbcr + count * YCBCR_COLORSPACE_SIZE;

	while(ycbcr != end) {
		const vec3_t y = { ycbcr[0], ycbcr[0], ycbcr[0] },
			cb = { ycbcr[1], ycbcr[1], ycbcr[1] },
			cr = { ycbcr[2], ycbcr[2], ycbcr[2] };

		const vec3_t converted = y + ((c1 * (cb - c0) + c2 * (cr - c0)) >> 8);

		rgb[0] = converted.x;
		rgb[1] = converted.y;
		rgb[2] = converted.z;

		ycbcr += YCBCR_COLORSPACE_SIZE;
		rgb += RGB_COLORSPACE_SIZE;
	}
}
#else
#ifdef CONVERT_VECTOR_EXTENSION
#warning "Convert vector extension not available, extension not supported"
#endif

void
color_convert_rgb_to_ycbcr(const uint8_t *rgb, uint8_t *ycbcr, size_t count) {
	const uint8_t * const end = rgb + count * RGB_COLORSPACE_SIZE;

	while(rgb != end) {
		const uint16_t r = rgb[0], g = rgb[1], b = rgb[2];

		ycbcr[0] = (    0 + (76  * r) + (150 * g) + (29  * b)) >> 8;
		ycbcr[1] = (32768 - (43  * r) - (85  * g) + (127 * b)) >> 8;
		ycbcr[2] = (32768 + (127 * r) - (107 * g) - (21  * b)) >> 8;

		rgb += RGB_COLORSPACE_SIZE;
		ycbcr += YCBCR_COLORSPACE_SIZE;
	}
}

void
color_convert_ycbcr_to_rgb(const uint8_t *ycbcr, uint8_t *rgb, size_t count) {
	const uint8_t * const end = ycbcr + count * YCBCR_COLORSPACE_SIZE;

	while(ycbcr != end) {
		const uint16_t y = ycbcr[0], cb = ycbcr[1], cr = ycbcr[2];

		rgb[0] = y + (                   (358 * (cr - 128)) >> 8);
		rgb[1] = y - (( 88 * (cb - 128) + 182 * (cr - 128)) >> 8);
		rgb[2] = y + ((452 * (cb - 128)                   ) >> 8);

		ycbcr += YCBCR_COLORSPACE_SIZE;
		rgb += RGB_COLORSPACE_SIZE;
	}
}
#endif

