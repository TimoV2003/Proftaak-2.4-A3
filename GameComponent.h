#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

class GameComponent
{
protected:
	std::string id;
	std::shared_ptr<GameObject> parent;
public:
	GameComponent(const std::string& id) : id(id) {}
	~GameComponent();

	virtual void update() {}; //TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
	std::string getId() const { return id; }
};

