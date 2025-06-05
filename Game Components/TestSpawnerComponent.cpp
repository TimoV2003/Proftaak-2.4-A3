#include "TestSpawnerComponent.h"
#include "MeshComponent.h"
#include "GameService.h"
#include "TimedSuicideComponent.h"
#include "IEndOfMillBehavior.h"
#include "EnemyMillBehavior.h"
#include "TreadmillComponent.h"

int random() {
	return 5 - ((float)(rand()) / (float)(RAND_MAX)) * 10;
}

void TestSpawnerComponent::update(float deltaTime)
{
	std::shared_ptr<IEndOfMillBehavior> keyboardInput;
	keyboardInput = std::make_shared<EnemyMillBehavior>();

	static float timeSinceLast = 0.0f;
	timeSinceLast += deltaTime;
	if (timeSinceLast < 1.0f) return;

	//called on a timer
	timeSinceLast = 0.0f;
	if (auto p = getParent()) {
		auto tree = std::make_shared<GameObject>("tree");
		tree->position = glm::vec3(random(), 0, random());
		tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
		tree->addComponent(std::make_shared<MeshComponent>(model));
		tree->addComponent(std::make_shared<TreadmillComponent>(keyboardInput));
		//tree->addComponent(std::make_shared<TimedSuicideComponent>(1.0f));
		p->game->instantiate(tree);
	}
}