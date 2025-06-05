#include "FloorMillBehavior.h"
#include "GameObject.h"
#include "GameService.h"
#include <iostream>

void FloorMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	if (taggedEnd) return;
	std::cout << "Enemy has reached the end of the mill!" << std::endl;
	parent->position.z = -100;
	taggedEnd = true;
}
