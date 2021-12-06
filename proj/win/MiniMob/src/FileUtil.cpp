#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FileUtil.h"

unsigned char* FileUtil::LoadFile(const char* filename)
{
	int filename_len = strlen(filename);
	char* fullpath = new char[5 + filename_len];
	fullpath[0] = 'r';
	fullpath[1] = 'e';
	fullpath[2] = 's';
	fullpath[3] = '/';
	memcpy(fullpath + 4, filename, filename_len);
	fullpath[filename_len + 4] = 0;
	FILE* f = fopen(fullpath, "r");
	delete[] fullpath;
	if (!f)
		return 0;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);
	unsigned char* data = new unsigned char[size];
	fread(data, 1, size, f);
	fclose(f);
	return data;
}