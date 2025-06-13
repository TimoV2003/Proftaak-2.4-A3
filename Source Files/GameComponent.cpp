#include "GameComponent.h"
#include "DebugReferenceCounter.h"

GameComponent::GameComponent() {
	DebugReferenceCounter::IncrementComponentReferenceCounter();
}

GameComponent::~GameComponent() {
	DebugReferenceCounter::DecrementComponentReferenceCounter();
}

std::shared_ptr<GameObject> GameComponent::getParent() {
    return parent.lock();
}