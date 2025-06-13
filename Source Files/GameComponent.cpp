#include "GameComponent.h"
#include "DebugRefferenceCounter.h"

GameComponent::GameComponent() {
	DebugRefferenceCounter::IncrementComponentReferenceCounter();
}

GameComponent::~GameComponent() {
	DebugRefferenceCounter::DecrementComponentReferenceCounter();
}

std::shared_ptr<GameObject> GameComponent::getParent() {
    return parent.lock();
}