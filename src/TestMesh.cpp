#include "MiniMobGL.h"
#include "TestMesh.h"
#include "FileUtil.h"
#include <string.h>

TestMesh::TestMesh(const char* filename)
{
	_tex = 0;
	_width = 0;
	_height = 0;
	unsigned char* data = FileUtil::LoadFile(filename);
	memcpy(&_width, data + 18, 4);
	memcpy(&_height, data + 22, 4);
	BMPColorRB(data + 54, _width * _height * 3);

	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_2D, _tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, data + 54);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] data;
}

TestMesh::~TestMesh()
{
	if (_tex != 0)
		glDeleteTextures(1, &_tex);
}

// 红蓝色交换
void TestMesh::BMPColorRB(unsigned char* texData, int dataLen)
{
	unsigned char tmp;
	for (int i = 0; i < dataLen; i += 3)
	{
		tmp = texData[i];
		texData[i] = texData[i + 2];
		texData[i + 2] = tmp;
	}
}

static const unsigned char indices[] = 
{ 
	0, 2, 1, 
	1, 2, 3 
};
static const float texCoord[] = 
{ 
	0, 1, 
	1, 1, 
	0, 0, 
	1, 0
};
static const float vertexArray2[] =
{
	0, 0,
	256, 0,
	0, 256,
	256, 256,
};
static const float vertexArray[] =
{
	256, 256,
	512, 256,
	256, 512,
	512, 512,
};

void TestMesh::Render()
{
	glLoadIdentity();


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, _tex);
	glVertexPointer(2, GL_FLOAT, 0, vertexArray);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
}