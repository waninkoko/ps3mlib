/*
 * spu.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <string.h>
#include <malloc.h>
#include <errno.h>

#include <psl1ght/lv2/spu.h>

#include "types.h"

/* Macros */
#define SPU_SIZE(x) (((x) + 127) & ~127)

/* SPU flag */
static bool inited = false;


s32 SPU_Init(void)
{
	s32 ret;

	/* Already inited */
	if (inited)
		return 0;

	/* Initialize SPUs */
	ret = lv2SpuInitialize(6, 5);
	if (!ret)
		inited = true;

	return ret;
}

s32 SPU_LoadELF(const void *module, u32 *spu)
{
	sysSpuSegment *segments;
	sysSpuImage    image;

	size_t len;
	u32    entry, count, s;
	s32    ret;

	/* Create raw SPU */
	ret = lv2SpuRawCreate(&s, NULL);
	if (ret)
		return ret;

	/* Get ELF information */
	sysSpuElfGetInformation(module, &entry, &count);

	/* Segment length */
	len = sizeof(sysSpuSegment) * count;

	/* Allocate memory for segments */
	segments = memalign(128, SPU_SIZE(len));
	if (!segments)
		return -ENOMEM;

	memset(segments, 0, len);

	/* Get ELF segments */
	sysSpuElfGetSegments(module, segments, count);

	/* Load ELF image */
	ret = sysSpuImageImport(&image, module, 0);
	if (ret)
		goto err;

	/* Load image into SPU */
	ret = sysSpuRawImageLoad(s, &image);
	if (ret)
		goto err;

	/* Copy SPU value */
	*spu = s;

	return 0;

err:
	/* Free memory */
	if (segments)
		free(segments);

	return ret;
}
