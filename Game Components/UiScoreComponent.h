#pragma once
#include "GameComponent.h"
#include <memory>

class ScoreStrategy;
class TextRenderer;

class UiScoreComponent : public GameComponent {
private:
	std::shared_ptr<ScoreStrategy> scoreHolder;
	TextRenderer* textRenderer;
public:
	UiScoreComponent(std::shared_ptr<ScoreStrategy> scoreHolder, TextRenderer* textRenderer);
	~UiScoreComponent() = default;

	virtual void update(const float& deltaTime) override;
	void drawLate();
};
