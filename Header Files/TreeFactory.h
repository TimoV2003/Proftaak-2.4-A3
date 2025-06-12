#pragma once
#include "GameEntityFactory.h"
#include "EntityMillBehavior.h"
#include "FloorMillBehavior.h"
#include "MeshComponent.h"


class TreeFactory : public GameEntityFactory
{
	float Spawndistance = -10.0f;
	Model model;

public:
	TreeFactory();
	~TreeFactory() = default;

	std::shared_ptr<GameObject> CreateEntity() override;
};

