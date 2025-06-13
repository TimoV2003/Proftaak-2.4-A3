#include "UiScoreComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tigl.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
using tigl::Vertex;

UiScoreComponent::UiScoreComponent(std::shared_ptr<IScoreStrategy> scoreHolder) : scoreHolder(scoreHolder)
{
	//TODO implement
}

void UiScoreComponent::update(float deltaTime)
{
	//TODO implement
}

void UiScoreComponent::draw()
{
	//TODO implement
}
