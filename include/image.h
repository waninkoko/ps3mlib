/*
 * image.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_IMAGE_H_
#define _PS3MLIB_IMAGE_H_

#include <pngdec/loadpng.h>

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
s32 Image_LoadPNG (PngDatas *image, const void *buffer, u32 len);
s32 Image_DrawPNG (PngDatas *image, u32 x, u32 y);
s32 Image_DrawRGBA(u32 *buffer, u32 w, u32 h, u32 x, u32 y);
s32 Image_DrawXRGB(u32 *buffer, u32 w, u32 h, u32 x, u32 y);
s32 Image_DrawYUV (u32 *buffer, u32 w, u32 h, u32 x, u32 y);

EXTERN_END

#endif	/* _PS3MLIB_IMAGE_H_ */
