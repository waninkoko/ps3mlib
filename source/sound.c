/*
 * sound.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <lv2/spu.h>

#include "sound.h"
#include "spu.h"

/* Externs */
extern const char spu_soundmodule_bin[];


FILE *Sound_OpenMem(const void *buffer, u32 len)
{
	char *buf = (char *)buffer;

	/* Open sound buffer */
	return (FILE *)mem_open(buf, len);
}

void Sound_CloseMem(FILE *fp)
{
	long fd = (long)fp;

	/* Close sound file */
	mem_close(fd);
}

s32 Sound_Init(void)
{
	u32 spu;
	s32 ret;

	/* Initialize SPUs */
	ret = SPU_Init();
	if (ret)
		return ret;

	/* Load SPU module */
	ret = SPU_LoadELF(spu_soundmodule_bin, &spu);
	if (ret)
		return ret;

	/* Init sound */
	ret = SND_Init(spu);
	if (ret)
		return ret;

	/* Pause all voices */
	SND_Pause(0);

	return 0;
}

s32 Sound_Play(FILE *fp, s32 pos, s32 mode)
{
	/* Play audio file */
	return PlayAudiofd(fp, pos, mode);
}

void Sound_Stop(void)
{
	/* Stop audio playback */
	return StopAudio();
}

void Sound_Pause(bool pause)
{
	/* Pause audio playback */
	PauseAudio(pause);
}
