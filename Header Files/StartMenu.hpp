#pragma once

#include <GL/glew.h>
#include "tigl.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <functional>

#include "StartMenuButton.hpp"
#include "TextRenderer.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

class StartMenu {
private:
	float windowHeight = 400.0f; // Default window height, can be set dynamically
	float windowWidth = 700.0f; // Default window width, can be set dynamically

	StartMenuButton* startbutton;
	TextRenderer* textRenderer;
	GLFWwindow* window = nullptr;

	glm::vec2 calculateButtonPosition(size_t buttonWith, size_t buttonHeight);
public:
	StartMenu(GLFWwindow* window);
	~StartMenu();

	void init();
	void draw();
	void update();
	void setCallbackOnButtonPress(std::function<void()> callback);
	//void handleInput(GLFWwindow* window);

	void setWindowSize(float width, float height);

};