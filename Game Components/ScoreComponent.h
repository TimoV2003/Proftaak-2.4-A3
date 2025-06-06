#pragma once
#include "GameComponent.h"
#include "I_ScoreStrategy.h"

class DistanceScoreComponent : public GameComponent
{
private:
	std::shared_ptr<IScoreStrategy> scoreHolder;
public:
	DistanceScoreComponent(std::shared_ptr<IScoreStrategy> scoreHolder) : scoreHolder(scoreHolder) {}
	~DistanceScoreComponent() = default;

	//TODO make distance score scale with the speed variable. currently its only based on time
	virtual void update(float deltaTime) override;
};

