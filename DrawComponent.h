#pragma once
#include "GameComponent.h"
class DrawComponent : public GameComponent
{
public:
	virtual void draw() = 0;
	DrawComponent();
	~DrawComponent();

};

