#pragma once
#include "GameComponent.h"

class DrawComponent : public GameComponent
{
public:
	DrawComponent() = default;
	~DrawComponent() = default;
	virtual void draw() = 0;
}; 