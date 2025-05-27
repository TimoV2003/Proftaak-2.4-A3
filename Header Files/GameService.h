#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GameService
{
private:
	GLFWwindow* window;
public:

	GameService(GLFWwindow* window) : window(window) {}
	~GameService() = default;

	void init();
	void update();
	void draw();
};

