#include "SpawnerComponent.h"
#include "GameService.h"


SpawnerComponent::SpawnerComponent() {
	this->treeFactory = std::make_shared<TreeFactory>();
}

void SpawnerComponent::update(float deltaTime)
{
	static float timeSinceLast = 0.0f;
	static float timeDelay;

	timeSinceLast += deltaTime;
	if (timeSinceLast < timeDelay) return;

	//called on a timer
	timeSinceLast = 0.0f;
	timeDelay = GameService::RandomValue(1.0f, 10.0f);

	if (auto p = getParent()) {
		//Never save this as a sharepointer in heap
		auto NewGameEntity = RandomEntityFromList();
		p->game->instantiate(NewGameEntity);
	}
}

std::shared_ptr<GameObject> SpawnerComponent::RandomEntityFromList() {
	auto newEntity = treeFactory->CreateEntity();
	return newEntity;
}
