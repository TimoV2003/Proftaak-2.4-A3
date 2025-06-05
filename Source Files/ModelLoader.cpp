#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ModelLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool ModelLoader::load(const std::string& filename, Model& model)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return false;
	}

	std::string line;
	std::string currentMaterial = "";
	int currentMaterialIndex = -1;

	std::string basePath = filename.substr(0, filename.find_last_of("/\\") + 1);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v") {
			glm::vec3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			model.vertices.push_back(vertex);
		}
		else if (prefix == "vt") {
			glm::vec2 tex;
			iss >> tex.x >> tex.y;
			model.texcoords.push_back(tex);
		}
		else if (prefix == "f") {
			Face face;
			std::string vertexStr;
			while (iss >> vertexStr) {
				std::stringstream vertexStream(vertexStr);
				std::string vStr, vtStr;

				std::getline(vertexStream, vStr, '/');
				std::getline(vertexStream, vtStr, '/');

				int vIndex = vStr.empty() ? -1 : std::stoi(vStr) - 1;
				int vtIndex = vtStr.empty() ? -1 : std::stoi(vtStr) - 1;

				face.vertices.push_back({ vIndex, vtIndex });
			}

			if (face.vertices.size() >= 3) {
				model.faces.push_back(face);
				model.faceMaterialIndices.push_back(currentMaterialIndex);
			}
		}
		else if (prefix == "mtllib") {
			std::string mtlFile = basePath + line.substr(7);
			if (!loadMaterialFile(mtlFile, model)) {
				std::cerr << "Warning: Could not load material file: " << mtlFile << std::endl;
			}
		}
		else if (prefix == "usemtl") {
			std::string materialName;
			iss >> materialName;
			currentMaterial = materialName;

			currentMaterialIndex = -1;
			for (size_t i = 0; i < model.materials.size(); ++i) {
				if (model.materials[i].name == materialName) {
					currentMaterialIndex = static_cast<int>(i);
					break;
				}
			}
		}
	}

	std::cout << "Loaded model with " << model.vertices.size()
		<< " vertices, " << model.faces.size()
		<< " faces, and " << model.materials.size()
		<< " materials." << std::endl;

	return true;
}

bool ModelLoader::loadMaterialFile(const std::string& mtlFilename, Model& model)
{
	std::ifstream file(mtlFilename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open material file " << mtlFilename << std::endl;
		return false;
	}

	std::string line;
	Material currentMaterial;
	bool inMaterial = false;

	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#')
			continue;

		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "newmtl") {
			if (inMaterial) {
				model.materials.push_back(currentMaterial);
			}
			currentMaterial = Material();
			inMaterial = true;
			iss >> currentMaterial.name;
		}
		else if (prefix == "Ka") {
			iss >> currentMaterial.ambient.r >> currentMaterial.ambient.g >> currentMaterial.ambient.b;
		}
		else if (prefix == "Kd") {
			iss >> currentMaterial.diffuse.r >> currentMaterial.diffuse.g >> currentMaterial.diffuse.b;
		}
		else if (prefix == "Ks") {
			iss >> currentMaterial.specular.r >> currentMaterial.specular.g >> currentMaterial.specular.b;
		}
		else if (prefix == "Ns") {
			iss >> currentMaterial.shininess;
		}
		else if (prefix == "map_Kd") {
			iss >> currentMaterial.textureFilename;

			std::string fullPath = mtlFilename.substr(0, mtlFilename.find_last_of("/\\") + 1) + currentMaterial.textureFilename;

			glGenTextures(1, &currentMaterial.textureID);
			glBindTexture(GL_TEXTURE_2D, currentMaterial.textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int width, height, nrChannels;
			unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				std::cerr << "Failed to load texture: " << fullPath << std::endl;
			}
			stbi_image_free(data);
		}
	}

	if (inMaterial) {
		model.materials.push_back(currentMaterial);
	}

	return true;
}
