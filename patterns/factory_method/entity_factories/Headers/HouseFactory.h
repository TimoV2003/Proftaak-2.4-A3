#pragma once
#include "MeshComponent.h"

// this include section is needed for the factory method pattern
#include "../patterns/factory_method/Interfaces/GameEntityFactory.h"


class HouseFactory : public GameEntityFactory
{
	Model model;
public:
	HouseFactory();
	~HouseFactory() = default;

	std::shared_ptr<GameObject> CreateEntity() override;
};

