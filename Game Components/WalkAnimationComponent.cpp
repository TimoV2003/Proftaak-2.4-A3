#include "WalkAnimationComponent.h"
#include <glm/glm.hpp>
#include "GameObject.h"

glm::vec3 initialScale = glm::vec3(0,0,0);
constexpr double PI = 3.14159265358979323846;

void WalkAnimationComponent::update(const float& deltaTime) {  
	if (initialScale == glm::vec3(0, 0, 0)) {  
		if (auto p = getParent()) {  
			initialScale = p->scale;  
		}  
	}
	
	static float time = 0.0f;
	time += deltaTime*animationSpeedMult;  
	if (time >= cyclePeriod) {  
		time -= cyclePeriod;  
	}
	if (auto p = getParent()) {  
		float scaler =  sin(time * PI);
		glm::vec3 newScale = initialScale * (baseScale + scaler * scaleFactor);
		p->scale = newScale;
	}  
}