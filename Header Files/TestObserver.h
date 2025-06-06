#pragma once
#include "I_Observer.h"
#include <iostream>

class TestObserver : public IObserver {
public:
	TestObserver() = default;
	~TestObserver() = default;
	void notify() override {
		std::cout << "Observer notify called" << std::endl;
	}
};