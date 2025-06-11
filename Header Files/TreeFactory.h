#pragma once
#include "GameEntityFactory.h"
#include "EntityMillBehavior.h"
#include "FloorMillBehavior.h"

class TreeFactory : public GameEntityFactory
{
	float Spawndistance = -10.0f;

public:
	TreeFactory();
	~TreeFactory() = default;

	std::shared_ptr<GameObject> CreateEntity() override;
};

