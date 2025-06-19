#pragma once
#include "GameComponent.h"
class ScoreStrategy;

/// <summary>
/// a component that updates the score based on the distance traveled.
/// </summary>
class DistanceScoreComponent : public GameComponent {
private:
	std::shared_ptr<ScoreStrategy> scoreHolder;
public:
	DistanceScoreComponent(std::shared_ptr<ScoreStrategy> scoreHolder) : scoreHolder(scoreHolder) {}
	~DistanceScoreComponent() = default;

	virtual void update(const float& deltaTime) override;
};

