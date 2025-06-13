#pragma once
#include "TreeFactory.h"
#include "EntityMillBehavior.h"
#include "FloorMillBehavior.h"
#include "GameService.h"
#include "EnemyComponent.h" 
#include "HealthComponent.h"

TreeFactory::TreeFactory() {
	endOfMillbehavior = std::make_shared<EntityMillBehavior>();
	ModelLoader::load("Resource Files/Tree/Tree_1.obj", model);
}

std::shared_ptr<GameObject> TreeFactory::CreateEntity() {
	float randomXPosition = GameService::RandomValue(-10.0f, 10.0f);


	auto tree = std::make_shared<GameObject>("tree",1);
	tree->position = glm::vec3(randomXPosition, 0, Spawndistance);
	tree->scale = glm::vec3(0.05f, 0.05f, 0.05f);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	auto player = GameService::getGameObject("blocky");
	auto healthComponent = player ? player->getComponent<HealthComponent>() : nullptr;
	tree->addComponent(std::make_shared<EnemyComponent>(player, [healthComponent]() { healthComponent->decreaseHealth(); }));

	return tree;
}