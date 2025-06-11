#pragma once
#include <memory>

class GameObject;

__interface IEndOfMillBehavior
{
public:
	void ReachedEndOfMill(std::shared_ptr<GameObject> parent);
};

