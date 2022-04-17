#ifndef __Shader_H__
#define __Shader_H__
#include "MiniMobGL.h"
class Shader
{
public:
	Shader(const char* path);
	GLuint programObject;
	GLuint samplerLoc;
private:
	static GLuint LoadShader(GLenum type, const char *shaderSrc);
	static GLuint LoadProgram(char *vertShaderSrc, char *fragShaderSrc);
};
#endif