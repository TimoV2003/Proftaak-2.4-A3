#pragma once
#include "GameComponent.h"

class GameEntityFactory;

class SpawnerComponent : public GameComponent
{
	
	std::shared_ptr<GameEntityFactory> treeFactory;
public:
	SpawnerComponent();
	~SpawnerComponent() = default;

	virtual void update(float deltaTime) override;
	std::shared_ptr<GameObject> RandomEntityFromList();
};

