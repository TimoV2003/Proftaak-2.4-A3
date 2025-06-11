#include "SpawnerComponent.h"
#include "GameService.h"


SpawnerComponent::SpawnerComponent() {
	treeFactory = std::make_shared<TreeFactory>();
}

int random() {
	return 5 - ((float)(rand()) / (float)(RAND_MAX)) * 10;
}

void SpawnerComponent::update(float deltaTime)
{
	static float timeSinceLast = 0.0f;
	timeSinceLast += deltaTime;
	if (timeSinceLast < 1.0f) return;

	//called on a timer
	timeSinceLast = 0.0f;
	if (auto p = getParent()) {
		auto NewGameEntity = RandomEntityFromList();
		p->game->instantiate(NewGameEntity);
	}
}

std::shared_ptr<GameObject> SpawnerComponent::RandomEntityFromList() {
	auto newEntity = treeFactory->CreateEntity();
	return newEntity;
}
