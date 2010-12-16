/*
 * fs.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_FS_H_
#define _PS3MLIB_FS_H_

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
s32 Fs_MakeDir (const char *path);
s32 Fs_CopyFile(const char *source, const char *dest);
s32 Fs_CopyDir (const char *source, const char *dest);

EXTERN_END

#endif	/* _PS3MLIB_FS_H_ */
