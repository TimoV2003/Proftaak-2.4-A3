#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

struct Model {
    std::vector<glm::vec3> vertices;
    std::vector<std::vector<int>> faces; // each face contains indices into the vertices vector
};

class ModelLoader {
public:
    static bool load(const std::string& filename, Model& model);
};

