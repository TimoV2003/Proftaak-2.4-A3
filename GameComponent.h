#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

class GameComponent
{
private:
	std::shared_ptr<GameObject> parent;
	std::string id;
public:
	GameComponent(const std::string& id) : id(id) {}
	virtual ~GameComponent() = default;

	virtual void update() {}; //TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
	std::string getId() const { return id; }
};

