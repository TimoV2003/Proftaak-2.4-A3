#pragma once
class ScoreStrategy
{
private:
	float score = 0.0f;

public:
	/// <summary>
	/// add or substract a score value
	/// </summary>
	void addScore(const float& delta);

	/// <summary>
	/// used by UI
	/// </summary>
	float getScore() const { return this->score; }
};