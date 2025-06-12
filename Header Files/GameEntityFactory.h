#pragma once
#include <memory>
#include "IEndOfMillBehavior.h"
#include "TreadmillComponent.h"



class GameEntityFactory
{

protected:
	std::shared_ptr<IEndOfMillBehavior> endOfMillbehavior;
public:
	GameEntityFactory() = default;
	~GameEntityFactory() = default;


	virtual std::shared_ptr<GameObject> CreateEntity() = 0;
};

