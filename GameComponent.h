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
	GameComponent(const std::string id) : id(id) {};
	~GameComponent() = default;

	virtual void update() {}; //TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
	std::string getId() const { return id; }
};

