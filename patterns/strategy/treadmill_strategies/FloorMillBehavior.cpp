#include "GameObject.h"
#include "GameService.h"
#include <iostream>
#include <math.h>

// this include section is needed for the treadmill strategy
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

void FloorMillBehavior::ReachedEndOfMill(std::shared_ptr<GameObject> parent)
{
	parent->position.z = -300 + fmod(parent->position.z, 300.0f);
}
