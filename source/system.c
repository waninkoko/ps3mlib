/*
 * system.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <stdlib.h>

#include <lv2/process.h>
#include <psl1ght/lv2.h>
#include <sysutil/events.h>


static void __System_EventHandler(u64 status, u64 param, void *usrdata)
{
	/* Check status */
	switch (status) {
	case EVENT_REQUEST_EXITAPP:
		sysProcessExit(1);
	}
}

static void __System_Cleanup(void)
{
	/* Unregister event handler */
	sysUnregisterCallback(EVENT_SLOT0);
}


s32 System_Init(void)
{
	s32 ret;

	/* Register exit handler */
	ret = atexit(__System_Cleanup);
	if (ret)
		return ret;

	/* Register event handler */
	return sysRegisterCallback(EVENT_SLOT0, __System_EventHandler, NULL);
}

