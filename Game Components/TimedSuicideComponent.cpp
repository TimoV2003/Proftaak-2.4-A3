#include "TimedSuicideComponent.h"
#include "GameService.h"
#include "HealthComponent.h"

void TimedSuicideComponent::update(float deltaTime)
{
	timer -= deltaTime;
	if (timer > 0) return;

	//called after timer runs out
	if (auto p = getParent()) {
		auto health = p->getComponent<HealthComponent>();
		if (health) {
			health->decreaseHealth();
		}
	}
}
