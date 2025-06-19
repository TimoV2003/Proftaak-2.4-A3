#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Material {
	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	std::string textureFilename;
	GLuint textureID = 0;
};

struct FaceVertex {
	int vertexIndex;
	int texcoordIndex;
};

struct Face {
	std::vector<FaceVertex> vertices;
};

struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texcoords;
	std::vector<Face> faces;
	std::vector<int> faceMaterialIndices;
	std::vector<Material> materials;
};

class ModelLoader {
public:
	/// <summary>
	/// loads an OBJ model from file and populates the provided Model structure.
	/// </summary>
	/// <returns>succes or not</returns>
	static bool load(const std::string& filename, Model& model);

	/// <summary>
	/// loads a material file and adds materials to the model.
	/// </summary>
	/// <returns>succes or not</returns>
	static bool loadMaterialFile(const std::string& mtlFilename, Model& model);
};
