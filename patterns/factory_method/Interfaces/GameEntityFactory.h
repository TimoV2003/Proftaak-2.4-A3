#pragma once
#include <memory>

// this include section is needed for the treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"
#include "TreadmillComponent.h"



class GameEntityFactory
{

protected:
	std::shared_ptr<IEndOfMillBehavior> endOfMillbehavior;
	float modelScaleX;
	float modelScaleY;
	float modelScaleZ;
	float modelScaleUniform;
public:
	GameEntityFactory() = default;
	~GameEntityFactory() = default;


	virtual std::shared_ptr<GameObject> CreateEntity() = 0;


};

