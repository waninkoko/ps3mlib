/*
 * endian.h -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef _PS3MLIB_ENDIAN_H_
#define _PS3MLIB_ENDIAN_H_

#include "types.h"

inline u16 Swap16(u16 val)
{
	return ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
}

inline u32 Swap32(u32 val)
{
	return ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
	       ((val & 0xFF000000) >> 24) | ((val & 0x00FF0000) >> 8);
}

inline u64 Swap64(u64 val)
{
	return ((val & 0x00000000000000FF) << 56) |
	       ((val & 0x000000000000FF00) << 40) |
	       ((val & 0x0000000000FF0000) << 24) |
	       ((val & 0x00000000FF000000) << 8)  |
	       ((val & 0x000000FF00000000) >> 8)  |
	       ((val & 0x0000FF0000000000) >> 24) |
	       ((val & 0x00FF000000000000) >> 40) |
	       ((val & 0xFF00000000000000) >> 56);
}

#endif	/* _PS3MLIB_ENDIAN_H_ */
