#pragma once
#include <stb_truetype.h>
#include <string>
#include <map>
#include <filesystem>
#include <fstream>
#include <GL/glew.h>
#include "tigl.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

struct FontData {
	const std::string fontName;
	GLuint textureId;
	stbtt_bakedchar *cdata;

	FontData(const std::string& name) : fontName(name) {}
};

class TextRenderer {
private:
	std::map<std::string, FontData> fonts; // Vector to hold loaded fonts

public:
	TextRenderer() = default;
	~TextRenderer();

	// Load a font from a file
	bool loadFont(const std::string fontName, const std::filesystem::path &fontPath);
	void writeText(const std::string& text, const std::string& fontName, const glm::vec4& color);
};
