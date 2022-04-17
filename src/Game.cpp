#include "Game.h"
#include "Graphics.h"

Game::Game()
{
	_testMesh = new TestMesh("test1.bmp", 200, 200, 256, 256);
}

Game::~Game()
{
	delete _testMesh;
}

void Game::RenderPipline()
{
	Graphics::BeginRender();
	_testMesh->Render();
}

void Game::Update()
{

}