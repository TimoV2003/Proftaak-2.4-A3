#include "EnemyMillBehavior.h"
#include "GameObject.h"
#include "GameService.h"
#include <iostream>

void EnemyMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	parent->game->queueDelete(parent);
}
