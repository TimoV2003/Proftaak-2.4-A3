#pragma once
#include "GameService.h"

//this include section is needed for the components
#include "EnemyComponent.h" 
#include "HealthComponent.h"

//this include section is needed for the factory method pattern
#include "Headers/HouseFactory.h"

//this include section is needed for the treadmill strategy
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

HouseFactory::HouseFactory() {
	endOfMillbehavior = std::make_shared<FloorMillBehavior>();
	ModelLoader::load("Resource Files/House/House1.obj", model);
	modelScaleUniform = 3.75f;
}

std::shared_ptr<GameObject> HouseFactory::CreateEntity() {
	auto tree = std::make_shared<GameObject>("house", 1);
	tree->scale = glm::vec3(modelScaleUniform, modelScaleUniform, modelScaleUniform);
	tree->addComponent(std::make_shared<MeshComponent>(model));
	tree->addComponent(std::make_shared<TreadmillComponent>(endOfMillbehavior));

	return tree;
}