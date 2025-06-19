#include <iostream>
#include <sstream>
#include <iomanip>
#include "UiScoreComponent.h"
#include "TextRenderer.h"
#include "ScoreStrategy.h"

std::string uiText;
uint32_t textFrameId;

UiScoreComponent::UiScoreComponent(std::shared_ptr<ScoreStrategy> scoreHolder, TextRenderer* textRenderer)
	: scoreHolder(scoreHolder), textRenderer(textRenderer) {
	if (!textRenderer || !scoreHolder) {
		std::cerr << "UiScoreComponent: textRenderer or scoreHolder is not set." << std::endl;
		return;
	}

	uiText = "Score: 0";
	textFrameId = textRenderer->createTextFrame(50); // buffer size of 50 characters for good mesure
}

void UiScoreComponent::update(const float& deltaTime) {
	std::stringstream stream;
	stream << "Score: " << std::fixed << std::setprecision(2) << this->scoreHolder->getScore();
	uiText = stream.str();
}

void UiScoreComponent::drawLate() {
	this->textRenderer->writeText(textFrameId, uiText, 16, glm::vec2(20, 40));
}
