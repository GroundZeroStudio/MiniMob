#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__
class FileUtil
{
public:
	static unsigned char* LoadFile(const char* filename);
	static char* LoadFileString(const char* filename);
};
#endif