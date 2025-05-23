#pragma once
#include "GameComponent.h"

class DrawComponent : public GameComponent
{
public:
	DrawComponent(const std::string id) : GameComponent(id) {};
	~DrawComponent() = default;
	virtual void draw() = 0;
};