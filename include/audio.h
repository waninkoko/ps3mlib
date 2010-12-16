/*
 * audio.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_AUDIO_H_
#define _PS3MLIB_AUDIO_H_

#include <audio/audio.h>

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
s32  Audio_Init(u32 channels);
void Audio_Quit(void);
u32  Audio_GetPort(void);

EXTERN_END

#endif	/* _PS3MLIB_AUDIO_H_ */
