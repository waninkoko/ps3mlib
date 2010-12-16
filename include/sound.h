/*
 * sound.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_SOUND_H_
#define _PS3MLIB_SOUND_H_

#include <audioplayer.h>

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
FILE *Sound_OpenMem(const void *buffer, u32 len);
void  Sound_CloseMem(FILE *fp);
s32   Sound_Init(void);
s32   Sound_Play(FILE *fp, s32 pos, s32 mode);
void  Sound_Stop(void);
void  Sound_Pause(bool pause);

EXTERN_END

#endif	/* _PS3MLIB_SOUND_H_ */
