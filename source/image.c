/*
 * image.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <string.h>
#include <errno.h>

#include "image.h"
#include "video.h"

/* Macros */
#define RGBA_TO_XRGB(p)		((p) >> 8)


static u32 __Image_YUV2RGB(s32 y, s32 u, s32 v)
{
	s32 r, g, b;

	v -= 128;
	u -= 128;

	/* Convert to RGB */
	r = y + u;
	g = y - (y >> 1) - (v >> 3);
	b = y + v;

	/* Check values */
	if (r < 0)   r = 0;
	if (g < 0)   g = 0;
	if (b < 0)   b = 0;
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	/* Return pixel */
	return (r << 16 | g << 8 | b);
}


s32 Image_LoadPNG(PngDatas *image, const void *buffer, u32 len)
{
	/* Setup image */
	image->png_in   = (void *)buffer;
	image->png_size = len;

	/* Load image */
	return LoadPNG(image, NULL);
}

s32 Image_DrawPNG(PngDatas *image, u32 x, u32 y)
{
	/* Draw PNG image */
	return Image_DrawXRGB(image->bmp_out, image->width, image->height, x, y);
}

s32 Image_DrawRGBA(u32 *buffer, u32 w, u32 h, u32 x, u32 y)
{
	u32 *screen;

	s32  height, width;
	s32  i, j;

	/* Get video buffer */
	screen = Video_GetBuffer();
	if (!screen)
		return -EINVAL;

	/* Get video resolution */
	width  = Video_GetWidth();
	height = Video_GetHeight();

	/* Out of screen */
	if ((x >= width) || (y >= height) ||
	    (x + w <= 0) || (y + h <= 0))
		return 0;

	/* Draw image */
	for (i = y; i < (y + h); i++)
	for (j = x; j < (x + w); j++) {
		/* Draw pixel */
		if (j >= 0 && j < width &&
		    i >= 0 && i < height)
			screen[i * width + j] = RGBA_TO_XRGB(*buffer);

		/* Update pointer */
		buffer++;
	}

	return 0;
}

s32 Image_DrawXRGB(u32 *buffer, u32 w, u32 h, u32 x, u32 y)
{
	u32 *screen;

	s32  height, width;
	s32  i, j;

	/* Get video buffer */
	screen = Video_GetBuffer();
	if (!screen)
		return -EINVAL;

	/* Get video resolution */
	width  = Video_GetWidth();
	height = Video_GetHeight();

	/* Out of screen */
	if ((x >= width) || (y >= height) ||
	    (x + w <= 0) || (y + h <= 0))
		return 0;

#if 0
	for (i = y; i < (y + h) && i < height; i++) {
		void *dst = screen + (i * width);
		void *src = buffer + (w * (i - y));
		u32   len = w;

		/* Non-visible line */
		if (i < 0) continue;

		/* Pixels to copy */
		if (x < 0) len += x;
		if ((x + w) > width) len -= (x + w) - width;

		/* Skip non-visible pixels */
		if (x > 0) dst += x;
		if (x < 0) src -= x;

		/* Copy line */
		memcpy(dst, src, len * 4);
	}
#endif

	/* Draw image */
	for (i = y; i < (y + h); i++)
	for (j = x; j < (x + w); j++) {
		/* Draw pixel */
		if (j >= 0 && j < width &&
		    i >= 0 && i < height)
			screen[i * width + j] = *buffer;

		/* Update pointer */
		buffer++;
	}

	return 0;
}

s32 Image_DrawYUV(u32 *buffer, u32 w, u32 h, u32 x, u32 y)
{
	u32 *screen;

	s32  height, width;
	s32  i, j;

	/* Get video buffer */
	screen = Video_GetBuffer();
	if (!screen)
		return -EINVAL;

	/* Get video resolution */
	width  = Video_GetWidth();
	height = Video_GetHeight();

	/* Out of screen */
	if ((x >= width) || (y >= height) ||
	    (x + w <= 0) || (y + h <= 0))
		return 0;

	/* Draw image */
	for (i = y; i < (y + h); i++)
	for (j = x; j < (x + w); j += 2) {
		u32 *dst = screen + (i * width) + j;
		u8  *src = (u8 *)buffer;

		/* Draw pixels */
		if (j >= 0 && j < width &&
		    i >= 0 && i < height) {
			dst[0] = __Image_YUV2RGB(src[0], src[3], src[1]);
			dst[1] = __Image_YUV2RGB(src[2], src[3], src[1]);
		}

		/* Update pointer */
		buffer++;
	}

	return 0;
}
