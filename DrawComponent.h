#pragma once
#include "GameComponent.h"
class DrawComponent : public GameComponent
{
public:
	virtual void Draw() = 0;
	DrawComponent();
	~DrawComponent();

};

