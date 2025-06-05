#include "EnemyMillBehavior.h"
#include "GameObject.h"
#include "GameService.h"
#include <iostream>

void EnemyMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	if (taggedEnd) return; 

	parent->game->queueDelete(parent);

	std::cout << "Enemy has reached the end of the mill!" << std::endl;
	taggedEnd = true;
}
