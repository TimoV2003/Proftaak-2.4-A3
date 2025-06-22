#pragma once
#include <GL/glew.h>
#include "tigl.h"
#include <GLFW/glfw3.h>
#include <functional>

#include "TextRenderer.h"

class StartMenuButton {

private:
	std::vector<tigl::Vertex> verticies;
	uint32_t VboId = 0, VaoId = 0;
	uint32_t textFrameId = 0;
	bool isPressed = false;
	std::function<void()> callback;
	GLFWwindow* window = nullptr;
	TextRenderer* textRenderer;

	glm::vec2 position;
	glm::vec2 size;
public:

	StartMenuButton(glm::vec2 position, glm::vec2 size, GLFWwindow* window, TextRenderer* textRenderer);
	~StartMenuButton() = default;

	void init();
	void draw();
	void update();

	void onButtonPressHandler(bool input);

	void setCallback(std::function<void()> callback);
	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);
};