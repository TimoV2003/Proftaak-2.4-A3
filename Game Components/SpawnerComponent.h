#pragma once
#include "GameComponent.h"
#include <vector>

class GameEntityFactory;

class SpawnerComponent : public GameComponent
{
	float minimumSpawndelay;
	float maximumSpawndelay;
	bool spawnXlocationIsRandom;
	std::shared_ptr<GameEntityFactory> treeFactory;
public:
	SpawnerComponent(float minimumSpawndelay, float maximumSpawndelay);
	SpawnerComponent(float minimumSpawndelay, float maximumSpawndelay, bool randomizeSpawnXLocation);
	~SpawnerComponent() = default;

	virtual void update(float deltaTime) override;
	std::shared_ptr<GameObject> RandomEntityFromList();
};

