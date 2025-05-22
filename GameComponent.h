#pragma once
#include <vector>
#include <memory>
#include <string>

class GameObject;

class GameComponent
{
protected:
	std::string id;
	std::shared_ptr<GameObject> parent;
public:
	GameComponent();
	~GameComponent();

	virtual void update() {}; //TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
	std::string getId() const { return id; }
};

