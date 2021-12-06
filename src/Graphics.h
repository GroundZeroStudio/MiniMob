#ifndef __GRAPHICS_2D_H__
#define __GRAPHICS_2D_H__
class Graphics
{
public:
	static void InitGL(int width, int height);
	static void BeginRender();
	static void DrawTriangle();
};
#endif