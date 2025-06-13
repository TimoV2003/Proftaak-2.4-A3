#include "GameComponent.h"
#if DEBUG
#include "DebugReferenceCounter.h"
#endif

GameComponent::GameComponent() {
#if DEBUG
	DebugReferenceCounter::IncrementComponentReferenceCounter();
#endif
}

GameComponent::~GameComponent() {
#if DEBUG
	DebugReferenceCounter::DecrementComponentReferenceCounter();
#endif
}

std::shared_ptr<GameObject> GameComponent::getParent() {
    return parent.lock();
}