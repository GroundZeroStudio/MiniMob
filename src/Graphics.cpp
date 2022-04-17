#include "MiniMobGL.h"
#include "Graphics.h"
#include <stdio.h>

int Graphics::_width = 0;
int Graphics::_height = 0;

void Graphics::InitGL(int width, int height)
{
	_width = width;
	_height = height;
}

void Graphics::BeginRender()
{
	glViewport(0, 0, _width, _height);						// Reset The Current Viewport
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
}

float Graphics::ScrWidth()
{
	return _width;
}

float Graphics::ScrHeight()
{
	return _height;
}