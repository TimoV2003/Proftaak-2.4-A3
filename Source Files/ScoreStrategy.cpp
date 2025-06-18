#include "ScoreStrategy.h"  
#include <algorithm>

void ScoreStrategy::addScore(const float& delta) {  
	this->score = std::max(this->score + delta, 0.0f);
}

