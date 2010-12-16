/*
 * pad.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_PAD_H_
#define _PS3MLIB_PAD_H_

#include <io/pad.h>

#include "types.h"

EXTERN_BEGIN

/* Buttons constants */
#define PAD_LEFT	(1 << 0)
#define PAD_DOWN	(1 << 1)
#define PAD_RIGHT	(1 << 2)
#define PAD_UP		(1 << 3)
#define PAD_START	(1 << 4)
#define PAD_R3		(1 << 5)
#define PAD_L3		(1 << 6)
#define PAD_SELECT	(1 << 7)
#define PAD_SQUARE	(1 << 16)
#define PAD_CROSS	(1 << 17)
#define PAD_CIRCLE	(1 << 18)
#define PAD_TRIANGLE	(1 << 19)
#define PAD_R1		(1 << 20)
#define PAD_L1		(1 << 21)
#define PAD_R2		(1 << 22)
#define PAD_L2		(1 << 23)

/* Prototypes */
s32  Pad_Init(void);
void Pad_GetButtons(s32 pad, PadData *res);

#if 0
bool Pad_IsPressed(s32 pad, u16 button);
#endif

EXTERN_END

#endif	/* _PS3MLIB_PAD_H_ */
