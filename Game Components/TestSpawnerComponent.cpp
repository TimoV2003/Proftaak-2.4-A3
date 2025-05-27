#include "TestSpawnerComponent.h"
#include "MeshComponent.h"
#include "GameService.h"
#include "TimedSuicideComponent.h"

int random() {
	return 5 - ((float)(rand()) / (float)(RAND_MAX)) * 10;
}

void TestSpawnerComponent::update(float deltaTime)
{
	static float timeSinceLast = 0.0f;
	timeSinceLast += deltaTime;
	if (timeSinceLast < 0.2f) return;

	//called on a timer
	timeSinceLast = 0.0f;
	if (auto p = getParent()) {
		auto tree = std::make_shared<GameObject>("tree");
		tree->position = glm::vec3(random(), 0, random());
		tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
		tree->addComponent(std::make_shared<MeshComponent>(model));
		tree->addComponent(std::make_shared<TimedSuicideComponent>(1.0f));
		p->game->instantiate(tree);
	}
}