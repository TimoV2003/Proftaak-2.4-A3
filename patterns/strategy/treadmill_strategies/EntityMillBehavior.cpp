#include "GameObject.h"
#include "GameService.h"
#include <iostream>

// this include section is needed for the treadmill strategy
#include "../patterns/strategy/treadmill_strategies/Headers/EntityMillBehavior.h"

void EntityMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	parent->game->queueDelete(parent);
}
