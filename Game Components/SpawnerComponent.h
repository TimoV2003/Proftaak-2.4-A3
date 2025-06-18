#pragma once
#include "GameComponent.h"

class GameEntityFactory;

class SpawnerComponent : public GameComponent
{
private:
	float minimumSpawndelay;
	float maximumSpawndelay;
	bool spawnXlocationIsRandom;
	std::shared_ptr<GameEntityFactory> treeFactory;
	std::shared_ptr<GameEntityFactory> floorFactory;
public:
	SpawnerComponent(float minimumSpawndelay, float maximumSpawndelay);
	SpawnerComponent(float minimumSpawndelay, float maximumSpawndelay, bool randomizeSpawnXLocation);
	~SpawnerComponent() = default;

	virtual void update(float deltaTime) override;
	std::shared_ptr<GameObject> RandomEntityFromList();
	std::shared_ptr<GameObject> selectItemFromLootTable();
};
