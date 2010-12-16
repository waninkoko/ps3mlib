/*
 * camera.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_CAMERA_H_
#define _PS3MLIB_CAMERA_H_

#include "types.h"

EXTERN_BEGIN

/* Prototypes */
s32   Camera_Init(void);
void  Camera_Quit(void);
s32   Camera_Connect(void);
void  Camera_Disconnect(void);
bool  Camera_IsOpen(void);
bool  Camera_IsAvailable(void);
void *Camera_GetBuffer(void);
s32   Camera_GetWidth(void);
s32   Camera_GetHeight(void);
s32   Camera_Read(void);
s32   Camera_Draw(s32 x, s32 y);

EXTERN_END

#endif	/* _PS3MLIB_CAMERA_H_ */
