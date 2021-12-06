#ifndef __GAME_H__
#define __GAME_H__
#include "TestMesh.h"
class Game
{
public:
	Game();
	~Game();
	void RenderPipline();
	void Update();
private:
	TestMesh* _testMesh;
};
#endif