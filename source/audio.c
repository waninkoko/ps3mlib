/*
 * audio.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <errno.h>

#include <audio/audio.h>

/* Audio port */
static u32 portNum = 0;


s32 Audio_Init(u32 channels)
{
	AudioPortParam params;

	s32 ret;

	/* Initialize audio */
	ret = audioInit();
	if (ret)
		return -EINVAL;

	/* Configure audio */
	params.numChannels = channels;
	params.numBlocks   = AUDIO_BLOCK_8;
	params.attr  = 0;
	params.level = 1;

	/* Open audio port */
	ret = audioPortOpen(&params, &portNum);
	if (ret)
		return -EINVAL;

	/* Start audio port */
	return audioPortStart(portNum);
}

void Audio_Quit(void)
{
	/* No port open */
	if (!portNum)
		return;

	/* Close audio port */
	audioPortStop(portNum);
	audioPortClose(portNum);

	/* Quit audio */
	audioQuit();
}

u32 Audio_GetPort(void)
{
	/* Return port number */
	return portNum;
}
