#include "MeshComponent.h"
#include <iostream>

MeshComponent::MeshComponent(const Model& model)
{
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indexData;

    for (size_t i = 0; i < model.vertices.size(); ++i) {
        const auto& vertex = model.vertices[i];
        const auto& color = model.colors[i]; // Assumes same size as vertices

        vertexData.push_back(vertex.x);
        vertexData.push_back(vertex.y);
        vertexData.push_back(vertex.z);

        vertexData.push_back(color.r);
        vertexData.push_back(color.g);
        vertexData.push_back(color.b);
    }

    for (const auto& face : model.faces) {
        if (face.size() == 3) {
            indexData.insert(indexData.end(), {
			static_cast<GLuint>(face[0]),
			static_cast<GLuint>(face[1]),
			static_cast<GLuint>(face[2])
            });
        }
        else if (face.size() == 4) {
            indexData.insert(indexData.end(), {
			static_cast<GLuint>(face[0]),
			static_cast<GLuint>(face[1]),
			static_cast<GLuint>(face[2]),
			static_cast<GLuint>(face[2]),
			static_cast<GLuint>(face[3]),
			static_cast<GLuint>(face[0])
            });
        }
        else {
            std::cerr << "Non-triangular face detected (" << face.size() << "), skipping for now.\n";
        }
    }

    indexCount = indexData.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);

    // Vertex Position (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    // Vertex Color (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

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
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
