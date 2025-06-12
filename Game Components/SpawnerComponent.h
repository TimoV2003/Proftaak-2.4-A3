#pragma once
#include "GameComponent.h"
#include "GameEntityFactory.h"
#include "TreeFactory.h"
#include "GameObject.h"

class SpawnerComponent : public GameComponent
{
	
	std::shared_ptr<GameEntityFactory> treeFactory;
public:
	SpawnerComponent();
	~SpawnerComponent() = default;

	virtual void update(float deltaTime) override;
	std::shared_ptr<GameObject> RandomEntityFromList();
};

