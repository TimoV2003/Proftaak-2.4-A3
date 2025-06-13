#pragma once
#include "TreeFactory.h"
#include "EntityMillBehavior.h"
#include "FloorMillBehavior.h"
#include "GameService.h"

TreeFactory::TreeFactory() {
	endOfMillbehavior = std::make_shared<EntityMillBehavior>();
	ModelLoader::load("Resource Files/Tree/Tree_1.obj", model);
}

std::shared_ptr<GameObject> TreeFactory::CreateEntity() {
	auto tree = std::make_shared<GameObject>("tree");
	tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	return tree;
}