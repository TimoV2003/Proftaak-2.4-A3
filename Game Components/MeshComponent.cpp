#include "MeshComponent.h"
#include <iostream>

#include "tigl.h"

MeshComponent::MeshComponent(const Model& model)
{
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	std::map<int, std::vector<GLuint>> materialToIndices;

	std::map<std::pair<int, int>, GLuint> uniqueVertices;
	GLuint currentIndex = 0;

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

				vertexData.insert(vertexData.end(), { pos.x, pos.y, pos.z, tex.x, tex.y });
				uniqueVertices[key] = currentIndex++;
			}
			indices.push_back(uniqueVertices[key]);
		}

		for (size_t j = 1; j + 1 < indices.size(); ++j) {
			materialToIndices[matIndex].push_back(indices[0]);
			materialToIndices[matIndex].push_back(indices[j]);
			materialToIndices[matIndex].push_back(indices[j + 1]);
		}
	}

	GLuint startIndex = 0;
	for (const auto& [matIndex, indices] : materialToIndices) {
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

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
}




MeshComponent::~MeshComponent()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void MeshComponent::draw()
{
    tigl::shader->use();
    glBindVertexArray(vao);

    for (const auto& batch : drawBatches) {
        if (batch.material.textureID) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, batch.material.textureID);
            tigl::shader->enableTexture(true);

            // Bind texture unit 0 to "s_texture" in your shader
            GLuint shaderProgram = tigl::shader->getID(); // Add getID() to your shader class if needed
            glUseProgram(shaderProgram);
            GLint textureUniform = glGetUniformLocation(shaderProgram, "s_texture");
            glUniform1i(textureUniform, 0); // 0 means GL_TEXTURE0
        }

        else
        {
			tigl::shader->enableTexture(false);
        }

        glDrawElements(GL_TRIANGLES, batch.count, GL_UNSIGNED_INT, (void*)(batch.startIndex * sizeof(GLuint)));
    }

    glBindVertexArray(0);
}


