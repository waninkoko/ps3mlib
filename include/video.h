/*
 * video.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_VIDEO_H_
#define _PS3MLIB_VIDEO_H_

#include "types.h"

/* Color constants (XRGB) */
#define COLOR_XRGB_BLACK	0x00000000
#define COLOR_XRGB_RED		0x00FF0000
#define COLOR_XRGB_GREEN	0x0000FF00
#define COLOR_XRGB_BLUE		0x000000FF

/* Color constants (XBGR) */
#define COLOR_XBGR_BLACK	0x00000000
#define COLOR_XBGR_RED		0x000000FF
#define COLOR_XBGR_GREEN	0x0000FF00
#define COLOR_XBGR_BLUE		0x00FF0000

EXTERN_BEGIN

/* Prototypes */
s32  Video_Init(void);
u32 *Video_GetBuffer(void);
s32  Video_GetWidth(void);
s32  Video_GetHeight(void);
void Video_Clear(u32 color);
void Video_Flip(void);
void Video_WaitFlip(void);

EXTERN_END

#endif	/* _PS3MLIB_VIDEO_H_ */
