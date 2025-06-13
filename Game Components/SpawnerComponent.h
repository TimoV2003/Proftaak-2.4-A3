#pragma once
#include "GameComponent.h"
#include <vector>

class GameEntityFactory;

class SpawnerComponent : public GameComponent
{
	float minimumSpawndelay;
	float maximumSpawndelay;
	bool randomizeSpawnXLocation = true;
	std::shared_ptr<GameEntityFactory> treeFactory;
public:
	SpawnerComponent(float minimumSpawndelay, float maximumSpawndelay);
	~SpawnerComponent() = default;

	virtual void update(float deltaTime) override;
	std::shared_ptr<GameObject> RandomEntityFromList();
};

