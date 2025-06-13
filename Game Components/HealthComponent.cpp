#include "HealthComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameService.h"
#include <tigl.h>
using tigl::Vertex;

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

	std::cout << "decreaseHealth called" << std::endl;

	health -= 1;
	if (health <= 0) {
		notifyDeath();
	}
}

void HealthComponent::notifyDeath() {
	if (auto p = getParent()) {
		if (p->game) {
			p->game->gameOver = true;
		}
	}
	//TODO notify something that health is 0
}

void HealthComponent::drawUI(int screenWidth, int screenHeight) const
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, screenHeight, 0, -1, 1); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 

	for (int i = 0; i < health; ++i) {
		float x = 20 + i * 50;
		float y = 20;
		float size = 40;

		glVertex2f(x, y);
		glVertex2f(x + size, y);
		glVertex2f(x + size, y + size);
		glVertex2f(x, y + size);
	}
	glEnd();

	glEnable(GL_DEPTH_TEST);
}

