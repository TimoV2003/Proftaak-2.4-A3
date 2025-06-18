#include "SpawnerComponent.h"
#include "GameService.h"
#include "GameObject.h"
#include "DistanceScoreComponent.h"
#include "ScoreStrategy.h"

// this include section is needed for the factory method pattern
#include "../patterns/factory_method/Interfaces/GameEntityFactory.h"
#include "../patterns/factory_method/entity_factories/Headers/TreeFactory.h"
#include "../patterns/factory_method/entity_factories/Headers/FloorFactory.h"


SpawnerComponent::SpawnerComponent(float initMinimumSpawndelay, float initMaximumSpawndelay) : 
	minimumSpawndelay(initMinimumSpawndelay), initialMaximumSpawnDelay(initMaximumSpawndelay) {
	this->treeFactory = std::make_shared<TreeFactory>();
	this->floorFactory = std::make_shared<FloorFactory>();
	this->spawnXlocationIsRandom = true;
	maximumSpawndelay = initialMaximumSpawnDelay;
}

SpawnerComponent::SpawnerComponent(float initMinimumSpawndelay,float initMaximumSpawndelay,bool randomizeSpawnXLocation) : 
	minimumSpawndelay(initMinimumSpawndelay), initialMaximumSpawnDelay(initMaximumSpawndelay), spawnXlocationIsRandom(randomizeSpawnXLocation){
	this->treeFactory = std::make_shared<TreeFactory>();
	maximumSpawndelay = initialMaximumSpawnDelay;
}

void SpawnerComponent::update(float deltaTime)
{
	static float timeSinceLast = 0.0f;
	static float timeDelay;
	float entityXPosition;

	timeSinceLast += deltaTime;
	if (timeSinceLast < timeDelay) return;

	//reset the timer
	timeSinceLast = 0.0f;
	maximumSpawndelay = newMaximumSpawnDelay();
	timeDelay = GameService::RandomValue(this->minimumSpawndelay, this->maximumSpawndelay);

	
	if (auto weakParent = getParent()) {

		//sets spawn X location based
		if (spawnXlocationIsRandom) {
			entityXPosition = GameService::RandomValue(-10.0f, 10.0f);
		}
		else {
			entityXPosition = weakParent->position.x;
		}


		//Never save this as a sharepointer in heap
		auto NewGameEntity = RandomEntityFromList();
		NewGameEntity->position = glm::vec3(entityXPosition, 0, weakParent->position.z);
		weakParent->game->instantiate(NewGameEntity);
	}
}

std::shared_ptr<GameObject> SpawnerComponent::RandomEntityFromList() {
	auto newEntity = selectItemFromLootTable();
	
	return newEntity;
}


std::shared_ptr<GameObject> SpawnerComponent::selectItemFromLootTable() {
	int randomGeneratedValue = GameService::RandomValue(0, 10);

	switch (randomGeneratedValue)
	{
	default:
		return treeFactory->CreateEntity();
	}
}
float SpawnerComponent::newMaximumSpawnDelay() {
	auto player = GameService::getGameObject("blocky");
	auto scoreComponent = player ? player->getComponent<DistanceScoreComponent>() : nullptr;
	float points = scoreComponent->getScoreHolder()->getScore();
	return (initialMaximumSpawnDelay-minimumSpawndelay) * pow(2.718,(-0.01 * points)) + minimumSpawndelay;
}

