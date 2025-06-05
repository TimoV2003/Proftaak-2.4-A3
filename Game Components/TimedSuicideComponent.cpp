#include "TimedSuicideComponent.h"
#include "GameService.h"

void TimedSuicideComponent::update(float deltaTime)
{
	timer -= deltaTime;
	if (timer > 0) return;

	//called after timer runs out
	if (auto p = getParent()) {
		p->game->queueDelete(p);
	}
}
