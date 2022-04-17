#include <iostream>
#include <windows.h>
#include "Game.h"
#include "Graphics.h"
#include "EGLUtil.h"

Game* game;

void GameUpdate()
{
	game->Update();
}

void RenderPipline()
{
	game->RenderPipline();
}

int main()
{
	EGLUtil * eglUtil = new EGLUtil(RenderPipline, GameUpdate);
	eglUtil->CreateEGLWindow("Mini Mob", 1280, 720);
	Graphics::InitGL(1280, 720);
	game = new Game();

	eglUtil->WindLoop();
	
	delete game;
	delete eglUtil;
	return 0;
}
