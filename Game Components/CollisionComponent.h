#include "GameComponent.h"

#pragma once

class CollisionComponent : public GameComponent {
public:
	CollisionComponent() = default;
	~CollisionComponent() = default;
	bool collides(std::shared_ptr<GameObject> other) const;
};