/*
 * syscalls.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_SYSCALLS_H_
#define _PS3MLIB_SYSCALLS_H_

#include <psl1ght/lv2.h>

/* Macros */
#define LV2_SYSCALL64	LV2_INLINE u64


LV2_SYSCALL64 LV2_Peek(u64 address)
{
	/* Syscall 6 */
	return Lv2Syscall1(6, address);
}

LV2_SYSCALL LV2_Poke(u64 address, u64 value)
{
	/* Syscall 7 */
	return Lv2Syscall2(7, address, value);
}

LV2_SYSCALL LV2_MapDevice(const char *oldpath, const char *newpath)
{
	/* Syscall 35 */
	return Lv2Syscall2(35, (u64)oldpath, (u64)newpath);
}

LV2_SYSCALL LV2_MapBDVD(const char *path)
{
	/* Syscall 36 */
	return Lv2Syscall1(36, (u64)path);
}

LV2_SYSCALL LV2_Mount(const char *device, const char *format, const char *point, s32 a, s32 b, s32 c, void *buffer, u32 len)
{
	/* Syscall 837 */
	return Lv2Syscall8(837, (u64)device, (u64)format, (u64)point, a, b, c, (u64)buffer, len);
}

#endif	/* _PS3MLIB_SYSCALLS_H_ */
