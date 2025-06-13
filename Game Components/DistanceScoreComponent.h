#pragma once
#include "GameComponent.h"
class ScoreStrategy;

class DistanceScoreComponent : public GameComponent
{
private:
	std::shared_ptr<ScoreStrategy> scoreHolder;
public:
	DistanceScoreComponent(std::shared_ptr<ScoreStrategy> scoreHolder) : scoreHolder(scoreHolder) {}
	~DistanceScoreComponent() = default;

	virtual void update(float deltaTime) override;
};

