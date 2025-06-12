#include "TreeFactory.h"
#include "GameService.h"

TreeFactory::TreeFactory() {
	endOfMillbehavior = std::make_shared<EntityMillBehavior>();
	ModelLoader::load("Resource Files/Tree/Tree_2.obj", model);
}

std::shared_ptr<GameObject> TreeFactory::CreateEntity() {
	float randomXPosition = GameService::RandomValue(-10.0f, 10.0f);


	auto tree = std::make_shared<GameObject>("tree");
	tree->position = glm::vec3(randomXPosition, 0, Spawndistance);
	tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	return tree;
}