#pragma once
#include "GameService.h"

//this include section is needed for the components
#include "EnemyComponent.h" 
#include "HealthComponent.h"

//this include section is needed for the factory method pattern
#include "Headers/TreeFactory.h"

//this include section is needed for the treadmill strategy
#include "../patterns/strategy/treadmill_strategies/Headers/EntityMillBehavior.h"
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

TreeFactory::TreeFactory() {
	endOfMillbehavior = std::make_shared<EntityMillBehavior>();
	ModelLoader::load("Resource Files/Tree/Tree1.obj", model);
}

std::shared_ptr<GameObject> TreeFactory::CreateEntity() {
	auto tree = std::make_shared<GameObject>("tree",1);
	tree->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	auto player = GameService::getGameObject("blocky");
	auto healthComponent = player ? player->getComponent<HealthComponent>() : nullptr;
	tree->addComponent(std::make_shared<EnemyComponent>(player, [healthComponent]() { healthComponent->decreaseHealth(); }));

	return tree;
}