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

	// This is for testing, remove this before merging
	autoDamageTimer += deltaTime;
	if (autoDamageTimer >= autoDamageInterval) {
		autoDamageTimer = 0.0f;
		decreaseHealth();
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
	// TODO: Notify other components or systems about the death event
}

void HealthComponent::drawUI(int screenWidth, int screenHeight) const
{
	if (health <= 0 )
		return;

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

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 

	glBegin(GL_QUADS);
	for (int i = 0; i < health; ++i) {
		float x = startX + i * spacing;
		glVertex2f(x, y);
		glVertex2f(x + size, y);
		glVertex2f(x + size, y + size);
		glVertex2f(x, y + size);
	}
	glEnd();

	glEnable(GL_DEPTH_TEST);
}



