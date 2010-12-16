/*
 * camera.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <errno.h>

#include <io/cam.h>
#include <sysmodule/sysmodule.h>

#include "camera.h"
#include "image.h"

/* Camera info */
static CameraInfoEx info = { 0 };
static CameraType   type = 0;

/* Memory container */
static mem_container_t container = 0;


s32 Camera_Init(void)
{
	s32 ret;

	/* Load camera module */
	ret = SysLoadModule(SYSMODULE_CAM);
	if (ret)
		return ret;

	/* Initialize camera */
	return cameraInit();
}

void Camera_Quit(void)
{
	/* Quit camera */
	cameraEnd();
}

s32 Camera_Connect(void)
{
	s32 ret;

	/* Allocate container */
	if (!container)
		lv2MemContinerCreate(&container, 0x200000);

	/* Get camera type */
	ret = cameraGetType(0, &type);
	if (ret)
		return ret;

	/* Playstation Eye */
	if (type == CAM_TYPE_PLAYSTATION_EYE) {
		/* Set camera info */
		info.format     = CAM_FORM_YUV422;
		info.framerate  = 30;
		info.resolution = CAM_RESO_VGA;
		info.info_ver   = 0x101;
		info.container  = container;

		/* Open camera */
		ret = cameraOpenEx(0, &info);
	} else {
		/* No device */
		ret = -ENOENT;
	}

	return ret;
}

void Camera_Disconnect(void)
{
	/* Stop camera */
	cameraStop(0);

	/* Close camera */
	cameraClose(0);

	/* Destroy container */
	if (container)
		lv2MemContinerDestroy(container);

	/* Reset variables */
	container = 0;
}

void Camera_Reset(void)
{
	/* Reset camera */
	cameraReset(0);
	cameraStart(0);
}

inline bool Camera_IsOpen(void)
{
	/* Check if camera is open */
	return cameraIsOpen(0);
}

inline bool Camera_IsAvailable(void)
{
	/* Check if camera is available */
	return cameraIsAvailable(0);
}

inline void *Camera_GetBuffer(void)
{
	/* Return camera buffer */
	return (void *)(u64)info.buffer;
}

inline s32 Camera_GetWidth(void)
{
	/* Return camera width */
	return info.width;
}

inline s32 Camera_GetHeight(void)
{
	/* Return camera height */
	return info.height;
}

s32 Camera_Read(void)
{
	s32 cnt, frame;
	s32 ret;

	/* Read camera frame */
	ret = cameraRead(0, &frame, &cnt);

	/* Check result */
	switch (ret) {
	case CAMERA_ERRO_NEED_START:
		/* Reset camera */
		Camera_Reset();
		break;
	}

	/* No frame read */
	if (!cnt)
		return -ENOENT;

	return ret;
}

s32 Camera_Draw(s32 x, s32 y)
{
	u32 *buffer;
	s32 ret;

	/* Check if camera is open */
	ret = Camera_IsOpen();
	if (!ret) {
		/* Connect camera */
		ret = Camera_Connect();
		if (ret)
			return ret;
	}

	/* Read camera frame */
	ret = Camera_Read();
	if (ret)
		return ret;

	/* Get camera buffer */
	buffer = Camera_GetBuffer();
	if (!buffer)
		return -ENOENT;

	/* Draw YUV frame */
	return Image_DrawYUV(buffer, info.width, info.height, x, y);
}
