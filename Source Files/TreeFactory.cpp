#include "TreeFactory.h"


TreeFactory::TreeFactory() {
	endOfMillbehavior = std::make_shared<EntityMillBehavior>();
}

std::shared_ptr<GameObject> TreeFactory::CreateEntity() {
	auto tree = std::make_shared<GameObject>("tree");
	tree->position = glm::vec3(0, 0, Spawndistance);
	tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));
	return tree;
}