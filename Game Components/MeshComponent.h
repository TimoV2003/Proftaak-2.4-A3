#pragma once
#include "DrawComponent.h"
#include "ModelLoader.h"
#include <GL/glew.h>
#include <map>

struct DrawBatch {
	GLuint startIndex;
	GLsizei count = 0;
	Material material;
};

class MeshComponent : public DrawComponent {
	private:
		GLuint vao = 0;
		GLuint vbo = 0;
		GLuint ebo = 0;
		size_t indexCount = 0;

		std::vector<DrawBatch> drawBatches;
	public:
		MeshComponent(const Model& model);
		~MeshComponent();
		void draw() override;
};

