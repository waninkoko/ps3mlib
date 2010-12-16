/*
 * fs.c -- ps3mlib
 *
 * Copyright (C) Miguel Boton (Waninkoko)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#include <stdio.h>
#include <sys/stat.h>

#include <psl1ght/lv2/filesystem.h>

#include "types.h"

/* Constants */
#define BLOCK_SIZE	0x1000


s32 Fs_MakeDir(const char *path)
{
	/* Create directory */
	return lv2FsMkdir(path, S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR);
}

s32 Fs_CopyFile(const char *source, const char *dest)
{
	Lv2FsFile src = -1, dst = -1;
	Lv2FsStat stats;

	char buffer[BLOCK_SIZE];
	u64  i;
	s32  ret;

	/* Open source file */
	ret = lv2FsOpen(source, LV2_O_RDONLY, &src, 0, NULL, 0);
	if (ret)
		goto out;

	/* Open destination file */
	ret = lv2FsOpen(dest, LV2_O_WRONLY | LV2_O_CREAT | LV2_O_TRUNC, &dst, 0, NULL, 0);
	if (ret)
		goto out;

	/* Set permissions */
	lv2FsChmod(dest, S_IFMT | 0777);

	/* Get file stats */
	lv2FsFstat(src, &stats);

	/* Copy loop */
	for (i = 0; i < stats.st_size;) {
		u64 pos, read, written;

		/* Seek */
		lv2FsLSeek64(src, i, 0, &pos);
		lv2FsLSeek64(dst, i, 0, &pos);

		/* Read block */
		ret = lv2FsRead(src, buffer, sizeof(buffer), &read);
		if (ret || !read)
			break;

		/* Write block */
		ret = lv2FsWrite(dst, buffer, read, &written);
		if (ret || !written)
			break;

		/* Update counter */
		i += written;
	}

out:
	/* Close files */
	if (src >= 0) lv2FsClose(src);
	if (dst >= 0) lv2FsClose(dst);

	return ret;
}

s32 Fs_CopyDir(const char *source, const char *dest)
{
	Lv2FsFile   fd;
	Lv2FsDirent entry;

	s32 ret;

	/* Open directory */
	ret = lv2FsOpenDir(source, &fd);
	if (ret)
		return ret;

	/* Read directory */
	while (1) {
		char src[MAXPATHLEN + 1];
		char dst[MAXPATHLEN + 1];

		u64 read;

		/* Read entry */
		ret = lv2FsReadDir(fd, &entry, &read);
		if (ret || !read)
			break;

		/* Ignore dot entries */
		if (entry.d_name[0] == '.')
			continue;

		/* Generate paths */
		snprintf(src, sizeof(src), "%s/%s", source, entry.d_name);
		snprintf(dst, sizeof(dst), "%s/%s", dest,   entry.d_name);

		/* Copy entry */
		if (entry.d_type == 1) {
			/* Create folder */
			Fs_MakeDir(dst);

			/* Copy folder */
			ret = Fs_CopyDir(src, dst);
		} else {
			/* Copy file */
			ret = Fs_CopyFile(src, dst);
		}

		/* Copy error */
		if (ret)
			break;
	}

	/* Close directory */
	lv2FsCloseDir(fd);

	return ret;
}
