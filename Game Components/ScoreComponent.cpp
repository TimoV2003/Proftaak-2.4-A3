#include "ScoreComponent.h"

void DistanceScoreComponent::update(float deltaTime)
{
	//TODO make distance score scale with the speed variable. currently its only based on time
	this->scoreHolder->addDistanceScore(deltaTime);
}
