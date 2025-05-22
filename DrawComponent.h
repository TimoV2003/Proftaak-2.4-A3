#pragma once
#include "GameComponent.h"

class DrawComponent : public GameComponent
{
public:
	DrawComponent();
	~DrawComponent();
	virtual void draw() = 0;
};

