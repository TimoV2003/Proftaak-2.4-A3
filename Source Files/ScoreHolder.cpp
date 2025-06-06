#include "ScoreHolder.h"
#include <algorithm>
#include <iostream>

void ScoreHolder::addDistanceScore(const float& score)
{
    this->distanceScore = std::max(this->distanceScore + score, 0.0f);
}

void ScoreHolder::addPotionScore(const int& score)
{
    this->potionScore = std::min(this->potionScore + score, 0);
}

float ScoreHolder::getDistanceScore() const
{
    return this->distanceScore;
}

int ScoreHolder::getPotionScore() const
{
    return this->potionScore;
}
