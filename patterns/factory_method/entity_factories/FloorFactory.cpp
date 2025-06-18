#pragma once
#include "GameService.h"

//this include section is needed for the components
#include "EnemyComponent.h" 
#include "HealthComponent.h"

//this include section is needed for the factory method pattern
#include "Headers/FloorFactory.h"

//this include section is needed for the treadmill strategy
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

FloorFactory::FloorFactory() {
	endOfMillbehavior = std::make_shared<FloorMillBehavior>();
	ModelLoader::load("Resource Files/GroundPlane/GroundTile", model);
	modelScaleUniform = 10.0f;
	modelScaleY = 1.0f;
}

std::shared_ptr<GameObject> FloorFactory::CreateEntity() {
	auto tree = std::make_shared<GameObject>("floor", 1);
	tree->scale = glm::vec3(modelScaleUniform, modelScaleY, modelScaleUniform);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	return tree;
}