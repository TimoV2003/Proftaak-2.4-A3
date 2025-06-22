#pragma once
#include "OpenGLHelperFunctions.hpp"

void OpenGLHelpers::setupVAOAndVBO(uint32_t& vboId, uint32_t& vaoId, const size_t size, GLenum vboUsage, const void* data) {
	// Setting up the VAO and VBO: -----------------------
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	if (data != nullptr) {
		glBufferData(GL_ARRAY_BUFFER, size, data, vboUsage);
	}
	else {
		// If no data is provided, allocate memory without initializing
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, vboUsage);
	}

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// position attribute:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(tigl::Vertex), 0);
	glEnableVertexAttribArray(0);

	// color attribute:
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(tigl::Vertex), (const void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texCoord attribute:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(tigl::Vertex), (const void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO after setting it up
}

std::vector<tigl::Vertex> OpenGLHelpers::createRectangleVerticies(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
	// Create vertices for a background image
	std::vector<tigl::Vertex> vertices = {
		tigl::Vertex::PTC(glm::vec3(position.x, position.y + size.y, 0), glm::vec2(0, 0), color), // Bottom-left,
		tigl::Vertex::PTC(glm::vec3(position.x + size.x, position.y + size.y, 0), glm::vec2(1, 0), color), // Bottom-right
		tigl::Vertex::PTC(glm::vec3(position.x + size.x, position.y, 0), glm::vec2(1, 1), color), // Top-right
		tigl::Vertex::PTC(glm::vec3(position.x, position.y , 0), glm::vec2(0, 1), color) // Top-left
	};
	return vertices;
}