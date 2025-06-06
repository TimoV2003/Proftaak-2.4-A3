#pragma once
#include "I_Observer.h"
#include <iostream>

class TestObserver : public IPlayerCollisionObserver {
public:
	TestObserver() = default;
	~TestObserver() = default;
	void onPlayerCollision() override {
		std::cout << "Observer onPlayerCollision called" << std::endl;
	}
};