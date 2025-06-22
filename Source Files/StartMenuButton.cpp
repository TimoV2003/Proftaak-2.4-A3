#pragma once

#include "StartMenuButton.hpp"
#include "OpenGLHelperFunctions.hpp"

void StartMenuButton::init() {
	this->verticies = OpenGLHelpers::createRectangleVerticies(this->position, this->size, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Button size is 200x50
	OpenGLHelpers::setupVAOAndVBO(this->VboId, this->VaoId, this->verticies.size() * sizeof(tigl::Vertex), GL_STATIC_DRAW, this->verticies.data());

	this->textFrameId = this->textRenderer->createTextFrame(10);
}

void StartMenuButton::draw() {
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableColor(false);

	glBindVertexArray(this->VaoId);
	glDrawArrays(GL_QUADS, 0, this->verticies.size());
	glBindVertexArray(0); // Unbind the button VAO after drawing

	glm::vec2 textPosition = this->position * glm::vec2(2) + this->size * glm::vec2(0.4, 1.2);
	this->textRenderer->writeText(this->textFrameId, "Start Game", 40, textPosition);
}

void StartMenuButton::update() {
	// Update code for the start menu
	// This could include checking for button clicks, updating animations, etc.
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		glm::vec4 mousePosition(mouseX, mouseY, 0.0f, 1.0f);

		glm::vec4 projectedMousePosition = mousePosition * glm::vec4(0.5); //mapping mouse position from mouse space to our space

		glm::vec2 buttonBottomRight(this->position.x + this->size.x, this->position.y + this->size.y);

		bool isMousexGreaterThanButtonX = (projectedMousePosition.x >= this->position.x);
		bool isMousexLessThanButtonXPlusWidth = (projectedMousePosition.x <= buttonBottomRight.x);
		bool isMouseyGreaterThanButtonY = (projectedMousePosition.y >= this->position.y);
		bool isMouseyLessThanButtonYPlusHeight = (projectedMousePosition.y <= buttonBottomRight.y);

		if (isMousexGreaterThanButtonX && isMousexLessThanButtonXPlusWidth &&
			isMouseyGreaterThanButtonY && isMouseyLessThanButtonYPlusHeight) {
			onButtonPressHandler(true);
		}
	}
	else {
		onButtonPressHandler(false);
	}
}

void StartMenuButton::onButtonPressHandler(bool input)
{
	if (input && !this->isPressed) {
		this->isPressed = true;

		if (this->callback) {
			this->callback();
		}
	}
	else if (!input && this->isPressed) {
		this->isPressed = false;
	}
}

void StartMenuButton::setCallback(std::function<void()> callback) {
	this->callback = callback;
}

void StartMenuButton::setPosition(glm::vec2 position) {
	this->position = position;
}

void StartMenuButton::setSize(glm::vec2 size) {
	this->size = size;
}


StartMenuButton::StartMenuButton(glm::vec2 position, glm::vec2 size, GLFWwindow* window, TextRenderer* textRenderer) {
	this->position = position;
	this->size = size;
	this->window = window;
	this->textRenderer = textRenderer;
}