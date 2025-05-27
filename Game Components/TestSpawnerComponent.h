#pragma once
#include "GameComponent.h"
#include "GameObject.h"
#include "ModelLoader.h"

class TestSpawnerComponent : public GameComponent
{
private:
	Model model;
public:
	TestSpawnerComponent(Model model) : model(model) {}
	~TestSpawnerComponent() = default;
	virtual void update(float deltaTime) override;
};

