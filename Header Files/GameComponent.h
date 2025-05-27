#pragma once
#include <vector>
#include <memory>
#include <string>

class GameObject;

class GameComponent
{
protected:
	std::weak_ptr<GameObject> parent;

	/// <summary>
	/// use this when using parent. create a if (auto p = getParent()){}
	/// this automatically gets the right reference to parent without a cyclical reffence.
	/// </summary>
	/// <returns>parent GameObject ptr or nullptr</returns>
	std::shared_ptr<GameObject> getParent();

public:
	GameComponent() = default;
	~GameComponent() = default;

	virtual void update(float deltaTime) {};
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
};

