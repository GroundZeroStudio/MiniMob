#ifndef __TEST_MESH_H__
#define __TEST_MESH_H__
#include "MiniMobGL.h"
#include "Graphics/Shader.h"
class TestMesh
{
public:
	TestMesh(const char* filename, int x, int y, int width, int height);
	~TestMesh();
	void Render();
private:
	void LoadTexture(const char* filename);
	void CalcVertexPosition(float x, float y, float width, float height);
	void BMPColorRB(unsigned char* data, int dataLen);
	GLuint _tex;
	int _textureWidth;
	int _textureHeight;
	GLfloat _vertexArray[12];
	Shader * _shader;
};
#endif