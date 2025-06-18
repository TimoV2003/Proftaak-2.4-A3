#include "HealthUI.h"
#include "HealthComponent.h"
#include <tigl.h>
#include <stb_image.h>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
using tigl::Vertex;

GLuint heartTexture;
void loadHeartTexture();
int screenWidth, screenHeight;


HealthUI::HealthUI(std::shared_ptr<HealthComponent> healthComponent, GLFWwindow* window) : healthComponent(healthComponent), window(window)
{
	glfwGetWindowSize(window, &screenWidth, &screenHeight);
}

void HealthUI::draw()
{
	tigl::shader->setProjectionMatrix(glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f));

	tigl::shader->setViewMatrix(glm::mat4(1.0f));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableColor(true);

	int health = this->healthComponent->getHealth();
	if (health <= 0)
		return;
	if (heartTexture == 0)
		loadHeartTexture();

	glUseProgram(0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, heartTexture);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, screenHeight, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float size = 48.0f;
	float spacing = 70.0f;
	float totalWidth = health * size + (health - 1) * (spacing - size);
	
	float startX = (screenWidth - totalWidth) / 2.0f;
	float y = 24.0f;

	for (int i = 0; i < health; ++i) {
		float x = startX + i * spacing;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x + size, y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x + size, y + size);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + size);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void loadHeartTexture() {
	if (heartTexture != 0)
		return;
	int width, height, channels;
	unsigned char* data = stbi_load("Resource Files/UI/heart.png", &width, &height, &channels, 4);

	if (data) {
		glGenTextures(1, &heartTexture);
		glBindTexture(GL_TEXTURE_2D, heartTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL error after texture upload: " << err << std::endl;
	}
}