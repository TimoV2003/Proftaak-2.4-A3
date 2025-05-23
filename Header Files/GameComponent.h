#pragma once
#include <vector>
#include <memory>
#include <string>

class GameObject;

class GameComponent
{
protected:
	std::shared_ptr<GameObject> parent;
public:
	GameComponent() = default;
	~GameComponent() = default;

	virtual void update() {}; //TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
};

