#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"

namespace OpenGLHelpers {

	void setupVAOAndVBO(uint32_t& vboId, uint32_t& vaoId, const size_t size, GLenum vboUsage, const void* data = nullptr);
	std::vector<tigl::Vertex> createRectangleVerticies(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
}