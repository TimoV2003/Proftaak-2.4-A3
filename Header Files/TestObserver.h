#pragma once
#include "I_Observer.h"
#include <iostream>

class TestObserver : public ICollisionObserver {
public:
	TestObserver() = default;
	~TestObserver() = default;
	void onCollision() override {
		std::cout << "Observer onCollision called" << std::endl;
	}
};