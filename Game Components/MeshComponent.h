#pragma once
#include "DrawComponent.h"
#include "ModelLoader.h"
#include <GL/glew.h>

class MeshComponent : public DrawComponent
{
	private:
		GLuint vao = 0;
		GLuint vbo = 0;
		GLuint ebo = 0;
		size_t indexCount = 0;
	public:
		MeshComponent(const Model& model);
		~MeshComponent();
		void draw() override;
};

