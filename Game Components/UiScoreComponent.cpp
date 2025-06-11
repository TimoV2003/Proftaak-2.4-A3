#include "UiScoreComponent.h"
#include "stb_truetype.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <tigl.h>

stbtt_bakedchar cdata[96];
GLuint texId;
glm::vec4 color = glm::vec4(0, 0, 0, 1);

std::string text = "Hello world";

UiScoreComponent::UiScoreComponent(std::shared_ptr<IScoreStrategy> scoreHolder) : scoreHolder(scoreHolder)
{

}

void UiScoreComponent::update(float deltaTime)
{

}

void UiScoreComponent::draw()
{

}
