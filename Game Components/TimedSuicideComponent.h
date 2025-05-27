#pragma once
#include "GameComponent.h"
#include "GameObject.h"

class TimedSuicideComponent : public GameComponent
{
private:
	float timer;
public:
	TimedSuicideComponent(float timer) : timer(timer) {}
	~TimedSuicideComponent() = default;
	virtual void update(float deltaTime) override;
};

