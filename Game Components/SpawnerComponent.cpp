#include "SpawnerComponent.h"
#include "GameService.h"
#include "GameEntityFactory.h"
#include "TreeFactory.h"
#include "GameObject.h"

SpawnerComponent::SpawnerComponent(float initMinimumSpawndelay, float initMaximumSpawndelay) {
	this->treeFactory = std::make_shared<TreeFactory>();
	this->minimumSpawndelay = initMinimumSpawndelay;
	this->maximumSpawndelay = initMaximumSpawndelay;
}

void SpawnerComponent::update(float deltaTime)
{
	static float timeSinceLast = 0.0f;
	static float timeDelay;

	timeSinceLast += deltaTime;
	if (timeSinceLast < timeDelay) return;

	//called on a timer
	timeSinceLast = 0.0f;
	timeDelay = GameService::RandomValue(this->minimumSpawndelay, this->maximumSpawndelay);

	if (auto weakParent = getParent()) {
		

		//Never save this as a sharepointer in heap
		auto NewGameEntity = RandomEntityFromList();
		weakParent->game->instantiate(NewGameEntity);
	}
}

std::shared_ptr<GameObject> SpawnerComponent::RandomEntityFromList() {
	auto newEntity = treeFactory->CreateEntity();
	return newEntity;
}
