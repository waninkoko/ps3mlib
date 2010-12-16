/*
 * pad.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <string.h>

#include "pad.h"
#include "types.h"


s32 Pad_Init(void)
{
	/* Initialize pad subsystem */
	return ioPadInit(MAX_PORT_NUM);
}

void Pad_GetButtons(s32 pad, PadData *res)
{
	PadInfo info;
	PadData data;

	/* Clear data */
	memset(res, 0, sizeof(PadData));

	/* Get pad info */
	ioPadGetInfo(&info);

	/* Read pad(s) */
	if (pad >= 0) {
		/* Get pad data */
		if (info.status[pad])
			ioPadGetData(pad, res);
	} else {
		u32 i, j;

		/* Check every pad */
		for (i = 0; i < MAX_PADS; i++) {
			if (info.status[i]) {
				/* Get pad data */
				ioPadGetData(i, &data);

				/* Copy bitmap */
				for (j = 0; j < PAD_MAX_CODES; j++)
					res->button[j] |= data.button[j];
			}
		}
	}
}

#if 0
bool Pad_IsPressed(s32 pad, u32 button)
{
	PadInfo info;
	PadData data;

	bool ret = false;

	/* Get pad info */
	ioPadGetInfo(&info);

	/* Read pad(s) */
	if (pad >= 0 && info.status[pad]) {
		ioPadGetData(pad, &data);
		ret = (data.button[1] & button);
	} else {
		u32 i;

		/* Check every pad */
		for (i = 0; i < MAX_PADS && !ret; i++) {
			if (info.status[i]) {
				ioPadGetData(i, &data);
				ret = (data.button[1] & button);
			}
		}
	}

	return ret;
}
#endif
