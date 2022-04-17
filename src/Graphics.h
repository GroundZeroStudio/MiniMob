#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include "MiniMobGL.h"
class Graphics
{
public:
	static void InitGL(int width, int height);
	static void BeginRender();
	static float ScrWidth();
	static float ScrHeight();
private:
	static int _width;
	static int _height;
};
#endif