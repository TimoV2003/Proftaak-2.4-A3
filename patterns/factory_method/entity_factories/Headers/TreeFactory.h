#pragma once
#include "../patterns/factory_method/Interfaces/GameEntityFactory.h"
#include "MeshComponent.h"

class TreeFactory : public GameEntityFactory
{
	Model model;

public:
	TreeFactory();
	~TreeFactory() = default;

	std::shared_ptr<GameObject> CreateEntity() override;
};

