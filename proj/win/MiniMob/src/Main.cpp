#include <iostream>
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include "Game.h"
#include "Graphics.h"

GLFWwindow* CreateGameWindow(int width, int height)
{
	GLFWwindow* window;

	if (!glfwInit())
		return 0;
	window = glfwCreateWindow(width, height, "Mini Mob Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	return window;
}

int main()
{
	GLFWwindow* window = CreateGameWindow(1280, 720);
	Game* game = new Game();
	Graphics::InitGL(1280, 720);
	while (true)
	{
		glfwPollEvents();
		game->Update();
		game->RenderPipline();
		glfwSwapBuffers(window);
	}
	delete game;
	glfwTerminate();
	std::cin.get();
	return 0;
}
