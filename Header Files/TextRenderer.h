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
	uint32_t fontAtlasTextureID;

	FontData(const std::string& name) : fontName(name) {}
};

struct TextFrame {
	uint32_t vaoID;
	uint32_t vboID;
	size_t vertexCount;
	size_t bufferSize;
};

struct TextVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
};

class TextRenderer {
private:
	std::map<std::string, FontData> fonts; // Vector to hold loaded fonts
	std::vector<TextFrame> textFrames; // Map to hold text frames by ID
	std::string activeFontName; // Name of the currently active font
	glm::vec4 activeColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Default color is white

	float windowHeight = 800.0f; // Default window height, can be set dynamically
	float windowWidth = 1400.0f; // Default window width, can be set dynamically

public:
	TextRenderer() = default;
	~TextRenderer();

	void setActiveFont(const std::string& fontName);
	void setActiveColor(const glm::vec4& color);
	void setWindowSize(float width, float height);

	// Load a font from a file
	void initFont(const std::string fontName, const std::filesystem::path &fontPath);
	uint32_t createTextFrame(uint16_t characterCount);
	void writeText(uint32_t textFrameId, const std::string& text, const float fontSize, const glm::vec2& position);
	void startFrame();
	void draw();
	
};
