#include "HealthComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameService.h"
#include <tigl.h>
#include <stb_image.h>
using tigl::Vertex;

GLuint HealthComponent::heartTexture = 0;

HealthComponent::HealthComponent(short playerHealth, float invincibilityTime){
	this->health = playerHealth;
	this->invincibilityTime = invincibilityTime;
	this->timeSinceHealthReduction = 0.0f;
}

void HealthComponent::update(float deltaTime) {
	if (timeSinceHealthReduction < invincibilityTime) {
		timeSinceHealthReduction += deltaTime;
	}
}
void HealthComponent::decreaseHealth() {
	if (!(timeSinceHealthReduction > invincibilityTime))
		return;
	timeSinceHealthReduction = 0.0f;

	if (health > 0)
		health -= 1;
	if (health < 0) 
		health = 0;
	if (health == 0) {
		notifyDeath();
	}
}

void HealthComponent::notifyDeath() {
	if (auto p = getParent()) {
		if (p->game) {
			p->game->gameOver = true;
			p->game->queueDelete(p);
		}
	}
}

void HealthComponent::drawUI(int screenWidth, int screenHeight) const
{
	if (health <= 0 )
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

void HealthComponent::loadHeartTexture() {
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




