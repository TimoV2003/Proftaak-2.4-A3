#pragma once

#include "StartMenu.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLHelperFunctions.hpp"

using namespace std;

std::vector<tigl::Vertex> backgroundVerticies;
uint32_t backgroundVboId, BackgroundVaoId;

glm::vec2 currentMousePosition = glm::vec2(100.0f, 100.0f); // Default position, will be updated later



void StartMenu::init() {
	// Initialization code for the start menu

	backgroundVerticies = OpenGLHelpers::createRectangleVerticies(glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight));
	OpenGLHelpers::setupVAOAndVBO(backgroundVboId, BackgroundVaoId, backgroundVerticies.size() * sizeof(tigl::Vertex), GL_STATIC_DRAW, backgroundVerticies.data());

	this->textRenderer = new TextRenderer();
	this->textRenderer->initFont("times", "c:/windows/fonts/times.ttf");
	this->textRenderer->setActiveFont("times");
	this->textRenderer->setActiveColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec2 buttonPosition = calculateButtonPosition(200, 50); // Assuming button width is 200
	this->startbutton = new StartMenuButton(buttonPosition, glm::vec2(200, 50), this->window, this->textRenderer);
	this->startbutton->init();
}

void StartMenu::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Drawing code for the start menu
	// This could include rendering buttons, text, etc.
	tigl::shader->use();
	const glm::mat4 projectionMatrix = glm::ortho(0.0f, this->windowWidth, this->windowHeight, 0.0f, -100.0f, 100.0f);
	tigl::shader->setProjectionMatrix(projectionMatrix);
	tigl::shader->setViewMatrix(glm::mat4(1.0f));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(false);
	tigl::shader->enableLighting(false);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColorMult(true);
	tigl::shader->setColorMult(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(BackgroundVaoId);
	glDrawArrays(GL_QUADS, 0, backgroundVerticies.size());
	glBindVertexArray(0); // Unbind the VAO after drawing

	tigl::shader->setColorMult(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	this->startbutton->draw();

	tigl::shader->setColorMult(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	const std::vector<tigl::Vertex> mouse = OpenGLHelpers::createRectangleVerticies(currentMousePosition, glm::vec2(10, 10));
	tigl::drawVertices(GL_QUADS, mouse);

	this->textRenderer->draw();
}

void StartMenu::update() {
	this->startbutton->update();
	// Update code for the start menu
	// This could include checking for button clicks, updating animations, etc.
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		double mouseX, mouseY;
		glfwGetCursorPos(this->window, &mouseX, &mouseY);
		glm::vec4 mousePosition(mouseX, mouseY, 0.0f, 1.0f);

		glm::vec4 projectedMousePosition = mousePosition * glm::vec4(0.5);
		currentMousePosition = projectedMousePosition;
	}
}

void StartMenu::setCallbackOnButtonPress(std::function<void()> callback) {
	if (this->startbutton) {
		this->startbutton->setCallback(callback);
	}
}

glm::vec2 StartMenu::calculateButtonPosition(size_t buttonWith, size_t buttonHeight) {
	// Calculate the position for the button based on the window size
	return glm::vec2((this->windowWidth - buttonWith) / 2.0f, (this->windowHeight - buttonHeight) / 2.0f);
}

void StartMenu::setWindowSize(float width, float height) {
	this->windowWidth = width;
	this->windowHeight = height;
}

StartMenu::StartMenu(GLFWwindow* window)
{
	this->window = window;
}

StartMenu::~StartMenu() {
	delete this->textRenderer;
}