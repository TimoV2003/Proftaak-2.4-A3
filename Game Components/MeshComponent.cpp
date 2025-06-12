#include "MeshComponent.h"
#include <iostream>
#include "tigl.h"

// Constructor: Builds the mesh from model data
MeshComponent::MeshComponent(const Model& model)
{
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	std::map<int, std::vector<GLuint>> materialToIndices; // Maps material index to triangle indices

	std::map<std::pair<int, int>, GLuint> uniqueVertices;
	GLuint currentIndex = 0;

	// Loop through each face to prepare vertex/index data
	for (size_t i = 0; i < model.faces.size(); ++i) {
		const auto& face = model.faces[i];
		int matIndex = model.faceMaterialIndices[i];
		std::vector<GLuint> indices;

		for (const auto& fv : face.vertices) {
			std::pair<int, int> key = { fv.vertexIndex, fv.texcoordIndex };
			if (uniqueVertices.count(key) == 0) {
				const glm::vec3& pos = model.vertices[fv.vertexIndex];
				glm::vec2 tex = (fv.texcoordIndex >= 0 && fv.texcoordIndex < model.texcoords.size())
					? model.texcoords[fv.texcoordIndex] : glm::vec2(0.0f);

				// Push vertex position and texcoord
				vertexData.insert(vertexData.end(), { pos.x, pos.y, pos.z, tex.x, tex.y });
				uniqueVertices[key] = currentIndex++;
			}
			indices.push_back(uniqueVertices[key]);
		}

		// Triangulate face
		for (size_t j = 1; j + 1 < indices.size(); ++j) {
			materialToIndices[matIndex].push_back(indices[0]);
			materialToIndices[matIndex].push_back(indices[j]);
			materialToIndices[matIndex].push_back(indices[j + 1]);
		}
	}

	GLuint startIndex = 0;
	for (const auto& [matIndex, indices] : materialToIndices) {
		// Create a draw batch per material
		DrawBatch batch;
		batch.startIndex = startIndex;
		batch.count = static_cast<GLsizei>(indices.size());
		batch.material = (matIndex >= 0 && matIndex < model.materials.size()) ?
			model.materials[matIndex] : Material{};
		drawBatches.push_back(batch);

		indexData.insert(indexData.end(), indices.begin(), indices.end());
		startIndex += static_cast<GLuint>(indices.size());
	}

	indexCount = static_cast<GLsizei>(indexData.size());

	// Create OpenGL buffers and VAO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);

	// Vertex attribute: position on index 0 (3 floats)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	// Vertex attribute: texcoord on index 2 (2 floats)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	//layout(location = 0) in vec3 a_position;
	//layout(location = 1) in vec4 a_color;
	//layout(location = 2) in vec2 a_texcoord;
	//layout(location = 3) in vec3 a_normal;
	glBindVertexArray(0);
}

// Destructor: Clean up OpenGL resources
MeshComponent::~MeshComponent()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

// Draw the mesh with correct material textures
void MeshComponent::draw()
{
	tigl::shader->use();
	glBindVertexArray(vao);

	for (const auto& batch : drawBatches) {
		if (batch.material.textureID) {
			// Enable and bind texture
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, batch.material.textureID);
			tigl::shader->enableTexture(true);
		}
		else {
			// No texture for this batch
			tigl::shader->enableTexture(false);
		}

		// Draw elements (triangles)
		glDrawElements(GL_TRIANGLES, batch.count, GL_UNSIGNED_INT, (void*)(batch.startIndex * sizeof(GLuint)));
	}

	glBindVertexArray(0);
}
