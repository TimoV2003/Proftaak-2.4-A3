#include "GameObject.h"
#include "tigl.h"

void GameObject::addComponent(std::shared_ptr<GameComponent> component) {
	if (std::shared_ptr<DrawComponent> draw = std::dynamic_pointer_cast<DrawComponent>(component)) {
		drawComponents.push_back(draw);
		return;
	}
	gameComponents.push_back(component);
}

void GameObject::update() {
	for (auto& component : gameComponents) 
	{
		component->update();
	}
}

void GameObject::draw() {
	for (auto& component : drawComponents)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
				* glm::scale(glm::mat4(1.0f), scale);

		tigl::shader->enableColor(true);
		tigl::shader->setModelMatrix(model);

		component->draw();
	}
}

