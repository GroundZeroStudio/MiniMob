#ifndef __TEST_MESH_H__
#define __TEST_MESH_H__
#include "MiniMobGL.h"
class TestMesh
{
public:
	TestMesh(const char* filename);
	~TestMesh();
	void Render();
private:
	void BMPColorRB(unsigned char* data, int dataLen);
	GLuint _tex;
	int _width;
	int _height;
};
#endif