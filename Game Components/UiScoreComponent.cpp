#include "UiScoreComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tigl.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include <glm/ext/matrix_clip_space.hpp>
using tigl::Vertex;

stbtt_bakedchar cdata[96];
GLuint texId;
glm::vec4 color = glm::vec4(0, 0, 0, 1);

std::string text = "Hello world";

UiScoreComponent::UiScoreComponent(std::shared_ptr<IScoreStrategy> scoreHolder) : scoreHolder(scoreHolder)
{
	//code from CGR Demo -> font demo
	//unsigned char* ttf_buffer = new unsigned char[1 << 20];
	//unsigned char* temp_bitmap = new unsigned char[512 * 512];
	//constexpr size_t element_size = 1;
	//constexpr size_t element_count = 1 << 20;
	//FILE* file = nullptr;
	//fopen_s(&file, "c:/windows/fonts/times.ttf", "rb"); //rb = read binary
	//if (file) fread(ttf_buffer, element_size, element_count, file);
	//stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
	//glGenTextures(1, &texId);
	//glBindTexture(GL_TEXTURE_2D, texId);
	//GLint swizzleMask[] = { GL_ALPHA, GL_ALPHA, GL_ALPHA, GL_ALPHA };
	//glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//delete[] ttf_buffer;
	//delete[] temp_bitmap;
}

void UiScoreComponent::update(float deltaTime)
{

}

void UiScoreComponent::draw()
{
	//int viewport[4];
	//glGetIntegerv(GL_VIEWPORT, viewport);
	//tigl::shader->setProjectionMatrix(glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, -100.0f, 100.0f));
	//tigl::shader->setViewMatrix(glm::mat4(1.0f));
	//tigl::shader->setModelMatrix(glm::mat4(1.0f));

	//tigl::shader->enableColor(false);
	//tigl::shader->enableLighting(false);
	//tigl::shader->enableTexture(true);
	//tigl::shader->enableColorMult(true);
	//tigl::shader->setColorMult(color);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
	//glBindTexture(GL_TEXTURE_2D, texId);

	//float x = 400, y = 300;
	//stbtt_aligned_quad q;
	//tigl::begin(GL_QUADS);
	//for (int i = 0; i < text.size(); i++) {
	//	if (text[i] >= 32 && text[i] < 128) {
	//		stbtt_GetBakedQuad(cdata, 512, 512, text[i] - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
	//		tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y0, 0), glm::vec2(q.s0, q.t0)));
	//		tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y0, 0), glm::vec2(q.s1, q.t0)));
	//		tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y1, 0), glm::vec2(q.s1, q.t1)));
	//		tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y1, 0), glm::vec2(q.s0, q.t1)));
	//	}
	//}
	//tigl::end();
	//tigl::shader->enableColorMult(false);
}
