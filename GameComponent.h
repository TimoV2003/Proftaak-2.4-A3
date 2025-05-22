#pragma once
#include "GameObject.h"
class GameComponent
{
private:
	std::shared_ptr<GameObject> parent;
public:
	GameComponent();
	~GameComponent();

	void update();//TODO elapsedtime
	void setGameObject(std::shared_ptr<GameObject> gameObject);
};

