#include "FloorMillBehavior.h"
#include "GameObject.h"
#include "GameService.h"
#include <iostream>

void FloorMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	parent->position.z = -100;
}
