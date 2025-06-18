#include "GameComponent.h"
#if _DEBUG
#include "DebugReferenceCounter.h"
#endif

GameComponent::GameComponent() {
#if _DEBUG
	DebugReferenceCounter::IncrementComponentReferenceCounter();
#endif
}

GameComponent::~GameComponent() {
#if _DEBUG
	DebugReferenceCounter::DecrementComponentReferenceCounter();
#endif
}

std::shared_ptr<GameObject> GameComponent::getParent()  {
    return parent.lock();
}