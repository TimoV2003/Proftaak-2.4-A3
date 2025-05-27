#include "GameComponent.h"

std::shared_ptr<GameObject> GameComponent::getParent() {
    return parent.lock();
}
