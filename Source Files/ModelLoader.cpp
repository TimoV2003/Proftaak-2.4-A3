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
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		if (prefix == "v") {
			glm::vec3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			model.vertices.push_back(vertex);
		}
		else if (prefix == "f") {
			std::vector<int> face;
			int index;
			while (iss >> index) {
				face.push_back(index - 1); // OBJ indices are 1-based
			}
			model.faces.push_back(face);
		}
	}

	std::cout << "Loaded model with " << model.vertices.size() << " vertices and " << model.faces.size() << " faces." << std::endl;

	return true;
}