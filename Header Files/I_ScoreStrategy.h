#pragma once

__interface IScoreStrategy
{
	/// <summary>
	/// Score in seconds * speed.
	/// works with both adition and substraction
	/// </summary>
	void addDistanceScore(const float& score);

	/// <summary>
	/// score for amount of patients cured
	/// works with both adition and substraction
	/// </summary>
	void addPotionScore(const int& score);

	/// <summary>
	/// used by UI
	/// </summary>
	float getDistanceScore() const;

	/// <summary>
	/// used by UI
	/// </summary>
	int getPotionScore() const;
};