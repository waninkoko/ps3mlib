/*
 * video.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <errno.h>

#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>

#include "video.h"

/* Video buffers */
static u32 *buffer[2] = { NULL };
static u32  offset[2] = { 0 };

/* Screen pitch */
static u32 pitch;

/* Current buffer */
static s32 current = -1;

/* Video context */
static gcmContextData *context = NULL;

/* Video resolution */
static VideoResolution res;


s32 Video_Init(void)
{
	VideoConfiguration vconfig;
	VideoState         state;

	void *hostAddr;
	s32   bufSize, ret;

	/* Allocate shared memory */
	hostAddr = memalign(1024*1024, 1024*1024);
	if (!hostAddr)
		return -ENOMEM;

	/* Initialize video context */
	context = realityInit(0x10000, 1024*1024, hostAddr); 
	if (!context)
		return -ENOMEM;

	/* Get video state */
	ret = videoGetState(0, 0, &state);
	if (ret || state.state)
		return -EINVAL;

	/* Get video resolution */
	ret = videoGetResolution(state.displayMode.resolution, &res);
	if (ret)
		return -EINVAL;

	/* Set screen pitch */
	pitch = res.width * 4;

	/* Set the framebuffer config (XRGB) */
	memset(&vconfig, 0, sizeof(vconfig));

	vconfig.resolution = state.displayMode.resolution;
	vconfig.format     = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch      = pitch;

	/* Configure video */
	ret = videoConfigure(0, &vconfig, NULL, 0);
	if (ret)
		return -EINVAL;

	/* Check video state */
	ret = videoGetState(0, 0, &state);
	if (ret)
		return -EINVAL;

	/* Enable v-sync */
	gcmSetFlipMode(GCM_FLIP_VSYNC);

	/* Set buffer size */
	bufSize = pitch * res.height;

	/* Allocate RSX buffers */
	buffer[0] = rsxMemAlign(16, bufSize);
	buffer[1] = rsxMemAlign(16, bufSize);

	if (!buffer[0] || !buffer[1])
		return -ENOMEM;

	realityAddressToOffset(buffer[0], &offset[0]);
	realityAddressToOffset(buffer[1], &offset[1]);

	/* Setup display buffers */
	gcmSetDisplayBuffer(0, offset[0], pitch, res.width, res.height);
	gcmSetDisplayBuffer(1, offset[1], pitch, res.width, res.height);

	/* Reset flip status */
	gcmResetFlipStatus();

	/* Set initial buffer */
	current = 1;

	/* Flip buffers */
	Video_Flip();

	return 0;
}

inline u32 *Video_GetBuffer(void)
{
	/* No buffer */
	if (current < 0)
		return NULL;

	/* Return current buffer */
	return buffer[current];
}

inline s32 Video_GetWidth(void)
{
	/* Return resolution width */
	return res.width;
}

inline s32 Video_GetHeight(void)
{
	/* Return resolution height */
	return res.height;
}

void Video_Clear(u32 color)
{
	u32 *screen;
	s32  i, j;

	/* Select buffer */
	screen = Video_GetBuffer();
	if (!screen)
		return;

	/* Fill buffer with color */
	for (i = 0; i < res.height; i++)
	for (j = 0; j < res.width;  j++)
		screen[i * res.width + j] = color;
}

void Video_Flip(void)
{
	/* No buffer */
	if (current < 0)
		return;

	/* Set flip buffers */
	gcmSetFlip(context, current);

	/* Flush buffer */
	realityFlushBuffer(context);

	/* Set to wait for the flip to finish */
	gcmSetWaitFlip(context);

	/* Toggle buffer */
	current = !current;
}

void Video_WaitFlip() 
{
	/* Wait until the flip operation is done */
	while(gcmGetFlipStatus())
		usleep(200);

	gcmResetFlipStatus();
}
