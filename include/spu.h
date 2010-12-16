/*
 * spu.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_SPU_H_
#define _PS3MLIB_SPU_H_

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
s32 SPU_Init(void);
s32 SPU_LoadELF(const void *module, u32 *spu);

EXTERN_END

#endif	/* _PS3MLIB_SPU_H_ */
