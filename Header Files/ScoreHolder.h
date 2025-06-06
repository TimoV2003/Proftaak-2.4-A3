#pragma once
#include "I_ScoreStrategy.h"
class ScoreHolder : public IScoreStrategy
{
private:
	float distanceScore = 0.0f;
	int potionScore = 0;
public:
	ScoreHolder() = default;
	~ScoreHolder() = default;

	// score clamped to 0 and above
	void addDistanceScore(const float& score) override;
	// score clamped to 0 and above
	void addPotionScore(const int& score) override;

	float getDistanceScore() const override;
	int getPotionScore() const override;
};

