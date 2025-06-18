#include "WalkAnimationComponent.h"
#include <glm/glm.hpp>
#include "GameObject.h"

glm::vec3 initialScale = glm::vec3(0,0,0);
constexpr double PI = 3.14159265358979323846;

void WalkAnimationComponent::update(float deltaTime) {  
	if (initialScale == glm::vec3(0, 0, 0)) {  
		if (auto p = getParent()) {  
			initialScale = p->scale;  
		}  
	}
	
	static float time = 0.0f;
	time += deltaTime*3;  
	if (time >= 2.0f) {  
		time -= 2.0f;  
	}
	if (auto p = getParent()) {  
		float scaleFactor =  sin(time * PI);
		glm::vec3 newScale = initialScale * (1.0f + scaleFactor * 0.03f);
		p->scale = newScale;
	}  
}