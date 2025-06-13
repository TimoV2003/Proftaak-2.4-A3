#include "EntityMillBehavior.h"
#include "GameObject.h"
#include "GameService.h"
#include <iostream>

void EntityMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	parent->game->queueDelete(parent);
}
