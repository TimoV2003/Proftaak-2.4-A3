#pragma once
#include "DrawComponent.h"
#include "I_ScoreStrategy.h"

class UiScoreComponent : public DrawComponent
{
private:
	std::shared_ptr<IScoreStrategy> scoreHolder;

public:
	UiScoreComponent(std::shared_ptr<IScoreStrategy> scoreHolder);
	~UiScoreComponent() = default;

	virtual void update(float deltaTime) override;
	virtual void draw() override;
};