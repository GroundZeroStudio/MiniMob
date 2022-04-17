#include "MiniMobGL.h"
#include "TestMesh.h"
#include "FileUtil.h"
#include "Graphics.h"
#include <string.h>

TestMesh::TestMesh(const char* filename, int x, int y, int width, int height)
{
	_shader = new Shader("shader/diffuse");
	_tex = 0;
	_textureWidth = 0;
	_textureHeight = 0;
	LoadTexture(filename);
	CalcVertexPosition(x, y, width, height);
}

void TestMesh::CalcVertexPosition(float x, float y, float width, float height)
{
	float scrWidth = Graphics::ScrWidth();
	float scrHeight = Graphics::ScrHeight();
	float vx = -1 + x / scrWidth;
	float vwidth = width / scrWidth * 2;
	float vheight = height / scrHeight * 2;
	float vy = 1 - y / scrHeight - vheight;

	_vertexArray[0] = vx;
	_vertexArray[1] = vy;
	_vertexArray[2] = 0;

	_vertexArray[3] = vx;
	_vertexArray[4] = vy + vheight;
	_vertexArray[5] = 0;

	_vertexArray[6] = vx + vwidth;
	_vertexArray[7] = vy + vheight;
	_vertexArray[8] = 0;

	_vertexArray[9] = vx + vwidth;
	_vertexArray[10] = vy;
	_vertexArray[11] = 0;
}

void TestMesh::LoadTexture(const char* filename)
{
	unsigned char* data = FileUtil::LoadFile(filename);
	memcpy(&_textureWidth, data + 18, 4);
	memcpy(&_textureHeight, data + 22, 4);
	BMPColorRB(data + 54, _textureWidth * _textureHeight * 3);
	
	// Generate a texture object
	glGenTextures(1, &_tex);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, _tex);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureWidth, _textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data + 54);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	delete[] data;
}

TestMesh::~TestMesh()
{
	if (_tex != 0)
		glDeleteTextures(1, &_tex);
	delete _shader;
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

GLfloat texcoordArray[] = {
						 0.0f,  0.0f,        // TexCoord 0 
						 0.0f,  1.0f,        // TexCoord 1
						 1.0f,  1.0f,        // TexCoord 2
						 1.0f,  0.0f         // TexCoord 3
};
GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

void TestMesh::Render()
{
	// Use the program object
	glUseProgram(_shader->programObject);

	// Load the vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, _vertexArray);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texcoordArray);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);

	// Set the sampler texture unit to 0
	glUniform1i(_shader->samplerLoc, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}