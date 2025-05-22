#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

class GameComponent
{
private:
	std::shared_ptr<GameObject> parent;
public:
	GameComponent();
	~GameComponent();

	virtual void update();//TODO elapsedtime
	inline void setGameObject(std::shared_ptr<GameObject> gameObject) { parent = gameObject; };
};

