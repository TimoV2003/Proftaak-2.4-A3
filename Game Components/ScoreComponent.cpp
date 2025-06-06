#include "ScoreComponent.h"

//TODO see header
void DistanceScoreComponent::update(float deltaTime)
{
	this->scoreHolder->addDistanceScore(deltaTime);
}
